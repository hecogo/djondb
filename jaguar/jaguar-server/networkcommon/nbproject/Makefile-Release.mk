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
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkservice.o \
	${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkcommon.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libnetworkcommon.so

dist/Release/GNU-Linux-x86/libnetworkcommon.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworkcommon.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkservice.o: nbproject/Makefile-${CND_CONF}.mk /home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkservice.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkservice.o /home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkservice.cpp

${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkcommon.o: nbproject/Makefile-${CND_CONF}.mk /home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkcommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkcommon.o /home/cross/workspace/jaguar/jaguar/jaguar-server/networkcommon/networkcommon.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libnetworkcommon.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
