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

#include <map>
#include <string>


using namespace std;



enum jobNames {power_job, mech_job, acs_job, cdh_job, coms_job, system_job, payload_job};

class job{
public:
    job(jobNames n, string p){
        this->name = n;
        this->path = p;
        
    }
    //assigned in constructor
    jobNames name;
    string path;
    // // // //
    
    //assigned on usage
    pid_t pid;
};


class Jobs {
public:    
    bool spawn(string path);
    bool killme(string path); //overlapped with kill from signal.h
    bool exists(string path);
    
private:
    //--------------------------------------------------------------------------
    // Members
    //--------------------------------------------------------------------------    
    map<string, pid_t> jobsList;                       
};

#endif	/* JOBS_H */

