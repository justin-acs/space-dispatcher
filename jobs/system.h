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
_________________________________________________________________
|////////////////////////////////////////////////////////////////|
|//////////////////////TABLE OF CONTENTS/////////////////////////|
| [0000] INCLUDES                                                |
|        [0100] SYSTEM                                           |
|        [0200] ACS                                              |
|        [0300] COMMUNICATIONS                                   |
|        [0400] C&DH                                             |
|        [0500] MECHANICAL                                       |
|        [0600] PAYLOAD                                          |
|        [0700] POWER                                            |
| [1000] DEFINES                                                 |
|        [1100] SYSTEM                                           |
|               [1110] THERMISTOR IDS                            |
|               [1120] IV SENSOR IDS                             |
|               [1130] GPIO IDS                                  |
|        [1200] ACS                                              |
|        [1300] COMMUNICATIONS                                   |
|        [1400] C&DH                                             |
|        [1500] MECHANICAL                                       |
|        [1600] PAYLOAD                                          |
|        [1700] POWER                                            |
| [2000] STRUCTS                                                 |
|        [2100] SYSTEM                                           |
|               [2110] SYSTEM STATES                             |
|        [2200] ACS                                              |
|        [2300] COMMUNICATIONS                                   |
|        [2400] C&DH                                             |
|        [2500] MECHANICAL                                       |
|        [2600] PAYLOAD                                          |
|        [2700] POWER                                            |
| [3000] ENUMS & FLAGS                                           |
|        [3100] SYSTEM                                           |
|        [3200] ACS                                              |
|               [3110] SYSTEM                                    |
|        [3300] COMMUNICATIONS                                   |
|        [3400] C&DH                                             |
|        [3500] MECHANICAL                                       |
|        [3600] PAYLOAD                                          |
|        [3700] POWER                                            |
| [4000] CONSTANTS                                               |
|        [4100] SYSTEM                                           |
|        [4200] ACS                                              |
|        [4300] COMMUNICATIONS                                   |
|        [4400] C&DH                                             |
|        [4500] MECHANICAL                                       |
|        [4600] PAYLOAD                                          |
|        [4700] POWER                                            |
| [5000] FUNCTIONS                                               |
|        [5100] SYSTEM                                           |
|               [5110] SYSTEM CHECKS                             |
|               [5120] DRIVERS                                   |
|        [5200] ACS                                              |
|        [5300] COMMUNICATIONS                                   |
|        [5400] C&DH                                             |
|        [5500] MECHANICAL                                       |
|        [5600] PAYLOAD                                          |
|        [5700] POWER                                            |
|////////////////////////////////////////////////////////////////|
_________________________________________________________________
*/


#ifndef SYS_H_INCLUDED
#define SYS_H_INCLUDED



/*----------------------------------------------------------------
----------------------****[0000]INCLUDES****----------------------
----------------------------------------------------------------*/

//----------------------------------------------------[0100]SYSTEM

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <bitset>
#include <iomanip>
#include <limits.h>
#include <string.h>
#include <time.h>

//-------------------------------------------------------[0200]ACS
//--------------------------------------------[0300]COMMUNICATIONS
//------------------------------------------------------[0400]C&DH
//------------------------------------------------[0500]MECHANICAL
//---------------------------------------------------[0600]PAYLOAD
//-----------------------------------------------------[0700]POWER

using namespace std;



/*-----------------------------------------------------------------
-----------------------****[1000]DEFINES****-----------------------
-----------------------------------------------------------------*/

//----------------------------------------------------[1100]SYSTEM

/*[1110] THERMISTOR IDS*/
#define antenna_thermistor_id 0x01 
#define EB_top_thermistor_id 0x02 
#define EB_bottom_thermistor_id 0x3 
#define GT_thermistor_id 0x04
#define GT_ambient_thermistor_id 0x05
#define battery_thermistor_id_1 0x06
#define battery_thermistor_id_2 0x07
#define solar_panel_thermistor_id_1 0x08
#define solar_panel_thermistor_id_2 0x09
#define solar_panel_thermistor_id_3 0x10
#define solar_panel_thermistor_id_4 0x11
#define solar_panel_thermistor_id_5 0x12
#define solar_panel_thermistor_id_6 0x13
#define solar_panel_thermistor_id_7 0x14
#define solar_panel_thermistor_id_8 0x15


