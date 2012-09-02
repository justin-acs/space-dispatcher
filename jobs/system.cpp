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


/*Health Check*/
//Triggered by Dispatcher every 5 minutes
void systemCheckout(){
   SystemState current_system_state;

   //Check all subsystems
   current_system_state.ACS_state = ACSSystemCheck();
   current_system_state.CDH_state = CDHSystemCheck();
   current_system_state.COMS_state = COMSSystemCheck();
   current_system_state.MECH_state = MECHSystemCheck();
   current_system_state.PAY_state = PAYSystemCheck();
   current_system_state.POW_state = POWSystemCheck();

    
    cout << "System has checked out" << endl;
   //Save data to file
   /*IS THIS THE BEST WAY TO SAVE THE SYSTEM STATE?*/

}
 //||FIXME: NOT YET IMPLEMENTED||
float readThermistor(int thermistor_id){
    
    /*Define ADC and Pin*/
    int ADC; //ADC corresponding to selected thermistor
    int pin; //Pin corresponding to selected thermistor
    switch (thermistor_id) {
        case antenna_thermistor_id:
            ADC = 0x24;
            pin = 2;
            break;
        case EB_top_thermistor_id:
            ADC = 0x24;
            pin = 7;
            break;
        case EB_bottom_thermistor_id:
            ADC = 0x24;
            pin = 8;
            break;
        case GT_thermistor_id:
            ADC = 0x24;
            pin = 5;
            break;
        case GT_ambient_thermistor_id:
            ADC = 0x24;
            pin = 6;
            break;
        case battery_thermistor_id_1:
            ADC = 0x24;
            pin = 3;
            break;
        case battery_thermistor_id_2:
            ADC = 0x24;
            pin = 4;
            break;
        case solar_panel_thermistor_id_1:
            ADC = 0x23;
            pin = 1;
            break;
        case solar_panel_thermistor_id_2:
            ADC = 0x23;
            pin = 2;
            break;
        case solar_panel_thermistor_id_3:
            ADC = 0x23;
            pin = 3;
            break;
        case solar_panel_thermistor_id_4:
            ADC = 0x23;
            pin = 4;
            break;
        case solar_panel_thermistor_id_5:
            ADC = 0x23;
            pin = 5;
            break;
        case solar_panel_thermistor_id_6:
            ADC = 0x23;
            pin = 6;
            break;
        case solar_panel_thermistor_id_7:
            ADC = 0x23;
            pin = 7;
            break;
        case solar_panel_thermistor_id_8:
            ADC = 0x23;
            pin = 8;
            break;
        default:
            break;
    }
    
    /*Set Registers*/
    
    
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