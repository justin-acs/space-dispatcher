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
// refrain from reading further. You have been warned. 
//-----------------------------------------------------------------------------


#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <errno.h>
#include "jobs/jobs.h"

using namespace std;
 
enum dispatcherState {baconing, comming, payloading, chillaxing};

void initializeALLtheThings();
void shutdownALLtheThings();

void baconingState();
void commingState();
void payloadingState();
void chillaxingState();


SystemState zeState;


dispatcherState currentState = baconing;

JobsCollection allJobs;

int main(int argc, char** argv) {
    int stayingAlive = 1;     
    initializeALLtheThings();
    
    while(stayingAlive) {
        
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
    
    return 0;
}


//------------------------------------------------------------------------------
// This is when bacons are cooked
//------------------------------------------------------------------------------
void baconingState() {
    
    if (zeState.hasEnoughPower()){
        allJobs.spawnJob(JobName::TurnOnTransceiver);
        allJobs.spawnJob(JobName::TurnOnBacon);
        allJobs.spawnJob(JobName::ListenToEarth);
    }        
    
}

void commingState() {    
    if (zeState.isTransceiverTransceiving()) {
        
    }    
}

void chillaxingState() {
    if (zeState.hasEnoughPower()){
        //keep chilling
    }
}

void initializeALLtheThings() {    
    
}

void shutdownALLtheThings() {
    allJobs.spawnJob(JobName::TurnOffTransceiver);
    allJobs.spawnJob(JobName::DoNotListenToEarth);
}












