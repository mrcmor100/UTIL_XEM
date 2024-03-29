#! /usr/bin/python

# Stephen JD Kay - 19/08/21 - University of Regina
# Script to grab info from a report file, for use in the run list shell script
# This script scans every line of the report file to find the correct info

# C. Yero - May 26, 2022
# Modified to meet the needs of CaFe 2022 Experiment.
# The modified code creates a csv file and writes the
# pertinent information from the cafe output report to
# a .csv file on a run-by-run basis

   

# Import relevant packages
import sys, math, os, subprocess, csv
from datetime import datetime
import numpy as np
sys.path.insert(0, 'python/')

#if len(sys.argv)-1!=3:
#    print("Invalid number of arguments. \n "
#    "e.g., python reportfile.py <path/to/cafe

# user input
ANATYPE = sys.argv[1]
RUNNUM = sys.argv[2]
EVTNUM = sys.argv[3]

# construct generic report output file from the user input (whihc should have been generated)
cafe_report_path = "CAFE_OUTPUT/REPORT/cafe_%s_report_%s_%s.txt" % (ANATYPE, RUNNUM, EVTNUM)

#bcm_type = sys.argv[2]         # <entry_type> = "bcm_type", passed from run_cafe_prod.sh
cafe_report = open(cafe_report_path)


# define filenames
fname_path='UTILS_CAFE/runlist/cafe-2022_runlist.csv'                                                                                                                                         
temp_fname_path='UTILS_CAFE/runlist/temp.csv' # temporary file (for overwriting entry, if the user desires)                                                                                    
    


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
start_of_run=0
end_of_run=0
kin_type=0
evt_num=0
beam_e=0
tgt_name=0
tgt_mass=0
hms_p=0
hms_angle=0
shms_p=0
shms_angle=0
beam_on_target=0
bcm_thrs=0
bcm_current=0
bcm_charge=0

# luminosity-normalized real counts (Counts / integrated_luminosity)
integrated_luminosity = np.nan
lumiNorm_counts = np.nan

# good events counts (initialize to NaN for ease of use with python later on)
heep_singles      = np.nan
heep_singles_rate = np.nan
heep_real         = np.nan
heep_real_rate    = np.nan
MF_real           = np.nan
MF_real_rate      = np.nan
SRC_real          = np.nan
SRC_real_rate     = np.nan



# trigger info (only enabled triggers, i.e PS# != -1 will be written to kin file)
PS1=-1    # SHMS 3/4
PS2=-1    # SHMS EL-REAL
PS3=-1    # HMS 3/4
PS5=-1    # SHMS EL-REAL x HMS 3/4 ( this needs to be implemented after pionLT run ends in August 2022 )
PS6=-1    # HMS 3/4 x SHMS 3/4

T1_scaler=np.nan
T2_scaler=np.nan
T3_scaler=np.nan
T5_scaler=np.nan
T6_scaler=np.nan

T1_scaler_rate=np.nan
T2_scaler_rate=np.nan
T3_scaler_rate=np.nan
T5_scaler_rate=np.nan
T6_scaler_rate=np.nan

T1_accp=np.nan
T2_accp=np.nan
T3_accp=np.nan
T5_accp=np.nan
T6_accp=np.nan

T1_accp_rate=np.nan
T2_accp_rate=np.nan
T3_accp_rate=np.nan
T5_accp_rate=np.nan
T6_accp_rate=np.nan

# tracking efficiency
hms_trk_eff=np.nan
shms_trk_eff=np.nan

# daq live time
T1_cpuLT=np.nan
T1_tLT=np.nan

T2_cpuLT=np.nan
T2_tLT=np.nan

T3_cpuLT=np.nan
T3_tLT=np.nan

T5_cpuLT=np.nan
T5_tLT=np.nan

T6_cpuLT=np.nan
T6_tLT=np.nan


# SIMC cafe statistical goals 
simc_counts_goal          = np.nan
simc_charge_goal          = np.nan
simc_integrated_luminosity = np.nan
simc_lumiNorm_counts       = np.nan

