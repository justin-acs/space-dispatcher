
/* 
 * TEST
=======
/*  MAIN TEST
>>>>>>> e6c0767233d0d41cf271630ca2c811b9cf13971d
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
#include "jobs/jobs.h"
#include "StringUtilities.h"
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <fstream>
#include <signal.h>

using namespace std;
 
#define COMMANDER_PATH "/usr/bin/gedit"
#define LEOP_PATH "~/LEOP" 
#define POWER_LEVEL_FILE "/home/spaceconcordia/Public/test/last_power_level"

enum dispatcherState {baconing, comming, payloading, chillaxing, leop};

void initializeALLtheThings();
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
void exitBaconState();
void checkPowerLevels();
int checkCommingSchedule();




dispatcherState currentState; 

Jobs jobs;

int pipeToCommander[2];
int writePipeCommander;
int lastBurning;
pid_t spawnCommander(){
    pipe(pipeToCommander);   
    fcntl(pipeToCommander[0], F_SETFL, O_NONBLOCK);
    fcntl(pipeToCommander[1], F_SETFL, O_NONBLOCK);
    
    //fork & execl commander
    pid_t childPID = fork();  
    
    if (childPID == 0){
        close(pipeToCommander[1]);
         
        //because execl expects a string, not an integer
        
        //PID should remain the same
        execl(COMMANDER_PATH,
              StringUtilities::intToString(pipeToCommander[1]).c_str(),
              (char *)NULL );
        
    }
    else {
        close(pipeToCommander[0]);
        return childPID;    
    }
}    
pid_t commanderPid;
int running; 

bool isLeopCompleted() {
    ifstream ifile(LEOP_PATH);
    return ifile;
}

int main(int argc, char** argv) {

    signal(SIGUSR1, exitBaconState); //Commander will signal the Dispatcher w
    lastBurning = -1;
    running = 1;     
    commanderPid = spawnCommander();
    currentState = baconing;
    
    while(running) {
        
        checkPowerLevels();//everyone needs power level checked
        switch (currentState){            
            case baconing:
                baconingState();                
                break;
            
            case comming:
                commingState();
                break;
            
            case chillaxing:    
                chillaxingState();
                break;
         }         
        
    }
    
    return EXIT_FAILURE;
}


//------------------------------------------------------------------------------
// This is when bacons are cooked
//------------------------------------------------------------------------------
void baconingState() {
    checkLeop();
    setBaconOn();
    systemCheckout();
    //sleep(300); ?
    return;
}

void commingState() {    
    setCommingOn();
    systemCheckout();
    //sleep(300); ?
    return;
}

void chillaxingState() {
    systemCheckout();
    sleep(checkCommingSchedule());
    //checkPayloadSchedule();
    
    return;
}

void initializeALLtheThings() {    
    
}

void shutdownALLtheThings() {
    
}


void checkLeop(){
    if (!(isLeopCompleted())) {
        if (lastBurning == -1){ 
            lastBurning = time(NULL);
            burnWire();
        }
        else{
            if ((time(NULL) + 18000) > lastBurning){ //if it's been more than 5 hours
                lastBurning = time(NULL);
                burnWire();          
            }
        }
    }
    return;
}

void burnWire(){
    //set pin high 
    //sleep required time
    //set pin low
    return;
}

pid_t spawnCommander(){
    pipe(pipeToCommander);   
    fcntl(pipeToCommander[0], F_SETFL, O_NONBLOCK);
    fcntl(pipeToCommander[1], F_SETFL, O_NONBLOCK);
    
    //fork & execl commander
    pid_t childPID = fork();  
    
    if (childPID == 0){
        close(pipeToCommander[1]);
                
        //PID should remain the same
        execl(COMMANDER_PATH,StringUtilities::intToString(pipeToCommander[0]).c_str(),(char *)NULL);
        
    }
    else{
        close(pipeToCommander[0]);
        writePipeCommander = pipeToCommander[1];
        return childPID;        
    }
}    

void setTransceiverOff(){
    char message[1]= 0xF;
    write(writePipeCommander, message,1); 
    return;
}

void setBaconOn(){
    char message[1]= 0x10;
    write(writePipeCommander, message,1); 
    return;
}

void setCommingOn(){
    char message[1]= 0x7;
    write(writePipeCommander, message,1); 
    return;
}

void exitBaconState(){
    currentState = chillaxing;
}

void checkCommingSchedule(){
        //load entire file in memory
        //check next scheduled comms
        //if it's further than 5 minutes, return 300 seconds
        //if it's within 5 minutes, return in how many seconds it is and set the current state to comming
}


void checkPowerLevels(){
    //system checkout should have produced a file describing on one line the current power level
    //read file and if power is too low... shut down and hope power knows how to wake us
    
}