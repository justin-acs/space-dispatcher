/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet
   Subsystem Lead: Justin Jean-pierre

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the Attitude Determination and Control System on ConSat-1.
*/

#include "system.h"

CDHSystemState CDHSystemCheck(){
   CDHSystemState CDH_state;
  
   /*Take readings*/
   //Check thermistors
   CDH_state.EB_top_temp = readThermistor(EB_top_thermistor_id);
   CDH_state.EB_bottom_temp = readThermistor(EB_bottom_thermistor_id);

   //Check data (?) - i.e. corruption, backups, performance history etc.

   //Check Q6 (?)
   
   /*Pipe it out*/
   //sendDownPipe(current_COMS_state, system_pipe);
  
   return CDH_state;
}