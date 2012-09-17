/* 
 * File:   StringUtilities.h
 * Author: spaceconcordia
 *
 * Created on September 12, 2012, 12:35 PM
 */

#ifndef STRINGUTILITIES_H
#define	STRINGUTILITIES_H

#include <string>
#include <sstream>

using namespace std;
void initializeJobObjects();

class StringUtilities {
public:
    static string intToString(int number);
    static string floatToString(float number);
};

#endif	/* STRINGUTILITIES_H */

