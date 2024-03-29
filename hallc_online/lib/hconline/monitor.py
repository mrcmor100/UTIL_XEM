#!/usr/bin/env python3

from hconline.error import HallCError
from epics import PV, caget
from collections import abc
from copy import deepcopy
from hconline.error import HallCError

import argparse
import json
import os
import subprocess
import sys
import time

class MonitorTypeError(HallCError):
    '''Exception raised when an unknown type is encountered by the monitor'''
    def __init__(self, type):
        self.message = 'Unknown variable type: {}'.format(type)
class MonitorKeyError(HallCError):
    '''Exception raised when trying to access unknown section.'''
    def __init(self, key):
        self.message = 'Unknown monitor section: {}'.format(key)

## misc target specs
def _target_spec(encoder, refgas):
    tolerance = 15000
    if encoder is None:
        return {
            'mass': 0.0,
            'name': 'UNKNOWN'}
    elif abs(encoder - 31700060) < tolerance:
        return {
            'mass': 3.0160293,
            'name': 'He3'}
    elif abs(encoder - 24126300) < tolerance:
        return {
            'mass': 4.002603254,
            'name': 'He4'}
    elif abs(encoder - 19368909) < tolerance:
        return {
            'mass': 26.981539,
            'name': 'OPTICS-1'}
    elif abs(encoder - 18556109) < tolerance:
        return {
            'mass': 26.981539,
            'name': 'Dummy'}
    elif abs(encoder - 16767949) < tolerance:
        return {
            'mass': 7.016003,
            'name': 'Li-7'}
    elif abs(encoder - 15630029) < tolerance:
        return {
            'mass': 6.01512288,
            'name': 'Li-6'}
    elif abs(encoder - 14492109) < tolerance:
        return {
            'mass': 9.0122,
            'name': 'Be-9'}
    elif abs(encoder - 13354189) < tolerance:
        return {
            'mass': 12.0107,
            'name': 'C-12'}
    elif abs(encoder - 12216269) < tolerance:
        return {
            'mass': 11.009306,
            'name': 'B4C-11'}
    elif abs(encoder - 11078349) < tolerance:
        return {
            'mass': 10.0102,
            'name': 'B4C-10'}
    elif abs(encoder - 9940429) < tolerance:
        return {
            'mass': 26.98,
            'name': 'Al'}
    elif abs(encoder - 8802509) < tolerance:
        return {
            'mass': 63.54,
            'name': 'Cu'}
    elif abs(encoder - 7664589) < tolerance:
        return {
            'mass': 47.9479463,
            'name': 'Ti'}
    elif abs(encoder - 6526669) < tolerance:
        return {
            'mass': 53.9396147,
            'name': 'Fe'}
    elif abs(encoder - 5388749) < tolerance:
        return {
            'mass': 196.966,
            'name': 'Au'}
    elif abs(encoder - 4250829) < tolerance:
        return {
            'mass': 39.962590863,
            'name': 'Ca-40'}
    elif abs(encoder - 3112909) < tolerance:
        return {
            'mass': 0.00,
            'name': 'EMPTY'}
    elif abs(encoder - 2073170) < tolerance:
        return {
            'mass': 12.0107,
            'name': 'Hole'}
    elif abs(encoder - 0.00) < tolerance:
        return {
            'mass': 0.0,
            'name': 'HOME'}
    else:
        return {
            'mass': 0.0,
            'name': 'UNKNOWN'}

_DEFAULT_DEFINITIONS = {
        'target': {
            'target_id': 'hcBDSPOS.VAL',
            'target_name': {
                'type': 'calc',
                'input': ['hcBDSPOS.VAL', 'hcBDSPOS.VAL'],
                'func': lambda encoder, refgas: _target_spec(encoder, refgas)['name']
                },
            'target_mass_amu': {
                'type': 'calc',
                'input': ['hcBDSPOS.VAL', 'polhe3:RefCellGasType'],
                'func': lambda encoder, refgas: _target_spec(encoder, refgas)['mass']
                },
            },
        'beam': {
            'beam_energy': {
                'type': 'calc',
                'input': ['HALLC:p'],
                'func': lambda p_in_mev: p_in_mev/1000.
                },
            'beam_current': 'ibcm1',
            'half_wave_plate': {
                'type': 'calc',
                'input': ['IGL1I00DI24_24M'],
                'func': lambda is_out: 'OUT' if is_out else 'IN'
                },
            'wien_angle': 'WienAngle',
            'Phi_FG': 'Phi_FG',
            'FlipState': 'FlipState',
            'HWienAngle': 'HWienAngle',
            'VWienAngle': 'VWienAngle'
            },
        'spectrometers': {
            'shms_momentum': 'hcSHMSMomentum',
            'hms_momentum': 'hcHMSMomentum',
            'shms_angle': 'hcSHMSCorrectedAngle',
            'hms_angle': 'hcHMSCorrectedAngle'
            },
        'daq': {
            'HMS_ps1': 'hcHMSDAQ_ps1',
            'HMS_ps2': 'hcHMSDAQ_ps2',
            'HMS_ps3': 'hcHMSDAQ_ps3',
            'HMS_ps4': 'hcHMSDAQ_ps4',
            'HMS_ps5': 'hcHMSDAQ_ps5',
            'HMS_ps6': 'hcHMSDAQ_ps6',
            'SHMS_ps1': 'hcSHMSDAQ_ps1',
            'SHMS_ps2': 'hcSHMSDAQ_ps2',
            'SHMS_ps3': 'hcSHMSDAQ_ps3',
            'SHMS_ps4': 'hcSHMSDAQ_ps4',
            'SHMS_ps5': 'hcSHMSDAQ_ps5',
            'SHMS_ps6': 'hcSHMSDAQ_ps6',
            'COIN_ps1': 'hcSHMSDAQ_ps1',
            'COIN_ps2': 'hcSHMSDAQ_ps2',
            'COIN_ps3': 'hcSHMSDAQ_ps3',
            'COIN_ps4': 'hcSHMSDAQ_ps4',
            'COIN_ps5': 'hcSHMSDAQ_ps5',
            'COIN_ps6': 'hcSHMSDAQ_ps6'
            },
        'replay': {
            'SHMS_nevts': 'hcSHMSRunApproxEvts',
            'HMS_nevts': 'hcHMSRunApproxEvts',
            'COIN_nevts': 'hcCOINRunApproxEvts'
            },
    }