TestVar = 0 # Counter to check the right number of variables have been set, 
for line in cafe_report:
    if (line[0]=="#"): continue;

    # general run information
    if "run_number" in line :
        run_num = int((line.split(":")[1]).strip())
        TestVar+=1
        # print(run_num)
    if "kin_type" in line :
        kin_type = (line.split(":")[1]).strip()
        TestVar+=1
        # print(kin_type)
    if "start_of_run" in line :
        start_of_run = (line.split("=")[1]).strip()
        #convert to datetime object
        start_of_run = datetime.strptime(start_of_run, '%Y-%m-%d %H:%M:%S')
        TestVar+=1
        # print(start_of_run)
    if "end_of_run" in line :
        end_of_run = (line.split("=")[1]).strip()
        #convert to datetime object
        end_of_run = datetime.strptime(end_of_run, '%Y-%m-%d %H:%M:%S') 
        TestVar+=1
        # print(end_of_run)
    if "events_replayed" in line :
        evt_num = int((line.split(":")[1]).strip())
        TestVar+=1
        # print(evt_num)
    if "beam_energy" in line :
        beam_e = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(beam_e)
    if "target_name:" in line :
        tgt_name = (line.split(":")[1]).strip()
        TestVar+=1
        # print(tgt_name)
    if "target_amu" in line :
        tgt_mass = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(tgt_mass)
    if "hms_h_momentum" in line :
        hms_p = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(hms_p)
    if "hms_h_angle" in line :
        hms_angle = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(hms_angle)
    if "shms_e_momentum" in line :
        shms_p = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(shms_p)
    if "shms_e_angle" in line :
        shms_angle = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(shms_angle)
    if "beam_on_target" in line :
        beam_on_target = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(beam_on_target_time)
    if "_Current_Threshold" in line :
        bcm_thrs = (line.split(":")[1]).strip()
        TestVar+=1
        # print(bcm_thrs)
    if "_Average_Current" in line :
        bcm_current = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(bcm_current)
    if "_Charge" in line :
        bcm_charge = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(bcm_charge)
    if "data_integrated_luminosity" in line :
        integrated_luminosity = float((line.split(":")[1]).strip()) 
        TestVar+=1
    if "data_lumiNorm_counts" in line :
        lumiNorm_counts = float((line.split(":")[1]).strip()) 
        TestVar+=1
    # good elastic, MF or SRC counts/rates
    if "heep_total_singles_counts" in line :
        heep_singles = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(heep_singles)
    if "heep_total_singles_rate" in line :
        heep_singles_rate = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(heep_singles_rate)
    if "heep_real_counts" in line :
        heep_real = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(heep_real)
    if "heep_real_rate" in line :
        heep_real_rate = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(heep_real_rate)
    if "MF_real_counts" in line :
        MF_real = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(MF_real)
    if "MF_real_rate" in line :
        MF_real_rate = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(MF_real_rate)
    if "SRC_real_counts" in line :
        SRC_real = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(SRC_real)
    if "SRC_real_rate" in line :
        SRC_real_rate = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(SRC_real_rate)

    # trigger info
    if "Ps1_factor" in line :
        PS1 = float(line.split(":")[1].strip())
        TestVar+=1
        # print(PS1)
    if "Ps2_factor" in line :
        PS2 = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(PS2)
    if "Ps3_factor" in line :
        PS3 = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(PS3)
    if "Ps5_factor" in line :
        PS5 = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(PS5)
    if "Ps6_factor" in line :
        PS6 = float((line.split(":")[1]).strip())
        TestVar+=1
        # print(PS6)
        
    # scaler counts
    if "T1_scaler" in line :
        T1_scaler = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T1_scaler)
    if "T2_scaler" in line :
        T2_scaler = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T2_scaler)
    if "T3_scaler" in line :
        T3_scaler = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T3_scaler)
    if "T5_scaler" in line :
        T5_scaler = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T5_scaler)
    if "T6_scaler" in line :
        T6_scaler = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T6_scaler)
        
    # scaler rates (same line, but get str within '[,]' brackets
    if "T1_scaler" in line :
        T1_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T1_scaler_rate)
    if "T2_scaler" in line :
        T2_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T2_scaler_rate)
    if "T3_scaler" in line :
        T3_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T3_scaler_rate)
    if "T5_scaler" in line :
        T5_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T5_scaler_rate)
    if "T6_scaler" in line :
        T6_scaler_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T6_scaler_rate)

    # accepted counts
    if "T1_accepted" in line :
        T1_accp = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T1_accp)
    if "T2_accepted" in line :
        T2_accp = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T2_accp)
    if "T3_accepted" in line :
        T3_accp = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T3_accp)
    if "T5_accepted" in line :
        T5_accp = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T5_accp)
    if "T6_accepted" in line :
        T6_accp = float((line.split(":")[1]).split("[")[0].strip())
        TestVar+=1
        # print(T6_accp)
        
    # accepted rates (same line, but get str within '[,]' brackets
    if "T1_accepted" in line :
        T1_accp_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T1_accp_rate)
    if "T2_accepted" in line :
        T2_accp_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T2_accp_rate)
    if "T3_accepted" in line :
        T3_accp_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T3_accp_rate)
    if "T5_accepted" in line :
        T5_accp_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T5_accp_rate)
    if "T6_accepted" in line :
        T6_accp_rate = float((line.split("[")[1]).split("kHz")[0].strip())
        TestVar+=1
        # print(T6_accp_rate)

    # tracking efficiency
    if "hms_had_track_eff" in line :
        hms_trk_eff = float(line.split(":")[1].split("+")[0].strip())
        # print(hms_trk_eff)
    if "shms_elec_track_eff" in line :
        shms_trk_eff = float(line.split(":")[1].split("+")[0].strip())
        # print(shms_trk_eff)
        
    # live times
    if "T1_cpuLT" in line :
        T1_cpuLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T1_cpuLT)
    if "T1_tLT" in line :
        T1_tLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T1_tLT)

    if "T2_cpuLT" in line :
        T2_cpuLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T2_cpuLT)
    if "T2_tLT" in line :
        T2_tLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T2_tLT)

    if "T3_cpuLT" in line :
        T3_cpuLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T3_cpuLT)
    if "T3_tLT" in line :
        T3_tLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T3_tLT)

    if "T5_cpuLT" in line :
        T5_cpuLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T5_cpuLT)
    if "T5_tLT" in line :
        T5_tLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T5_tLT)

    if "T6_cpuLT" in line :
        T6_cpuLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T6_cpuLT)
    if "T6_tLT" in line :
        T6_tLT = float(line.split(":")[1].split("+")[0].strip())
        # print(T6_tLT)

    # SIMC statistical goals
    if "simc_counts_goal" in line:
        simc_counts_goal = float((line.split(":")[1]).strip())
    if "simc_charge_goal" in line:
        simc_charge_goal = float((line.split(":")[1]).strip())
    if "simc_integrated_luminosity" in line:
        simc_integrated_luminosity = float((line.split(":")[1]).strip())
    if "simc_lumiNorm_counts" in line:
        simc_lumiNorm_counts = float((line.split(":")[1]).strip())

        
