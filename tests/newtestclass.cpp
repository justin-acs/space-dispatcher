/*
 * File:   newtestclass.cpp
 * Author: spaceconcordia
 *
 * Created on Aug 20, 2012, 8:19:32 PM
 */

#include "newtestclass.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testMethod() {
    CPPUNIT_ASSERT(true);
}

void newtestclass::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

