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

  unsigned char buff[6];
  unsigned short raw[3];
  unsigned char reg = MAGN_DATAREG;
  int i = 0;
  
  // Select device
  i2cSetAddress(MAGN_ADDRESS);
   
  // Read 6 bytes
  while(i<6&&reg<MAGN_DATAREG+6){
    
    buff[i] = i2cReadByte(reg);
    //printf("magn[%x]:%x ",reg,buff[i]);
    //usleep(5000);
    reg++;
    i++;
    
  }
  
  if (i == 6)  // All bytes received?
  {
    //ints are stored as 2-byte 2s-complements on an arduino so casting to int is sufficent to
    //retrieve 16bit 2s-complement values from sensor registers on an arduino. 
    //magnetom[0] = -1*((((int) buff[0]) << 8) | buff[1]);         // X axis (internal sensor x axis)
    //magnetom[1] = -1*((((int) buff[4]) << 8) | buff[5]);  // Y axis (internal sensor -y axis)
    //magnetom[2] = -1*((((int) buff[2]) << 8) | buff[3]);  // Z axis (internal sensor -z axis)
    
    // MSB byte first, then LSB; Y and Z reversed: X, Z, Y
    raw[0] = ((buff[0]) << 8) | buff[1];    // X axis (internal sensor -y axis)
    raw[1] = ((buff[4]) << 8) | buff[5];    // Y axis (internal sensor -x axis)
    raw[2] = ((buff[2]) << 8) | buff[3];    // Z axis (internal sensor -z axis)
    
    //Manual 2s-Complement conversion
    //TODO:Make this branchless
    int k;
    for(k=0;k<3;k++){
        //Convert from twos complement
        if((raw[k] >> 15) == 1){
     raw[k] = ~raw[k] + 1;
	  mag_readings[k] = raw[k];
	  mag_readings[k] *= -1;
	  //printf("negative");
        }else{
	  mag_readings[k] = raw[k];
	}
        //XXXX is the maximum value of an X-bit signed register
        //TODO: Scale based on Max value being read.
        //magnetom[k] = (float)16 * (magnetom[k]/(0x1FF));
	     //printf("\n%f\n",mag_readings[k]);
    }
    
   // printf("magn: %f %f %f\n",mag_readings[0],mag_readings[1],mag_readings[2]);
  }
  else
  {
      printf("!ERR: reading magnetometer");
  }
   
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