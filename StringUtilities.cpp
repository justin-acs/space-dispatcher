/* 
 * File:   StringUtilities.cpp
 * Author: spaceconcordia
 * 
 * Created on September 12, 2012, 12:35 PM
 */

#include "StringUtilities.h"

string StringUtilities::intToString(int number) {   
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

string StringUtilities::floatToString(float number) {   
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}