//||FIXEME:STUB! GET THE SENSOR IDS!||
/*[1120] IV SENSOR IDS*/
#define GT_V_drop_id 1
#define solar_panel_IV_sensor_id_1 1
#define solar_panel_IV_sensor_id_2 2
#define solar_panel_IV_sensor_id_3 3
#define solar_panel_IV_sensor_id_4 4
#define solar_panel_IV_sensor_id_5 5
#define solar_panel_IV_sensor_id_6 6
#define solar_panel_IV_sensor_id_7 7
#define solar_panel_IV_sensor_id_8 8
#define bus_15v_IV_sensor_id 9
#define bus_5v_IV_sensor_id 10
#define bus_3_3v_IV_sensor_id 11
#define battery_IV_sensor_id 12


/*[1130] GPIO IDS*/
#define antenna_deployment_GPIO_id 1 //||FIXEME:STUB! FIND THE REAL PIN!||
#define transceiver_enable_GPIO_id 2 //||FIXEME:STUB! FIND THE REAL PIN!||
#define payload_enable_GPIO_id 3 //||FIXEME:STUB! FIND THE REAL PIN!||
#define power_interrupt_GPIO_id 4 //||FIXEME:STUB! FIND THE REAL PIN!||


//-------------------------------------------------------[1200]ACS

//--------------------------------------------[1300]COMMUNICATIONS

//User-defined constants
#define HE_UART_TX 17
#define HE_UART_RX 18
#define COMMAND_TYPE_I 0x10      //For data entering the radio
#define COMMAND_TYPE_O 0x20      //For data leaving the radio
#define HEADER_SIZE 8

//COMMAND_TYPE_I Op Codes
#define I_NO_OP 0x1001           //Simply increment command processing counter
#define I_RESET 0x1002           //Reset radio processors and systems
#define I_TRANSMIT 0x1003        //Send n bytes to radio
#define I_GET_CONFIG 0x1005      //Get radio configuration
#define I_SET_CONFIG 0x1005      //Set radio configuration
#define I_BUFFER_QUERY 0x1006    //Request # of buffers in transmission queue
#define I_TELEMETRY 0x100A       //query a telemetry frame

//COMMAND_TYPE_O Op Codes
#define O_NO_OP 0x2001           //Acknowledge No-Op
#define O_RESET 0x2002           //Acknowledge radio processors and systems reset
#define O_TRANSMIT 0x2003        //Acknowledge valid transmit command   
#define O_GET_CONFIG 0x2004      //Response to read radio configuration (returns struct of radio config)
#define O_SET_CONFIG 0x2005      //Acknowledge radio configuration set
#define O_BUFFER_QUERY 0x2006    //Response to buffer query (returns depth of transmission buffer)
#define O_TELEMETRY 0x200A       //query telemetry points

//------------------------------------------------------[1400]C&DH
//------------------------------------------------[1500]MECHANICAL
//---------------------------------------------------[1600]PAYLOAD
//-----------------------------------------------------[1700]POWER



/*-----------------------------------------------------------------
-----------------------****[2000]STRUCTS****-----------------------
-----------------------------------------------------------------*/


//-------------------------------------------------------[2200]ACS
//MagXYZ: magnitude of magnetic field in 3 axes
typedef struct {
   float mag_x;
   float mag_y;
   float mag_z;
} MagXYZ;

//ECIposition: Earth-Centered Inertial position in 3 axes
typedef struct {
   float r_x;
   float r_y;
   float r_z;
} ECIposition;

//EulerAngle: Euler angle representation of attitude using 3 3x3 matrices
typedef struct {
   float A_x[3][3];
   float A_y[3][3];
   float A_z[3][3];
} EulerAngle;

//--------------------------------------------[2300]COMMUNICATIONS

//User-defined transceiver command
typedef struct {
   uint8_t command_type;
   uint16_t command;
   uint8_t * payload_data;
   uint16_t payload_size;
} Transceiver_Command;

