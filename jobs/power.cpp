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

/*Subsystem Check*/
POWSystemState POWSystemCheck(){
   POWSystemState POW_state;

   /*Take readings*/
    //Check Thermistors
   for (int i=0; i<8; i++) 
      POW_state.solar_panel_temps[i] = readThermistor(SOLAR_PANEL_THERMISTOR_IDS[i]);

   for (int i=0; i<2; i++) 
      POW_state.battery_temps[i] = readThermistor(BATTERY_THERMISTOR_IDS[i]);

   //Check IV Sensors
   POW_state.bus_15v_I = readISensor(bus_15v_IV_sensor_id);
   POW_state.bus_5v_I = readISensor(bus_5v_IV_sensor_id);
   POW_state.bus_3_3v_I = readISensor(bus_3_3v_IV_sensor_id);
   POW_state.battery_I = readISensor(battery_IV_sensor_id);

   POW_state.bus_15v_V = readVSensor(bus_15v_IV_sensor_id);
   POW_state.bus_5v_V = readVSensor(bus_5v_IV_sensor_id);
   POW_state.bus_3_3v_V = readVSensor(bus_3_3v_IV_sensor_id);
   POW_state.battery_V = readISensor(battery_IV_sensor_id);

   //Check Battery Status
   POW_state.battery_charge = readBatteryCharge(POW_state.bus_5v_V);

   /*Pipe it out*/
   //sendDownPipe(POW_state, SYSTEM_PIPE);

   return POW_state;
}


//||FIXME: NOT YET IMPLEMENTED||
float readBatteryCharge(float battery_voltage){
    float batteryCharge;
    return batteryCharge;
}


   //check related thermistors
   //check current sensors
   //check voltage sensors
   //relate battery voltage to battery capacity

/*Enable 3.3V Line*/
   //Toggle GPIO
   //||think about redundancy

/*Enable 15V Line*/
   //Toggle GPIO 
   //||think about redundancy

/*Interrupt on Line Failure*/
   //Power off warning (or brownout or overcurrent) for each 3.3v, 5v or 15v
   //Save all telemetry ASAP
   //Save all data from subsystems connected to failing line

