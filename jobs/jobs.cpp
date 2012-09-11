//-----------------------------------------------------------------------------
// DISCLAMER!!!
//
// The following code is intended for with sense of humor audiences only.
// This writing contains strong language, graphic scenes of 
// violence and senseless butchery. Those who are faint of heart should
// refrain from reading further. You have been warned. 
//-----------------------------------------------------------------------------

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "jobs.h"
#include "errorsFromSpace.h"

int JobsCollection::spawnJob(JobName::Enum name) {
    for(int i = 0; i != jobs.size(); i++) {
        if (jobs[i].name == name) {           
            return ERROR_JOB_NAME_EXISTS;
        }
    }    
    forkJob(name);
    return NO_ERROR;
}

int JobsCollection::killAllJobs() {
    for(int i = 0; i != jobs.size(); i++) {
        jobs[i].killMe();     
    }
    return NO_ERROR;    
}

void JobsCollection::forkJob(JobName::Enum name) {
    int pipeJobToDispatcher[2];
    int pipeDispatcherToJob[2];
    pipe(pipeJobToDispatcher);
    pipe(pipeDispatcherToJob);
    
    //to set the pipes as non-blocking, that way, it doesn't block on read when there is no data in the pipe or write when the pipe is full
    fcntl(pipeJobToDispatcher[0], F_SETFL, O_NONBLOCK);
    fcntl(pipeJobToDispatcher[1], F_SETFL, O_NONBLOCK);
    fcntl(pipeDispatcherToJob[0], F_SETFL, O_NONBLOCK);
    fcntl(pipeDispatcherToJob[1], F_SETFL, O_NONBLOCK);       
    
    pid_t childPID = fork();
    
    if (childPID == 0){
        //closing unused ends of pipes
        close(pipeJobToDispatcher[0]);
        close(pipeDispatcherToJob[1]);               
        
        switch (name) {            
            case JobName::FajeJob2:
                FakeJob2(pipeJobToDispatcher[1], pipeDispatcherToJob[0]);
                break;
            case JobName::FakeJob1:
                FakeJob1(pipeJobToDispatcher[1], pipeDispatcherToJob[0]);
                break;
            
        }
                
    }
    else{
        close(pipeJobToDispatcher[1]);
        close(pipeDispatcherToJob[0]);        
               
        Job tempJob(childPID, name, pipeJobToDispatcher[0],pipeDispatcherToJob[1]);
        jobs.push_back(tempJob);                
    }
    
}

void FakeJob1(int writePipe, int readPipe){
    
        
}

void FakeJob2(int writePipe, int readPipe){
    
    int dontBitflip = 1;
    
    while(dontBitflip ){
                
    }

}




