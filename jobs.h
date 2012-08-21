/* 
 * File:   jobs.h
 * Author: spaceconcordia
 *
 * Created on August 20, 2012, 6:53 PM
 */

//-----------------------------------------------------------------------------
// DISCLAMER!!!
//
// The following code is intended for with sense of humor audiences only.
// This writing contains strong language, graphic scenes of 
// violence and senseless butchery. Those who are faint of heart should
// refrain from reading further. You have been warned. 
//-----------------------------------------------------------------------------

#ifndef JOBS_H
#define	JOBS_H

#include <vector>
#include <time.h>
#include <stdint.h>

using namespace std;

// // // // enums // // // // 

//maybe we can just assign names for jobs through an enum?
//C++ enums kinda suck so this is a cool workaround
namespace JobName {
    enum Enum { 
        FakeJob1,
        FajeJob2, 
        TurnOnBacon, 
        TurnOffBacon, 
        ReadACS,
        TurnOnTransceiver, 
        TurnOffTransceiver,
        ListenToEarth,
        DoNotListenToEarth                
    };
}   



class GeoClock { //but tell me why?! ?!
public:
    time_t timestamp;    
    uint32_t latitude;     
    uint32_t longitude;
};

class Job{
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    Job(pid_t jobPID, JobName::Enum name, int jobPipeReadFrom, int jobPipeWriteTo) {
        this->PID = jobPID;        
        this->name = name;
        this->pipeRead = jobPipeReadFrom;
        this->pipeWrite = jobPipeWriteTo;      
    }
    
    //-------------------------------------------------------------------------
    // Variables
    //-------------------------------------------------------------------------

    pid_t PID;    
    JobName::Enum name;
    int pipeRead;
    int pipeWrite;
    
    //-------------------------------------------------------------------------
    // Methods
    //-------------------------------------------------------------------------    
    bool isAlive() {};
    int killMe() {};
    int pauseMe() {};
    int continueMe() {} ;
    int doMe();       
    
    
    
};

// // // //  classes // // // // 
class JobsCollection {
public:
    vector<Job> jobs;
    int spawnJob(JobName::Enum name);
    int killAllJobs();
private:
    void forkJob(JobName::Enum name);    
};


class SystemState {
public:
    int getTroubleMaker() {};
    bool hasEnoughPower() {};
    bool isLavaHotEnough() {};   
    bool isTransceiverTransceiving() {};
private:
    int voltage;
    int current;
    int lavaLevel;    
};


void FakeJob1(int, int);
void FakeJob2(int, int);
void TurnOnBacon(int, int);
void TurnOffBacon(int, int);
void ReadACS(int,int);






#endif	/* JOBS_H */

