/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet
   Subsystem Lead: Tiago Leao

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the Communications System on ConSat-1.
*/

#include "system.h"

COMSSystemState COMSSystemCheck(){
   COMSSystemState COMS_state;

   /*Take readings*/
   //Check thermistors
    COMS_state.antenna_temp = readThermistor(antenna_thermistor_id);

   //Check transceiver configuration    
    COMS_state.radio_config = getRadioConfiguration();

   //Check transceiver telemetry
   COMS_state.radio_telemetry = getRadioTelemetry();    /*FIX RETURNED VALUES*/

   /*Pipe it out*/
   //sendDownPipe(COMS_state, SYSTEM_PIPE);
    
    COMS_flags &= (0<<CF_GROUND_CONTACT);
    
   return COMS_state;
}

RadioConfiguration getRadioConfiguration(){
    Transceiver_Command get_config;
    get_config.command_type = COMMAND_TYPE_I;
    get_config.command = I_GET_CONFIG;
    get_config.payload_size = 0;
    uint8_t get_config_data = NULL;
    get_config.payload_data = &get_config_data;
    
    //||FIXME: FIX RETURN VALUE||
    return DEFAULT_RADIO_CONFIG;
    //return commandTransceiver(get_config);
}

RadioTelemetry getRadioTelemetry(){
    Transceiver_Command get_telemetry;
    get_telemetry.command_type = COMMAND_TYPE_I;
    get_telemetry.command = I_TELEMETRY;
    get_telemetry.payload_size = 0;
    uint8_t get_telemetry_data = NULL;
    get_telemetry.payload_data = &get_telemetry_data;
    
    //||FIXME: FIX RETURN VALUE||
    return DEFAULT_RADIO_TELEMETRY;
    //return commandTransceiver(get_telemetry);
}

string speedUpTester(bool do_increase_speed){

   RadioConfiguration config;
   

   config = DEFAULT_RADIO_CONFIG;

   Transceiver_Command set_config;
   set_config.command_type = COMMAND_TYPE_I;
   set_config.command = I_SET_CONFIG;
   set_config.payload_size = 46;
   config.tx_rf_baud_rate = (do_increase_speed) ? 0x04 : 0x02;
   set_config.payload_data = (uint8_t *) &config;

  return commandTransceiver(set_config);
}

string commandTransceiver(Transceiver_Command inputCommand){ 

   uint8_t command_type = inputCommand.command_type;
   uint16_t command = inputCommand.command; 
   uint8_t payload_size = inputCommand.payload_size;
   uint8_t * payload_data = inputCommand.payload_data; 
   
   //configure header
   uint8_t header_bytes[8];
   uint8_t header_checksum_A = 0;
   uint8_t header_checksum_B = 0;
   header_bytes[0] = SYNC_CHARACTERS[0];
   header_bytes[1] = SYNC_CHARACTERS[1];
   header_bytes[2] = command_type;        //either COMMAND_TYPE_I or COMMAND_TYPE_O
   header_bytes[3] = command;             //see above op codes
   header_bytes[4] = (payload_size >> 8) & 0xff; //for MSB of payload_size
   header_bytes[5] = payload_size & 0xff; //for LSB of payload_size
   
   //perform header checksum
   //note that 'H' and 'e' are not counted
   for (int i = 2; i< HEADER_SIZE - 2; i++){
      header_checksum_A += header_bytes[i];
      header_checksum_B += header_checksum_A;
      //cout << (int) header_checksum_A << "\t" <<  (int) header_checksum_B << endl;
   }

   //add checksum to header
   header_bytes[6] = header_checksum_A;
   header_bytes[7] = header_checksum_B;

   //set payload
   uint8_t payload_checksum_A = 0;
   uint8_t payload_checksum_B = 0;


   //perform payload checksum
   for (int i = 0; i< payload_size; i++){
      payload_checksum_A += (int) payload_data[i];
      payload_checksum_B += payload_checksum_A;
      //cout << (int) payload_checksum_A << "\t" <<  (int) payload_checksum_B << endl;
   }


   //load everything into a single command buffer
   uint8_t command_buffer[HEADER_SIZE + payload_size + 2]; //8 bytes for header, 0 - 255 for paylod, 2 for payload checksums

   for (int i = 0; i < HEADER_SIZE; i++){
      command_buffer[i] = header_bytes[i];
   }

   for (int i = HEADER_SIZE; i < HEADER_SIZE + payload_size; i++){
      command_buffer[i] = payload_data[i - HEADER_SIZE];
   }

   command_buffer[HEADER_SIZE + payload_size] = payload_checksum_A;
   command_buffer[HEADER_SIZE + payload_size + 1] = payload_checksum_B;

   return serialWrite(command_buffer);
}

