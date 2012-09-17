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
#include "errorsFromSpace.h"
#include "jobs/jobs.h"

bool Jobs::exists(string path) {
    return jobsList.find(path) == jobsList.end();
}

bool Jobs::spawn(string path) {
    pid_t pid = -1;
    
    if (!exists(path)) {                
        jobsList.insert(std::make_pair(path, pid));
    }
    
    return pid > 0;
}

bool Jobs::killme(string path) {
    if (exists(path)) {
        map<string, pid_t>::iterator iter = jobsList.find(path);
        
        pid_t pid = iter->second;
        kill(pid, SIGKILL);
        jobsList.erase(path);
 
        return true;
    }
    else {
        return false;
    }
}



