#! /usr/bin/python

# Stephen JD Kay - 19/08/21 - University of Regina
# Script to grab info from a report file, for use in the run list shell script
# This script scans every line of the report file to find the correct info

# C. Yero - May 26, 2022
# Modified to meet the needs of CaFe 2022 Experiment.
# The modified code creates a csv file and writes the
# pertinent information from the cafe output report to
# a .csv file on a run-by-run basis

# Casey Morean
# Modified to meed the needs of XEM 2022 Experiment.
# The modified code creates a csv file and writes the
# useful information from the XEM output report to
# a CSV file on a run-by-run basis.

# Import relevant packages
import sys, math, os, subprocess, csv
from datetime import datetime
import numpy as np
sys.path.insert(0, 'python/')

# user input
SPEC = sys.argv[1]
RUNNUM = sys.argv[2]
EVTNUM = sys.argv[3]

# construct generic report output file from the user input (whihc should have been generated)
if SPEC=="shms":
    xem_report_path = "REPORT_OUTPUT/SHMS/PRODUCTION/replay_shms_production_%s_%s.report" % (RUNNUM, EVTNUM)
    fname_path='UTIL_XEM/runlist/xem-2022_shms_runlist.csv'
    specl = "p"
elif SPEC=="hms":
    xem_report_path = "REPORT_OUTPUT/HMS/PRODUCTION/replay_hms_production_%s_%s.report" % (RUNNUM, EVTNUM)
    fname_path='UTIL_XEM/runlist/xem-2022_hms_runlist.csv'
    specl = "h"

#bcm_type = sys.argv[2]         # <entry_type> = "bcm_type", passed from run_cafe_prod.sh
xem_report = open(xem_report_path)


# define filenames
temp_fname_path='UTIL_XEM/runlist/temp.csv' # temporary file (for overwriting entry, if the user desires)

# check if run list exists, else create it and add a header
run_exists_flag = False
overwrite_flag = False

if os.path.isfile(fname_path):
    print (fname_path," exists !")

# ---------------check if RUNNUM already exists-------------
    f= open(fname_path, 'r')
    lines = csv.reader(f, delimiter=',')

    for row in lines:
        if(row[0]==str(RUNNUM)):
            run_exists_flag = True
            break;
        else:
            run_exists_flag = False

    f.close()

#Check if the user wants to overwrite an existing run in the runlist.
    query=""
    query_2=""
    if(run_exists_flag):
        if( int(sys.version[0]) < 3 ):
            query = raw_input('Run Number %s exits ! Are you sure you want to overwrite it? [y/n]:' %(RUNNUM))
        else:
            query = input('Run Number %s exits ! Are you sure you want to overwrite it? [y/n]:' %(RUNNUM))
        print('query_test: ', query)
        if(query=='y' or query=='Y' or query=='yes' or query=='YES'):
            print('OK, will overwrite run %s in csv file !' % RUNNUM)
            overwrite_flag = True
        elif(query=='n' or query=='N' or query=='no' or query=='NO'):
            print('Will NOT overwrite run %s in csv file !' % RUNNUM)
            overwrite_flag = False

            if( int(sys.version[0]) < 3 ):
                query_2 = raw_input('Would you like to write Run Number %s as a duplicate entry? [y/n]:' %(RUNNUM))
            else:
                query_2 = input('Would you like to write Run Number %s as a duplicate entry? [y/n]:' %(RUNNUM))
            if(query_2=='y' or query_2=='Y' or query_2=='yes' or query_2=='YES'):
                print('OK, will add Run Number %s as a duplicate in csv file !' % RUNNUM)
            elif(query_2=='n' or query_2=='N' or query_2=='no' or query_2=='NO'):
                print('OK, will NOT add Run Number %s as a duplicate in csv file !\n Exiting Now . . .' % RUNNUM)
                exit()

#---------------------------------------------------


# general run info
run_num=0
momentum=0
target_amu=0
spec_theta=0
beam_e=0
evt_num=0