string serialWrite(uint8_t * command){
   int fd; //device handle
   uint8_t response[255+8+2];
   string returnResponse;

   const char *device = "/dev/ttyUSB0";
   fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
   if(fd == -1) {
     printf( "failed to open port\n" );
   }

   struct termios config;

   if(!isatty(fd)) { cout << "Not a TTY" << endl; }
   if(tcgetattr(fd, &config) < 0) {cout << "Termios structure is broken" << endl;}

   config.c_iflag  = 0;//&= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
   config.c_oflag = 0; //&= ~(OCRNL | ONLCR | ONLRET | ONOCR | CSTOPB | ONOEOT| OFILL | OPOST);
   config.c_cflag &= ~(CSIZE | PARENB | CSTOPB); // 8bits, no parity, 1 stop
   config.c_cflag |= CS8 | CREAD | HUPCL;
   config.c_cc[VMIN]  = 0;
   config.c_cc[VTIME] = 1;

   // Communication speed (simple version, using the predefined constants)
   if(cfsetispeed(&config, B9600) < 0 || cfsetospeed(&config, B9600) < 0) {
       cout << "Speed is messed up" << endl;
   }

   // Finally, apply the configuration
   if(tcsetattr(fd, TCSAFLUSH, &config) < 0) { cout << "Applied Configuration is broken" << endl;}
   
   // uint8_t c[2] = {'D','A'};
   // write(fd,&c,2);
   //uint8_t TESTSEND[8] = {0x48, 0x65, 0x10, 0x01, 0x00, 0x00, 0x11, 0x43};
//   uint8_t TESTSEND[8] = {0x48, 0x65, 0x10, 0x05, 0x00, 0x00, 0x15, 0x4F};
//   write(fd,TESTSEND,8);

   printf("%s\n", "---------------COMMAND -----------");
   int i = 0;
   for (i = 0; i != 8; i++) {
       printf("%d\n", command[i]);
   }     
   printf("%s\n", "---------------COMMAND END -----------");
   
   int size = 8;
   if (command[5] > 0) { //Has payload data
       size = command[5] + 10; //8 bytes for header + 2 for payload checksums
   }    
   write(fd, command, size);
   
   //Read if data available on serial
   sleep(1);
   bool responseReceived = false;
   char buffer[5];

   while (read(fd,response,1)>0) {      
      sprintf(buffer, "%d ", response[0]);
      returnResponse += buffer;

      printf("%x - %d\n", response[0], response[0]);
      responseReceived = true;
   }  

//   DEBUGGER CODE - COMMENT OUT
 /*  for (int i = 0; i < command[5]+10; i++){
      cout << "BIN" << i << ": " << setw(8) << bitset<CHAR_BIT>(command[i]);
      cout << "\t\t\tHex" << i << ": " << setw(8) << hex << (unsigned int) command[i];
      cout << "\t\t\tDec" << i << ": " << setw(10) << dec << (unsigned int) command[i];
      cout << "\t\t\tASCII" << i << ": " << command[i] << endl;
   }

*/
   close(fd);

   return (responseReceived) ? returnResponse : "Transmit successful, but no response";
}

