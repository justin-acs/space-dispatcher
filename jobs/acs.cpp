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

   Triggers
*/

#include "system.h"

ACSSystemState ACSSystemCheck(){
   ACSSystemState ACS_state;
   
   /*Take readings*/
   //Get all Magnetometer readings since last system check
   ACS_state.mag = getMagReadings(); /*GET CODE FROM ACS*/

   //Get current position from lookuptable
   ACS_state.position = getPosition(time(NULL)); /*ASK MATHIAS TO IMPLEMENT*/

   //Use position and time to get attitude
   MagXYZ reference_mag = getIGRF(ACS_state.position); /*GET CODE FROM ACS*/
   ACS_state.attitude = getAttitude(ACS_state.mag, reference_mag);

   /*Pipe it out*/
   //sendDownPipe(ACS_state, system_pipe);

   return ACS_state;
}

//||FIXME: NOT YET IMPLEMENTED||
MagXYZ getMagReadings(){
    MagXYZ mag_readings;
    return mag_readings;
}


//||FIXME: NOT YET IMPLEMENTED||
ECIposition getPosition(time_t time){
    ECIposition position;
    return position;
}

//||FIXME: NOT YET IMPLEMENTED||
MagXYZ getIGRF(ECIposition position){
    MagXYZ IGRF_mag;
    return IGRF_mag;
}

//||FIXME: NOT YET IMPLEMENTED||
EulerAngle getAttitude(MagXYZ current_mag, MagXYZ reference_mag){
    EulerAngle attitude;
    return attitude;
}