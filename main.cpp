/*  MAIN TEST
 * File:   main.cpp
 * Author: spaceconcordia
 * 
 * Created on August 16, 2012, 7:10 PM
 */

//-----------------------------------------------------------------------------
// DISCLAMER!!!
//
// The following code is intended for with sense of humor audiences only.
// This writing contains strong language, graphic scenes of 
// violence and senseless butchery. Those who are faint of heart should
// refrain from reading further. You have been warned 'cause you read this.
//-----------------------------------------------------------------------------


#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <errno.h>
#include "StringUtilities.h"
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <fstream>
#include <signal.h>
#include "jobs/system.h"
#include <vector>
#include "jobs/jobs.h"

using namespace std;
 
#define COMMANDER_PATH "/home/CODE/commander"
#define LEOP_PATH "/home/CODE/LEOP_Done" 
#define POWER_LEVEL_FILE "/home/CODE/power_level"

enum dispatcherState {baconing, comming, payloading, chillaxing, leop};



//void g_initializeJobObjects(); moved to system header
void shutdownALLtheThings();
void setBaconOn();
void setCommingOn();
void burnWire();
void setTransceiverOff();
void checkLeop();
void baconingState();
void commingState();
void payloadingState();
void chillaxingState();
void exitBaconState(int);
void checkPowerLevels();
int checkCommingSchedule();
pid_t spawnCommander();

dispatcherState currentState; 

Jobs jobs;


int g_pipeToCommander[2];
int g_writePipeCommander;
int g_lastBurning;
pid_t g_commanderPid;
int g_running; 
bool g_enoughPower = true;
unsigned int g_bootTime;

pid_t spawnCommander(){
    cout << "Dispatcher: Spawning Commander" << endl;
    pipe(g_pipeToCommander);   
    fcntl(g_pipeToCommander[0], F_SETFL, O_NONBLOCK);
    fcntl(g_pipeToCommander[1], F_SETFL, O_NONBLOCK);
    
    //fork & execl commander
    pid_t childPID = fork();  
    
    if (childPID == 0){
        close(g_pipeToCommander[1]);
                
        //PID should remain the same
        cout << StringUtilities::intToString(g_pipeToCommander[0]);
        cout.flush();
        execl(COMMANDER_PATH,
              COMMANDER_PATH,  
              StringUtilities::intToString(g_pipeToCommander[0]).c_str(),
              (char *)NULL);
        
    }
    else{
        close(g_pipeToCommander[0]);
        g_writePipeCommander = g_pipeToCommander[1];
        return childPID;        
    }
}    

bool isLeopCompleted() {
    cout << "Dispatcher: Checking LEOP" << endl;
    ifstream ifile(LEOP_PATH);
    return ifile;
}

int main(int argc, char** argv) {
    
    g_bootTime = time(NULL);
    ofstream bootLog("/home/CODE/logs/boots",ios::out | ios::app);
    bootLog << g_bootTime << "\n";
    bootLog.close();
    
    initializeJobObjects();
    
    signal(SIGUSR1, exitBaconState); //Commander will signal the Dispatcher when it's time to leave the bacon state
    
    g_lastBurning = -1;
    g_running = 1;     
    g_commanderPid = spawnCommander();
    currentState = baconing;
        
    while(g_running) {
        
        checkPowerLevels();//everyone needs power level checked
        switch (currentState){            
            case baconing:
                if (g_enoughPower == true){ baconingState(); }
                break;
            
            case comming:
                if (g_enoughPower == true){ commingState(); }
                break;
            
            case chillaxing:    
                chillaxingState(); //
                break;
            
         }  
        
        sleep(10);
    }
    
    return EXIT_FAILURE;
}


//------------------------------------------------------------------------------
// This is when bacons are cooked
//------------------------------------------------------------------------------
void baconingState() {
    cout << "Dispatcher: in baconingState()" << endl;
    checkLeop();
    setBaconOn();
    systemCheckout();
    //sleep(300); the five minutes between sys checkouts
    
    return;
}

void commingState() {    
    cout << "Dispatcher: in commingState()" << endl;
    setCommingOn();
    systemCheckout();
    //sleep(300); the five minutes between sys checkouts
    return;
}

void chillaxingState() {
    cout << "Dispatcher: in chillaxingState()" << endl;
    systemCheckout();
    sleep(checkCommingSchedule());
    //checkPayloadSchedule();
    
    return;
}

void shutdownALLtheThings() {
    
}


void checkLeop(){
    if ((time(NULL) - g_bootTime) < (300)){
        return;        
    }
        
    if (!isLeopCompleted()) {
        if (g_lastBurning == -1){ 
            g_lastBurning = time(NULL);
            burnWire();
        }
        else{
            if ((time(NULL) + 18000) > g_lastBurning){ //if it's been more than 5 hours
                g_lastBurning = time(NULL);
                burnWire();          
            }
        }
    }
    else {
        cout << endl;
        cout << "//------------------------------------\\\\" << endl;
        cout << "//    LEOP done, and still alive      \\\\" << endl;
        cout << "//------------------------------------\\\\" << endl;
        cout << endl; 
        cout.flush();
    }    
}

void burnWire(){
    cout << "Pyro Dispatcher: Hurrururururu! Mmmrpgh crpyha drghya! Hahahah!" << endl; cout.flush();
    //set pin high 
    //sleep required time
    //set pin low
    return;
}

  

void setTransceiverOff(){
    char message= {0xF};
    write(g_writePipeCommander, &message,1); 
    return;
}

void setBaconOn(){
    cout << "Dispatcher here! Set the bacon on!!" << endl;  cout.flush();
    char message= {0x10};
    write(g_writePipeCommander, &message,1); 
    return;
}

void setCommingOn(){
    char message = {0x7};
    write(g_writePipeCommander, &message,1); 
    return;
}

void exitBaconState(int sigNum){
    cout << "Dispatcher in the house, bacon state offline!" << endl; cout.flush();
    currentState = chillaxing;
    return;
}

int checkCommingSchedule(){
        //load entire file in memory
        //check next scheduled comms
        //if it's further than 5 minutes, return 300 seconds
        //if it's within 5 minutes, return in how many seconds it is and set the current state to comming
}

void checkPowerLevels(){
    ifstream file("/home/CODE/latest_power");
    unsigned int powerPercent = 0 ;
    unsigned int powerThreshold = 0 ;
    if (file.good()){
        string line;
        
        getline(file,line);
        powerPercent = atoi(line.c_str());
        
    }
    
    
    ifstream file2("/home/CODE/latest_power_threshold");
    if (file2.good()){
        string line;
        
        getline(file2,line);
        powerThreshold = atoi(line.c_str());
                
                
      }
    
    if (powerPercent < powerThreshold ){
        g_enoughPower = false;
        setTransceiverOff();
        
    }
    else{
        g_enoughPower = true;
    }
    //commander should create a power threshold file specifying the acceptable threshold as its told by Ground Station
    //system checkout should have produced a file describing on one line the current power level
    //read file and if power is too low... shut down and hope power knows how to wake us    
}
//
// // computer avg thermistance
//  int n = 50;
//  float rt=0.0;
//  for (int i=0;i<n;++i) {
//    rt+=ro/(vdd/read_adc()-1.0);
//  }
//  rt/=n;
//  Serial.print("RT: ");
//  Serial.println(rt);
//  
//  // compute average temp
//  float temp;
//  temp=1.0/(1.0/(to+to_cal)+log(rt/ro_cal)/tb);
//  temp=temp-to; // convert to c
//  
//  return temp;