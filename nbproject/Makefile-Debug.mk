#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/jobs/acs.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/jobs/system.o \
	${OBJECTDIR}/jobs/power.o \
	${OBJECTDIR}/jobs/payload.o \
	${OBJECTDIR}/jobs/cdh.o \
	${OBJECTDIR}/jobs/mech.o \
	${OBJECTDIR}/jobs/jobs.o \
	${OBJECTDIR}/jobs/coms.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/space-dispatcher

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/space-dispatcher: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/space-dispatcher ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/jobs/acs.o: jobs/acs.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/acs.o jobs/acs.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/jobs/system.o: jobs/system.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/system.o jobs/system.cpp

${OBJECTDIR}/jobs/power.o: jobs/power.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/power.o jobs/power.cpp

${OBJECTDIR}/jobs/payload.o: jobs/payload.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/payload.o jobs/payload.cpp

${OBJECTDIR}/jobs/cdh.o: jobs/cdh.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/cdh.o jobs/cdh.cpp

${OBJECTDIR}/jobs/mech.o: jobs/mech.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/mech.o jobs/mech.cpp

${OBJECTDIR}/jobs/jobs.o: jobs/jobs.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/jobs.o jobs/jobs.cpp

${OBJECTDIR}/jobs/coms.o: jobs/coms.cpp 
	${MKDIR} -p ${OBJECTDIR}/jobs
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/jobs/coms.o jobs/coms.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/space-dispatcher

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
