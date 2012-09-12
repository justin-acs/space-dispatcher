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
#include "StringUtilities.h"
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <fstream>

using namespace std;
 
#define COMMANDER_PATH "/usr/bin/gedit"
#define LEOP_PATH "~/LEOP"

enum dispatcherState {baconing, comming, payloading, chillaxing, leop};

void initializeALLtheThings();
void shutdownALLtheThings();

void baconingState();
void commingState();
void payloadingState();
void chillaxingState();


//SystemState zeState;


dispatcherState currentState = baconing;

Jobs jobs;

int pipeToCommander[2];

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

bool isLeopCompleted() {
    ifstream ifile(LEOP_PATH);
    return ifile;
}

int main(int argc, char** argv) {
    int running = 1;     
    pid_t  commanderPid = spawnCommander();
    
    if (!isLeopCompleted()) {
        currentState = leop;
    }
    
    while(running) {        
        switch (currentState){            
            case leop:
                currentState = baconing;
                break;
                
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
      
    
}

void commingState() {    

}

void chillaxingState() {
    
}

void initializeALLtheThings() {    
    
}

void shutdownALLtheThings() {
    
}