//Astrodev-specified transceiver configuration
typedef struct {
   uint8_t radio_interface_mode;//Radio Interface mode (default AX.25 = 0x01) 
   uint32_t radio_time;//Radio Time (default 0x0000)
   uint8_t interface_baud_rate;//Radio Interface Baud Rate (default 9600=0x03) 
   uint8_t tx_rf_baud_rate; //Radio TX RF Baud Rate (default 9600=0x02) 
   uint8_t rx_rf_baud_rate; //Radio RX RF Baud Rate (default 9600=0x02) 
   uint8_t rx_buff_size; //Rx Buffer Size (default 0x06)
   uint8_t tx_buff_size; //Tx Buffer Size (default 0x04)
   uint8_t tx_power_amp_level; //Tx Power Amp level (default max = 0x0A)
   uint8_t rx_mode; //Channel Rx Mode (do not implement)
   uint8_t tx_mode; //Channel Tx Mode (do not implement)
   uint32_t rx_freq; //Channel Rx Frequency (default radio specific)
   uint32_t tx_freq; //Channel Tx Frequency (default radio specific)
   unsigned char source[6]; //AX25 Mode Source Call Sign (default NOCALL) 
   unsigned char destination[6]; //AX25 Mode Destination Call Sign (default NOCALL)
   uint8_t tx_delay; //AX25 Mode Tx Delay (default 10ms)
   uint8_t tx_delay_end; //AX25 Mode Tx Delay End (default 100ms)
   uint8_t pid; //AX25 Mode PID (default 0x60)
   uint8_t binary_encode_method; //Binary Mode Encoding Method
   uint8_t binary_scrambling_method; //Binary Mode Scrambling Function
   uint8_t binary_flag_sync_byte; //Binary Mode Flag or Synch Bytes
   uint8_t binary_checksum_method; //Binary Mode Checksum method
   uint8_t spare;
} RadioConfiguration;

//Astrodev-specified transceiver configuration
typedef struct {
    uint8_t radio_interface_mode;//Radio Interface mode (default AX.25 = 0x01)
    uint32_t radio_time;//Radio Time (default 0x0000)
    uint8_t interface_baud_rate;//Radio Interface Baud Rate (default 9600=0x03)
    uint8_t tx_rf_baud_rate; //Radio TX RF Baud Rate (default 9600=0x02)
    uint8_t rx_rf_baud_rate; //Radio RX RF Baud Rate (default 9600=0x02)
    uint8_t rx_buff_size; //Rx Buffer Size (default 0x06)
    uint8_t tx_buff_size; //Tx Buffer Size (default 0x04)
    uint8_t tx_power_amp_level; //Tx Power Amp level (default max = 0x0A)
    uint8_t rx_mode; //Channel Rx Mode (do not implement)
    uint8_t tx_mode; //Channel Tx Mode (do not implement)
    uint32_t rx_freq; //Channel Rx Frequency (default radio specific)
    uint32_t tx_freq; //Channel Tx Frequency (default radio specific)
    unsigned char source[6]; //AX25 Mode Source Call Sign (default NOCALL)
    unsigned char destination[6]; //AX25 Mode Destination Call Sign (default NOCALL)
    uint8_t tx_delay; //AX25 Mode Tx Delay (default 10ms)
    uint8_t tx_delay_end; //AX25 Mode Tx Delay End (default 100ms)
    uint8_t pid; //AX25 Mode PID (default 0x60)
    uint8_t binary_encode_method; //Binary Mode Encoding Method
    uint8_t binary_scrambling_method; //Binary Mode Scrambling Function
    uint8_t binary_flag_sync_byte; //Binary Mode Flag or Synch Bytes
    uint8_t binary_checksum_method; //Binary Mode Checksum method
    uint8_t spare;
} RadioTelemetry;


//------------------------------------------------------[2400]C&DH
//------------------------------------------------[2500]MECHANICAL
//---------------------------------------------------[2600]PAYLOAD
//-----------------------------------------------------[2700]POWER

//----------------------------------------------------[2100]SYSTEM

/*[2110]SYSTEM STATES*/

typedef struct {
    MagXYZ mag;
    ECIposition position;
    EulerAngle attitude;
} ACSSystemState;

typedef struct {
    float antenna_temp;
    RadioConfiguration radio_config;
    RadioTelemetry radio_telemetry; //||FIXME: MAKE THIS TYPE||
} COMSSystemState;

typedef struct {
    float EB_top_temp;
    float EB_bottom_temp;
} CDHSystemState;

