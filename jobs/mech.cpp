/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet
   Subsystem Lead: Alex Potapov

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the Mechanical System on ConSat-1.
*/

#include "system.h"


MECHSystemState MECHSystemCheck(){
   MECHSystemState MECH_state;

   /*Flag state*/
   

   /*Pipe it out*/
   //sendDownPipe(MECH_state, system_pipe);

   return MECH_state;
}

//Function triggers every 60 minutes after deployment
//Software update will remove this job during LEOP
void deployAntenna(){
   //Check two flags to ensure we've deployed the antenna
   //If we've deployed the antenna and have had contact with the ground station
   //Then do nothing. Expect this code to be deleted with a software update.
   if (MF_ANTENNA_DEPLOYED){ 
      if (CF_GROUND_CONTACT) return;
   }

   //Set the GPIO high for antenna deployment
   //This sends 2A <>VERIFYTHEVALUE of current to the nichrome wire
   setGPIOHigh(antenna_deployment_GPIO_id);

   sleep(DEPLOYMENT_TIME);

   //Set the GPIO low for antenna deployment
   setGPIOLow(antenna_deployment_GPIO_id);
   
   //Set Antenna Deployed Flag high
   MECH_flags |= (1<<MF_ANTENNA_DEPLOYED);
}