bcm_thrs=0
beam_on_target=0
beam_on_tgt_pct=0

bcm1_cut_current=0
bcm1_cut_charge=0
bcm2_cut_current=0
bcm2_cut_charge=0
bcm4a_cut_current=0
bcm4a_cut_charge=0
bcm4b_cut_current=0
bcm4b_cut_charge=0
bcm4c_cut_current=0
bcm4c_cut_charge=0

run_length=0

# trigger info (only enabled triggers, i.e PS# != -1 will be written to kin file)
PS1=-1    # SHMS 3/4
PS2=-1    # SHMS EL-REAL
PS3=-1    # SHMS EL-CLEAN

T1_scaler=np.nan
T2_scaler=np.nan
T3_scaler=np.nan

T1_scaler_rate=np.nan
T2_scaler_rate=np.nan
T3_scaler_rate=np.nan

T1_accp=np.nan
T2_accp=np.nan
T3_accp=np.nan

T1_accp_rate=np.nan
T2_accp_rate=np.nan
T3_accp_rate=np.nan

# tracking efficiency
trk_eff=np.nan

# daq live time
T1_cpuLT=np.nan
T1_tLT=np.nan

T2_cpuLT=np.nan
T2_tLT=np.nan

T3_cpuLT=np.nan
T3_tLT=np.nan

EDTM_accp=0
EDTM_sent=0

