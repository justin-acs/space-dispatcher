/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the General Systems on ConSat-1.
*/

#include "system.h"
#include "jobs.h"
#include <vector>
#include <signal.h>
#include <sys/wait.h>
using namespace std;


vector<job*> g_allJobs;

void initializeJobObjects() {    
    //vector<job*> allJobs;
    cout << "Dispatcher: Ini job" << endl;
    job* temp;

    temp = new job(power_job,"/home/CODE/jobs/power_job.exe");
    g_allJobs.push_back(temp);

    temp = new job(mech_job,"/home/CODE/jobs/mech_job.exe");
    g_allJobs.push_back(temp);  

    temp = new job(acs_job,"/home/CODE/jobs/acs_job.exe");
    g_allJobs.push_back(temp);  

    temp = new job(coms_job,"/home/CODE/jobs/coms_job.exe");
    g_allJobs.push_back(temp);  

    temp = new job(cdh_job,"/home/CODE/jobs/cdh_job.exe");
    g_allJobs.push_back(temp);  

    temp = new job(payload_job,"/home/CODE/jobs/payload_job.exe");
    g_allJobs.push_back(temp);  

    temp = new job(system_job,"/home/CODE/jobs/system_job.exe");
    g_allJobs.push_back(temp);      
}

/*Health Check*/
//Triggered by Dispatcher every 5 minutes
void systemCheckout(){
   cout << "Dispatcher: sys checkout" << endl;
   for(int i = 0; i < g_allJobs.size(); i++){
       pid_t jobPid;
       
       jobPid = fork();
       
       if (jobPid == 0){
           execl(g_allJobs[i]->path.c_str(),
                 g_allJobs[i]->path.c_str(),  
                 (char *)NULL);  
           cout << "Dispatcher: unicorn child created " << getpid() << endl;        
           exit(0);
       }
       else{
           g_allJobs[i]->pid = jobPid;
       }
       sleep(15);
       
        //should be enough for the job to finish
       if(!(jobFinished(jobPid))){
           killJob(jobPid);
           
           if(isJobBezerk(jobPid)){
               rebootQ6();
           }
        }
    
   }
   
    cout << "Dispatcher: System health requires doctor assistance!" << endl;
}
int jobFinished(pid_t pid){
    if((kill(pid, 0)) < 0){
        return true;
    }
    else{
        return false;
    }
}

void killJob(pid_t pid){
    cout << "Dispatcher: killing job " << pid << endl;
    kill(pid, SIGKILL);
    int status;
    
    //find a way to unwait if child does not terminate
    //find a way to totally kill zombies for the real
    waitpid(pid, &status, WUNTRACED | WCONTINUED);
    //wait();
 }

int isJobBezerk(pid_t pid){
    //sigkill did nothing
    return !jobFinished(pid);
}

void rebootQ6() {
    cout << "Dispatcher: Would be rebooting now.." << endl;
    //system("reboot -n -f");    
    
    //if (!rebooted) { autodestroy(); }
}


 //||FIXME: NOT YET IMPLEMENTED||
float readThermistor(int thermistor_id){
    
    /*Define ADC and Pin*/
    int ADC; //ADC corresponding to selected thermistor
    ADC = (thermistor_id <= 0x07) ?  0x24 : 0x23;
    switch (thermistor_id) {
        case antenna_thermistor_id:
            ADC_7998_configuration_register.set(CR_d5);
            break;
        case EB_top_thermistor_id:
            ADC_7998_configuration_register.set(CR_d10);
            break;
        case EB_bottom_thermistor_id:
            ADC_7998_configuration_register.set(CR_d11);
            break;
        case GT_thermistor_id:
            ADC_7998_configuration_register.set(CR_d8);
            break;
        case GT_ambient_thermistor_id:
            ADC_7998_configuration_register.set(CR_d9);
            break;
        case battery_thermistor_id_1:
            ADC_7998_configuration_register.set(CR_d6);
            break;
        case battery_thermistor_id_2:
            ADC_7998_configuration_register.set(CR_d7);
            break;
        case solar_panel_thermistor_id_1:
            ADC_7998_configuration_register.set(CR_d1);
            break;
        case solar_panel_thermistor_id_2:
            ADC_7998_configuration_register.set(CR_d2);
            break;
        case solar_panel_thermistor_id_3:
            ADC_7998_configuration_register.set(CR_d3);
            break;
        case solar_panel_thermistor_id_4:
            ADC_7998_configuration_register.set(CR_d4);
            break;
        case solar_panel_thermistor_id_5:
            ADC_7998_configuration_register.set(CR_d5);
            break;
        case solar_panel_thermistor_id_6:
            ADC_7998_configuration_register.set(CR_d6);
            break;
        case solar_panel_thermistor_id_7:
            ADC_7998_configuration_register.set(CR_d7);
            break;
        case solar_panel_thermistor_id_8:
            ADC_7998_configuration_register.set(CR_d8);
            break;
        default:
            //set all bits to read all values
            ADC_7998_configuration_register.set(CR_d1);
            ADC_7998_configuration_register.set(CR_d2);
            ADC_7998_configuration_register.set(CR_d3);
            ADC_7998_configuration_register.set(CR_d4);
            ADC_7998_configuration_register.set(CR_d5);
            ADC_7998_configuration_register.set(CR_d6);
            ADC_7998_configuration_register.set(CR_d7);
            ADC_7998_configuration_register.set(CR_d8);
            break;
    }
    
    /*Set Registers*/
    ADC_7998_configuration_register.set(CR_d3); //enable filtering by default
    
    
    /*Read Registers*/
    //||DEBUG||
    cout << "Dispatcher: Config register: " << ADC_7998_configuration_register << endl;
    cout << "Dispatcher: Result register: " <<ADC_7998_conversion_result_register << endl;
    
    return 1;
}

//||FIXME: NOT YET IMPLEMENTED||
float readISensor(int IV_sensor_id){
    return 1;
}

//||FIXME: NOT YET IMPLEMENTED||
float readVSensor(int IV_sensor_id){ 
    return 1;
}
 
void setGPIOHigh(int GPIO_id){
    char system_command[300];
    
    //ensure pin is active low
    sprintf(system_command, "echo '1' > pin%i/active_low", GPIO_id);
    system(system_command);
    
    //ensure pin is output
    sprintf(system_command, "echo 'out' > pin%i/direction", GPIO_id);
    system(system_command);
    
    //set pin value active (0, since it's active low)
    sprintf(system_command, "echo '0' > pin%i/active_low", GPIO_id);
    system(system_command);
    
    return;
}
        
void setGPIOLow(int GPIO_id){
    char system_command[300];
    
    //ensure pin is active low
    sprintf(system_command, "echo '1' > pin%i/active_low", GPIO_id);
    system(system_command);
    
    //ensure pin is output
    sprintf(system_command, "echo 'out' > pin%i/direction", GPIO_id);
    system(system_command);
    
    //set pin value inactive (1, since it's active low)
    sprintf(system_command, "echo '1' > pin%i/active_low", GPIO_id);
    system(system_command);

    return;
}

void sendDownPipe(SystemState current_state, string SYSTEM_PIPE ){
    return;
}