#  run list was separated into sub-categories for ease of use and more flexibility if things need to be changed


# general run entry list
header_1     = ['run\nnumber', 'start_run', 'end_run', 'kin\nstudy', 'beam_on_target\n[sec]', 'evts\nreplayed', 'beam\nenergy\n[GeV]', 'target', 'target\nmass\n[amu]', 'HMS_P\n[GeV/c]', 'HMS_Angle\n[deg]', 'SHMS_P\n[GeV/c]', 'SHMS_Angle\n[deg]', 'BCM4A\nthrs\n[uA]', 'BCM4A\ncurrent\n[uA]', 'BCM4A\ncharge\n[mC]', 'integrated\nluminosity\n[fb^-1]', 'lumiNorm_counts[fb]' ]
gen_run_info = "%i,            %s,           %s,           %s,         %.3f,          %i,       %.4f,     %s,        %.6f,      %.4f,   %.3f,       %.4f,    %.3f,        %s,        %.3f,         %.3f,          %.3f,                  %.4f " % \
               (run_num,  start_of_run,  end_of_run,    kin_type,  beam_on_target,  evt_num,   beam_e,  tgt_name,   tgt_mass,   hms_p,  hms_angle,  shms_p, shms_angle, bcm_thrs, bcm_current,  bcm_charge, integrated_luminosity,  lumiNorm_counts)