TestVar = 0 # Counter to check the right number of variables have been set,
for line in xem_report:
    if (line[0]=="="): continue;

    # general run information
    if "Run Num" in line :
        run_num = int((line.split(":")[1]).strip())
        TestVar+=1
        # print(run_num)
    if "Momentum" in line :
        momentum = float((line.split(":")[1]).strip())
        if int(RUNNUM) < 17671 :
            momentum*=1./0.983
        TestVar+=1
        # print(run_num)
    if "Target AMU" in line :
        tgt_mass = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(tgt_mass)
    if "Spec Theta" in line :
        spec_theta = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(spec_theta)
    if "Beam Energy" in line :
        beam_e = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(beam_e)
    if "Run Length" in line :
        run_length = float(line.split(":")[1].split("sec")[0].strip())
        TestVar+=1
        # print(start_of_run)

    if "Accepted Physics Triggers" in line :
        evt_num = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(beam_e)

    if "Beam over threshold for" in line :
        tmp_line = (line.split(" for ")[1]).strip()
        beam_on_target = float(tmp_line.split("s,")[0])
        TestVar+=1
        # print(beam_on_target_time)
    if "Cut on BCM4 current of" in line :
        tmp_line = (line.split(" of ")[1]).strip()
        bcm_thrs = float((tmp_line.split(" uA")[0]).strip())
        TestVar+=1
        # print(bcm_thrs)

    if "BCM1 Beam Cut Current" in line :
        bcm1_cut_current = float(line.split(":")[1].split("uA")[0])
        TestVar+=1
        # print(bcm1_cut_current)
    if "BCM2 Beam Cut Current" in line :
        bcm2_cut_current = float(line.split(":")[1].split("uA")[0])
        TestVar+=1
        # print(bcm1_cut_current)
    if "BCM4A Beam Cut Current" in line :
        bcm4a_cut_current = float(line.split(":")[1].split("uA")[0])
        TestVar+=1
        # print(bcm1_cut_current)
    if "BCM4B Beam Cut Current" in line :
        bcm4b_cut_current = float(line.split(":")[1].split("uA")[0])
        TestVar+=1
        # print(bcm1_cut_current)
    if "BCM4C Beam Cut Current" in line :
        bcm4c_cut_current = float(line.split(":")[1].split("uA")[0])
        TestVar+=1
        # print(bcm1_cut_current)

    if "BCM1  Beam Cut Charge" in line :
        bcm1_cut_charge = float(line.split(":")[1].split("uC")[0])
        TestVar+=1
        # print(bcm1_cut_charge)
    if "BCM2  Beam Cut Charge" in line :
        bcm2_cut_charge = float(line.split(":")[1].split("uC")[0])
        TestVar+=1
        # print(bcm1_cut_charge)
    if "BCM4A Beam Cut Charge" in line :
        bcm4a_cut_charge = float(line.split(":")[1].split("uC")[0])
        TestVar+=1
        # print(bcm1_cut_charge)
    if "BCM4B Beam Cut Charge" in line :
        bcm4b_cut_charge = float(line.split(":")[1].split("uC")[0])
        TestVar+=1
        # print(bcm1_cut_charge)
    if "BCM4C Beam Cut Charge" in line :
        bcm4c_cut_charge = float(line.split(":")[1].split("uC")[0])
        TestVar+=1
        # print(bcm1_cut_charge)


    # trigger info
    if "Ps1_factor" in line :
        PS1 = float(line.split(" = ")[1].strip())
        TestVar+=1
        # print(PS1)
    if "Ps2_factor" in line :
        PS2 = float((line.split(" = ")[1]).strip())
        TestVar+=1
        # print(PS2)
    if "Ps3_factor" in line :
        PS3 = float((line.split(" = ")[1]).strip())
        TestVar+=1
        # print(PS3)

    # scaler counts
    if "%sTRIG1" % (specl) in line :
        T1_scaler = int((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T1_scaler)
    if "%sTRIG2" % (specl) in line :
        T2_scaler = int((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T2_scaler)
    if "%sTRIG3" % (specl) in line :
        T3_scaler = int((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T3_scaler)

    # scaler rates (same line, but get str within '[,]' brackets
    if "%sTRIG1" % (specl) in line :
        T1_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T1_scaler_rate)
    if "%sTRIG2" % (specl) in line :
        T2_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T2_scaler_rate)
    if "%sTRIG3" % (specl) in line :
        T3_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T3_scaler_rate)

    # live times
    if "Ps1 %s Computer Live Time" % (SPEC.upper()) in line :
        T1_accp = float(line.split(":")[1].split("%")[0].strip())
        T1_accp = int(T1_accp * T1_scaler / PS1)
        T1_accp_rate = float(T1_accp_rate / run_length)
        # print(T1_cpuLT)
    if "Ps2 %s Computer Live Time" % (SPEC.upper()) in line :
        T2_accp = float(line.split(":")[1].split("%")[0].strip())
        T2_accp = int(T2_accp * T2_scaler / PS2)
        T2_accp_rate = float(T2_accp_rate / run_length)
        # print(T2_cpuLT)
    if "Ps3 %s Computer Live Time" % (SPEC.upper()) in line :
        T3_accp = float(line.split(":")[1].split("%")[0].strip())
        T3_accp = int(T3_accp * T3_scaler / PS3)
        T3_accp_rate = float(T3_accp_rate / run_length)
        # print(T3_cpuLT)

    # tracking efficiency
    if "E SING FID TRACK EFFIC" in line :
        trk_eff = float(line.split(":")[1].split("+")[0].strip())
        # print(hms_trk_eff)

    # live times
    if "Ps1 %s Computer Live Time" % (SPEC.upper()) in line :
        T1_cpuLT = float(line.split(":")[1].split("%")[0].strip())
        # print(T1_cpuLT)
    if "Ps2 %s Computer Live Time" % (SPEC.upper()) in line :
        T2_cpuLT = float(line.split(":")[1].split("%")[0].strip())
        # print(T2_cpuLT)
    if "Ps1 %s Computer Live Time" % (SPEC.upper()) in line :
        T3_cpuLT = float(line.split(":")[1].split("%")[0].strip())
        # print(T3_cpuLT)

    if "Ps1 Total Live Time (EDTM)" in line :
        T1_tLT = float(line.split(":")[1].split("%")[0].strip())
        # print(T3_tLT)
    if "Ps2 Total Live Time (EDTM)" in line :
        T2_tLT = float(line.split(":")[1].split("%")[0].strip())
        # print(T3_tLT)
    if "Ps3 Total Live Time (EDTM)" in line :
        T3_tLT = float(line.split(":")[1].split("%")[0].strip())
        # print(T3_tLT)

