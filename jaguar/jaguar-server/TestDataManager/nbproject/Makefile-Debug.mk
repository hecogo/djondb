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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o

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
LDLIBSOPTIONS=-Wl,-rpath /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/dist/Debug/GNU-Linux-x86 -L/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/dist/Debug/GNU-Linux-x86 -ldatamanager -Wl,-rpath /home/cross/workspace/jaguar/jaguar/jaguar-server/common/dist/Debug/GNU-Linux-x86 -L/home/cross/workspace/jaguar/jaguar/jaguar-server/common/dist/Debug/GNU-Linux-x86 -lcommon -Wl,-rpath /home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar/dist/Debug/GNU-Linux-x86 -L/home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar/dist/Debug/GNU-Linux-x86 -ldbjaguar

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/testdatamanager

dist/Debug/GNU-Linux-x86/testdatamanager: /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/dist/Debug/GNU-Linux-x86/libdatamanager.so

dist/Debug/GNU-Linux-x86/testdatamanager: /home/cross/workspace/jaguar/jaguar/jaguar-server/common/dist/Debug/GNU-Linux-x86/libcommon.so

dist/Debug/GNU-Linux-x86/testdatamanager: /home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar/dist/Debug/GNU-Linux-x86/libdbjaguar.so

dist/Debug/GNU-Linux-x86/testdatamanager: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lmysqlclient -lz -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testdatamanager ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager -I/home/cross/workspace/jaguar/jaguar/jaguar-server/common -I/home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/testdatamanager

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
