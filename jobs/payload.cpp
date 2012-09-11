/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet
   Subsystem Lead: Michelle Boyce

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the Payload System on ConSat-1.
*/
   
#include "system.h"

/*Subsystem Check*/
PAYSystemState PAYSystemCheck(){
    PAYSystemState PAY_state;

   /*Take readings*/
    //Check Thermistors
   PAY_state.GT_temp = readThermistor(GT_thermistor_id);
   PAY_state.GT_ambient_temp = readThermistor(GT_ambient_thermistor_id);

   //Check IV Sensors
   PAY_state.GT_V_drop = readVSensor(GT_V_drop_id);

   /*Pipe it out*/
   //sendDownPipe(PAY_state, system_pipe);

   return PAY_state;
}




/*Geiger Tube Events*/
   //activate geiger tube
   //read samples at GT_EVENT_SAMPLE_RATE
   //call Geiger Tube Spectra


/*Geiger Tube Spectra*/
   //timestamp current geiger tube samples in memory
   //save geiger tube samples to SSD and mark for transmission
   //(toggle) mark raw data slice for transmission
   //clear geiger tube memory space
   //call Geiger Tube Events 