//||FIXME: CHANGE TO MECH FLAGS||
typedef struct {
    float antenna_deployment_I;
    float antenna_deployment_V;
} MECHSystemState;

typedef struct {
    float solar_panel_temps[8];
    float battery_temps[2];
    float solar_panel_Is[8], solar_panel_Vs[8];
    float bus_15v_I, bus_15v_V;
    float bus_5v_I, bus_5v_V;
    float bus_3_3v_I, bus_3_3v_V;
    float battery_I, battery_V;
    float battery_charge;
} POWSystemState;

typedef struct {
    float GT_ambient_temp;
    float GT_temp;
    float GT_V_drop;
} PAYSystemState;

typedef struct {
    ACSSystemState ACS_state;
    CDHSystemState CDH_state;
    COMSSystemState COMS_state;
    MECHSystemState MECH_state;
    PAYSystemState PAY_state;
    POWSystemState POW_state;
} SystemState;



/*---------------------------------------------------------------
------------------****[3000]ENUMS & FLAGS****--------------------
---------------------------------------------------------------*/

//---------------------------------------------------[3100]SYSTEM
//------------------------------------------------------[3200]ACS
//-------------------------------------------[3300]COMMUNICATIONS

enum COMS_flag_enum{
    CF_GROUND_CONTACT = (0<<0) //initially 0
};

static unsigned int COMS_flags;



//-----------------------------------------------------[3400]C&DH
//-----------------------------------------------[3500]MECHANICAL

enum MECH_flags{
    MF_ANTENNA_DEPLOYED = (0<<0) //initially 0
};

static unsigned int MECH_flags;


//--------------------------------------------------[3600]PAYLOAD
//----------------------------------------------------[3700]POWER


/*----------------------------------------------------------------
---------------------****[4000]CONSTANTS****----------------------
----------------------------------------------------------------*/

//----------------------------------------------------[4100]SYSTEM

const static int HEALTH_CHECKOUT_RATE = 300; //in seconds
const static string SYSTEM_PIPE = "Pipename.pipe"; //||FIXME: DEFINE PIPES!||

const static int SOLAR_PANEL_THERMISTOR_IDS[8] = {
   solar_panel_thermistor_id_1,
   solar_panel_thermistor_id_2,
   solar_panel_thermistor_id_3,
   solar_panel_thermistor_id_4,
   solar_panel_thermistor_id_5,
   solar_panel_thermistor_id_6,
   solar_panel_thermistor_id_7,
   solar_panel_thermistor_id_8
};

const static int BATTERY_THERMISTOR_IDS[2] = {
   battery_thermistor_id_1,
   battery_thermistor_id_2
};


//-------------------------------------------------------[4200]ACS

//--------------------------------------------[4300]COMMUNICATIONS

const static float SNR_LIMIT = 1; //in dBm ||FIXME: FIGURE OUT WHAT THE LIMIT IS||
const static char SYNC_CHARACTERS[2] = {'H','e'};

const static RadioConfiguration DEFAULT_RADIO_CONFIG = {
   0x00,//Radio Interface mode = binary 
   0x0000,//Radio Time = ?????????
   0x02,//Radio Interface Baud Rate = 9600 
   0x02, //Radio TX RF Baud Rate  = 9600
   0x02, //Radio RX RF Baud Rate = 9600
   0x06, //Rx Buffer Size  = ???????????
   0x04, //Tx Buffer Size  = ???????????
   0x0A, //Tx Power Amp level  = 3W
   0x00, //Channel Rx Mode (do not implement)
   0x00, //Channel Tx Mode (do not implement)
   144990, //Channel Rx Frequency (default radio specific)
   434200, //Channel Tx Frequency (default radio specific)
   {'N','O','C','A','L','L'}, //AX25 Mode Source Call Sign  
   {'N','O','C','A','L','L'}, //AX25 Mode Destination Call Sign 
   10, //AX25 Mode Tx Delay 
   100, //AX25 Mode Tx Delay End 
   0x60, //AX25 Mode PID 
   0x00, //Binary Mode Encoding Method
   0x00, //Binary Mode Scrambling Function
   0x00, //Binary Mode Flag or Synch Bytes
   0x00, //Binary Mode Checksum method
   0x00 //Spare
};