# trigger info
# should probably define what these are more specifically later on . . . e.g., PS1 : SHMS 3/4 . . .
header_2   = ['PS1', 'PS2', 'PS3', 'PS5', 'PS6', 'T1\nscaler_rates\n[kHz]', 'T2\nscaler_rates\n[kHz]','T3\nscaler_rates\n[kHz]','T5\nscaler_rates\n[kHz]','T6\nscaler_rates\n[kHz]', 'T1\naccp_rates\n[kHz]','T2\naccp_rates\n[kHz]','T3\naccp_rates\n[kHz]','T5\naccp_rates\n[kHz]','T6\naccp_rates\n[kHz]' ]
trig_info = "%i   %i   %i   %i   %i   %.3f            %.3f            %.3f            %.3f            %.3f            %.3f          %.3f          %.3f           %.3f           %.3f                        "  % \
            (PS1, PS2, PS3, PS5, PS6, T1_scaler_rate, T2_scaler_rate, T3_scaler_rate, T5_scaler_rate, T6_scaler_rate, T1_accp_rate, T2_accp_rate, T3_accp_rate,  T5_accp_rate,  T6_accp_rate                          )

# live time and trk_eff info
header_3   = ['T1_tLT', 'T2_tLT','T3_tLT','T5_tLT','T6_tLT','HMS\nTrkEff', 'SHMS\nTrkEff']
efficiency_info = "%.3f    %.3f    %.3f    %.3f    %.3f    %.3f         %.3f        " % \
           (T1_tLT, T2_tLT, T3_tLT, T5_tLT, T6_tLT, hms_trk_eff, shms_trk_eff )


# good event count info
header_4   = ['heep_singles\ncounts', 'heep_singles\nrates [Hz]', 'heep_coin\ncounts', 'heep_coin\nrates [Hz]', 'MF_real\ncounts', 'MF_real\nrates [Hz]', 'SRC_real\ncounts', 'SRC_real\nrates [Hz]']
good_evt_info = "%.2f           %.3f               %.2f       %.3f            %.2f     %.3f          %.2f      %.3f    " % \
                (heep_singles,  heep_singles_rate, heep_real, heep_real_rate, MF_real, MF_real_rate, SRC_real, SRC_real_rate )

# SIMC cafe statistical goals (full stats goal for each (target, kin_type) combo, e.g. (Be9, MF)
header_5             = ['simc_counts_goal', 'simc_charge_goal\n[mC]', 'simc_integrated\nluminosity\n[fb^-1]', 'simc_lumiNorm_counts[fb]', 'Comments']
simc_stats_goal_info = "%.3f                        %.3f                       %.4f                                 %.4f" % \
                       (simc_counts_goal,     simc_charge_goal,        simc_integrated_luminosity,              simc_lumiNorm_counts)

# combine headers
total_header = header_1 + header_2 + header_3 + header_4 + header_5


# read user comment (raw_input is required for python 2.7, else use input())
#comment = input("Please enter any relevant comments this run: \n")
comment=""
if( int(sys.version[0]) < 3 ):
    comment = raw_input("Please enter comments for run %s (press Enter to skip): " %(RUNNUM))
else:
    comment = input("Please enter comments for run %s (press Enter to skip) " %(RUNNUM))   

# clean user comment out of weird characters or spaces and replace them with '_'
specialChars = "!@#$%^&*()+={[]}|\:;,<>?/\" "

for specialChar in specialChars:
    comment = comment.replace(specialChar, '_')


# convert data strings to a list
gen_run_info_list    = gen_run_info.split(',')
trig_info_list       = trig_info.split()
efficiency_info_list = efficiency_info.split()
good_evt_info_list   = good_evt_info.split()
simc_stats_goal_info_list = simc_stats_goal_info.split()

# combine lists
total_list = gen_run_info_list + trig_info_list + efficiency_info_list + good_evt_info_list + simc_stats_goal_info_list

# append user comments to list
total_list.append(comment)

# close report file
cafe_report.close()

# --- create / append data to cafe runlist .csv file ----------

os.system('mkdir -p UTILS_CAFE/runlist') 
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