#  run list was separated into sub-categories for ease of use and more flexibility if things need to be changed


# general run entry list
header_1    = ['runNo','momentum','theta','beam_e','tgt_amu','nevts','run_length']
gen_run_info = "%i %.3f %.3f %.3f %.3f %i %.3f" % \
               (run_num, momentum, spec_theta, beam_e, tgt_mass, evt_num, run_length)

header_2 = ['beam_ovr_thr','bcm_cut_thr','I_bcm1','I_bcm2','I_bcm4a','I_bcm4b','I_bcm4c','Q_bcm1','Q_bcm2','Q_bcm4a','Q_bcm4b','Q_bcm4c']
gen_bcm_info = "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f" % \
               (beam_on_target, bcm_thrs, bcm1_cut_current,  bcm2_cut_current, bcm4a_cut_current, bcm4b_cut_current, bcm4c_cut_current, bcm1_cut_charge,  bcm2_cut_charge, bcm4a_cut_charge, bcm4b_cut_charge, bcm4c_cut_charge)

# trigger info
# should probably define what these are more specifically later on . . . e.g., PS1 : SHMS 3/4 . . .
header_3   = ['PS1', 'PS2', 'PS3', 'sr_T1[kHz]', 'sr_T2[kHz]','sr_T3[kHz]', 'tr_T1[kHz]','tr_T2[kHz]','tr_T3[kHz]']
trig_info = "%i %i %i %.3f %.3f %.3f %i %i %i"  % \
            (PS1, PS2, PS3, T1_scaler_rate, T2_scaler_rate, T3_scaler_rate, T1_scaler, T2_scaler, T3_scaler)

# live time and trk_eff info
header_4   = ['T1_cpuLT', 'T1_tLT', 'T2_cpuLT', 'T2_tLT','T3_cpuLT', 'T3_tLT','TrkEff']
efficiency_info = "%.3f    %.3f    %.3f    %.3f    %.3f    %.3f         %.3f        " % \
           (T1_cpuLT, T1_tLT, T2_cpuLT, T2_tLT, T3_cpuLT, T3_tLT, trk_eff )

# combine headers
total_header = header_1 + header_2 + header_3 + header_4

# convert data strings to a list
gen_run_info_list    = gen_run_info.split()
gen_bcm_info_list    = gen_bcm_info.split()
trig_info_list       = trig_info.split()
efficiency_info_list = efficiency_info.split()

# combine lists
total_list = gen_run_info_list + gen_bcm_info_list + trig_info_list + efficiency_info_list

# close report file
xem_report.close()

# --- create / append data to cafe runlist .csv file ----------

os.system('mkdir -p UTIL_XEM/runlist')
#os.system('mkdir -p /home/cdaq/cyero/backup_runlist')

# check if run list exists, else create it and add a header
if os.path.isfile(fname_path):
    print (fname_path," exists !")

    if(overwrite_flag):
        with open(fname_path) as inf, open(temp_fname_path, 'w') as outf:
            reader = csv.reader(inf)
            writer = csv.writer(outf)
            for line in reader:
                #search for RUNNUM, and replace line when it finds it
                if(line[0]==str(RUNNUM)):
                    writer.writerow(total_list)
                else:
                    writer.writerow(line)
        # move temp.csv back to original .csv file
        os.system('cp %s %s '%(temp_fname_path, fname_path))

    else:
        with open(fname_path, "a") as f:
            writer = csv.writer(f,delimiter=",")
            writer.writerow(total_list)


else:
    print (fname_path," does NOT exist ! \n Will create it and add a header")

    with open(fname_path, "a") as f:
        writer = csv.writer(f,delimiter=",")
        writer.writerow(total_header)
        writer.writerow(total_list)

        f.close()



#fname_path_bkp='/home/cdaq/cyero/backup_runlist/cafe-2022_runlist_backup.csv'
#os.system('cp %s %s' % (fname_path, fname_path_bkp))