const static RadioTelemetry DEFAULT_RADIO_TELEMETRY = {
    0x00,//Radio Interface mode = binary
    0x0000,//Radio Time = ?????????
    0x02,//Radio Interface Baud Rate = 9600
    0x02, //Radio TX RF Baud Rate  = 9600
    0x02, //Radio RX RF Baud Rate = 9600
    0x06, //Rx Buffer Size  = ???????????
    0x04, //Tx Buffer Size  = ???????????
    0x0A, //Tx Power Amp level  = 3W
    0x00, //Channel Rx Mode (do not implement)
    0x00, //Channel Tx Mode (do not implement)
    144990, //Channel Rx Frequency (default radio specific)
    434200, //Channel Tx Frequency (default radio specific)
    {'N','O','C','A','L','L'}, //AX25 Mode Source Call Sign
    {'N','O','C','A','L','L'}, //AX25 Mode Destination Call Sign
    10, //AX25 Mode Tx Delay
    100, //AX25 Mode Tx Delay End
    0x60, //AX25 Mode PID
    0x00, //Binary Mode Encoding Method
    0x00, //Binary Mode Scrambling Function
    0x00, //Binary Mode Flag or Synch Bytes
    0x00, //Binary Mode Checksum method
    0x00 //Spare
};

//------------------------------------------------------[4400]C&DH
//------------------------------------------------[4500]MECHANICAL

const static int DEPLOYMENT_TIME = 240; //seconds


//---------------------------------------------------[4600]PAYLOAD

const static float GT_EVENT_SAMPLE_RATE = 1/20000; //in seconds
const static float GT_SPECTRUM_SAMPLE_RATE = 2/3; //in seconds
const static int GT_SPECTRUM_SIZE = 100; //resolution of GT spectrum

//-----------------------------------------------------[4700]POWER


/*---------------------------------------------------------------
---------------------****[5000]FUNCTIONS****---------------------
---------------------------------------------------------------*/

//---------------------------------------------------[5100]SYSTEM

/*[5110] SYSTEM CHECKS*/
void systemCheckout();
ACSSystemState ACSSystemCheck();
COMSSystemState COMSSystemCheck();
CDHSystemState CDHSystemCheck();
MECHSystemState MECHSystemCheck();
POWSystemState POWSystemCheck();
PAYSystemState PAYSystemCheck();

void sendDownPipe(SystemState current_state, string system_pipe); //||FIXME: NOT YET IMPLEMENTED||

/*[5120] DRIVERS*/
float readThermistor(int thermistor_id); //||FIXME: NOT YET IMPLEMENTED||
float readISensor(int IV_sensor_id); //||FIXME: NOT YET IMPLEMENTED||
float readVSensor(int IV_sensor_id); //||FIXME: NOT YET IMPLEMENTED||
void setGPIOHigh(int GPIO_id); //||FIXME: NOT YET IMPLEMENTED||
void setGPIOLow(int GPIO_id); //||FIXME: NOT YET IMPLEMENTED||


//------------------------------------------------------[5200]ACS

MagXYZ getMagReadings(); //||FIXME: NOT YET IMPLEMENTED||
MagXYZ getIGRF(ECIposition current_position); //||FIXME: NOT YET IMPLEMENTED||
ECIposition getPosition(time_t current_time); //||FIXME: NOT YET IMPLEMENTED||
EulerAngle getAttitude(MagXYZ current_mag, MagXYZ reference_mag); //||FIXME: NOT YET IMPLEMENTED||

//-------------------------------------------[5300]COMMUNICATIONS

string commandTransceiver(Transceiver_Command inputCommand);
RadioConfiguration getRadioConfiguration();//||FIXME: IMPLEMENT FUNCTION||
RadioTelemetry getRadioTelemetry();//||FIXME: IMPLEMENT FUNCTION||
string serialWrite(uint8_t * command); //Private
string speedUpTester(bool do_increase_speed); //||FIXME: TEST FUNCTION||


//-----------------------------------------------------[5400]C&DH
//-----------------------------------------------[5500]MECHANICAL

//Function triggers every 60 minutes after deployment
//Software update will remove this job during LEOP
void deployAntenna(); //||FIXME: NOT YET COMPLETE||


//--------------------------------------------------[5600]PAYLOAD
//----------------------------------------------------[5700]POWER
float readBatteryCharge(float battery_voltage);


#endif