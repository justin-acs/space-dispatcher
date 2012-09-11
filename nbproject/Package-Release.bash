#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build
NBTMPDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
<<<<<<< HEAD
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/space-dispatcher
OUTPUT_BASENAME=space-dispatcher
PACKAGE_TOP_DIR=space-dispatcher/
=======
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/space_dispatcher
OUTPUT_BASENAME=space_dispatcher
PACKAGE_TOP_DIR=spacedispatcher/
>>>>>>> e6c0767233d0d41cf271630ca2c811b9cf13971d

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
rm -rf ${NBTMPDIR}
mkdir -p ${NBTMPDIR}

# Copy files and create directories and links
cd "${TOP}"
<<<<<<< HEAD
makeDirectory "${NBTMPDIR}/space-dispatcher/bin"
=======
makeDirectory "${NBTMPDIR}/spacedispatcher/bin"
>>>>>>> e6c0767233d0d41cf271630ca2c811b9cf13971d
copyFileToTmpDir "${OUTPUT_PATH}" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}" 0755


# Generate tar file
cd "${TOP}"
<<<<<<< HEAD
rm -f ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/space-dispatcher.tar
cd ${NBTMPDIR}
tar -vcf ../../../../${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/space-dispatcher.tar *
=======
rm -f ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/spacedispatcher.tar
cd ${NBTMPDIR}
tar -vcf ../../../../${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/spacedispatcher.tar *
>>>>>>> e6c0767233d0d41cf271630ca2c811b9cf13971d
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${NBTMPDIR}
