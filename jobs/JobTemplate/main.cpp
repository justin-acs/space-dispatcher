/* 
 * File:   main.cpp
 * Author: charizard
 *
 * Created on August 30, 2012, 7:01 PM
 */

#include <cstdlib>
#include <string>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "shakespeare.h"

using namespace std;



const string LOG_PATH("/home/charizard/Dropbox/code/JobTemplate/");
const string LOG_PREFIX("SUBSYSTEM.");
const string LOG_SUFFIX(".log");

string do_work() {};

int main(int argc, char** argv) {    
    string parameter;
    
    if (argc == 2) {
        parameter.assign(argv[1], strlen(argv[1]) + 1);        
    }               
             
    cout << "Child(" << getpid() << ") SYSTEM: working working working" << endl;
    //string result = do_work();
        
    //FILE *log = fopen(get_filename(LOG_PATH, LOG_PREFIX, LOG_SUFFIX).c_str(), "w");        
    //Log(log, result);
    //fclose( log);       
    
    return 0;
}