class MonitorAddError(HallCError):
    def __init__(self, var, problem):
        self.message = 'Unable to add variable {}, {}'.format(var, problem)

class Monitor():
    def __init__(self):
        '''Initialize the monitor.'''
        self._definitions = deepcopy(_DEFAULT_DEFINITIONS)
        self.sections = [key for key in self._definitions]
        for section_name in self.sections:
            setattr(self, section_name, lambda : self.get(section_name))
        self._pv_buf = {}
        self._init_pvs()
    def get(self, section_name):
        '''Return the a dict with the values for section_name.'''
        if section_name is 'all':
            return self.all()
        section = self._definitions[section_name]
        return {key: self._get_value(section[key]) for key in section}
    def all(self):
        '''Return the values for all sections at once in a master dictionary.'''
        return {key: self.get(key) for key in self._definitions}
    def add(self, section_name, name, var):
        '''Add new variables to the monitor, with error checking.
        
        Parameters:
            - section_name: Can be the name of an existing or new section
            - name: Variable name. Existing variables will be overwritten
            - var: Variable definition, can be:
                - a string containing an epics variable name
                - a dictionary for a straight epics variable:
                    {'type': 'pv', 'name': 'EpicsPVName'}
                - a 'lookup' object that links to the value of a new epics variable based on
                  the values of a list of input epics variables
                    {'type': 'lookup', 'input': [ListOfInputPVs], 
                                       'func': lambda *InputPvValues: sometransform
                                       'table': {input, 'PVName', ...}
                - a 'calc' object that calculates a new value based on
                  the values of a list of input epics variables
                    {'type': 'calc', 'input': [ListOfInputPVs], 'func': CalcValue(*input)}
        '''
        if section_name not in self.sections:
            self.section.append(section_name)
            self._definitions[section_name] = {}
        ## Check for problems
        if isinstance(var, abc.Mapping):
            if not 'type' in var:
                raise MonitorAddError(name, 'no type field provided, unable to proceed proceed')
            elif var['type'] is 'pv' and not 'name' in var:
                raise MonitorAddError(name, 'type is pv but no name field provided')
            elif var['type'] is 'lookup' and not 'input' in var:
                raise MonitorAddError(name, 'type is lookup but no input field provided')
            elif var['type'] is 'lookup' and not 'table' in var:
                raise MonitorAddError(name, 'type is lookup but no table field provided')
            elif var['type'] is 'lookup' and not 'func' in var:
                raise MonitorAddError(name, 'type is lookup but no func field provided')
            elif var['type'] is 'calc' and not 'input' in var:
                raise MonitorAddError(name, 'type is calc but no input field provided')
            elif var['type'] is 'calc' and not 'func' in var:
                raise MonitorAddError(name, 'type is calc but no func field provided')
        ## All good:
        self._definitions[section_name][name] = var
        self._init_pvs()
    def _get_value(self, var):
        '''Get the value associated with this var, throw on issues.'''
        if not isinstance(var, abc.Mapping):
            return self._pv_get(var)
        else:
            if var['type'] is 'pv':
                return self._pv_get(var['name'])
            elif var['type'] is 'lookup':
                input = [self._pv_get(pv) for pv in var['input']]
                return self._pv_get(var['table'][var['func'](*input)])
            elif var['type'] is 'calc':
                input = [self._pv_get(pv) for pv in var['input']]
                return var['func'](*input)
            else: 
                raise MonitorTypeError(var['type'])
    def _pv_get(self, pv_name):
        '''Internal function that returns the PV value.'''
        ret =  self._pv_buf[pv_name].get()
        return ret
    def _init_pvs(self):
        print('Monitor: Loading PVs (will take 10s) ...')
        for section_name in self._definitions:
            section = self._definitions[section_name]
            for key in section:
                var = section[key]
                if not isinstance(var, abc.Mapping):
                    self._load_pv(var)
                else:
                    if var['type'] is 'pv':
                        self._load_pv(var['name'])
                    elif var['type'] is 'lookup':
                        self._load_pvs(var['input'])
                        self._load_pvs(var['table'])
                        for index in var['table']:
                            self._load_pv(var['table'][index])
                    elif var['type'] is 'calc':
                        for pv_name in var['input']:
                            self._load_pv(pv_name)
                    else:
                        raise MonitorTypeError(var['type'])
        time.sleep(10)
        print('Monitor: PVs loaded.')
    def _load_pvs(self, pv_names):
        if not isinstance(pv_names, abc.Mapping):
            for pv_name in pv_names:
                self._load_pv(pv_name)
        else:
            for key in pv_names:
                self._load_pv(pv_names[key])
    def _load_pv(self, pv_name):
        if not pv_name in self._pv_buf:
            self._pv_buf[pv_name] = PV(pv_name)



