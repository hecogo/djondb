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
	${OBJECTDIR}/util/cache.o \
	${OBJECTDIR}/util/timerecord.o \
	${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/common/util.o \
	${OBJECTDIR}/util/threads.o \
	${OBJECTDIR}/util/logger/logger.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libcommon.so

dist/Release/GNU-Linux-x86/libcommon.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcommon.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/util/cache.o: nbproject/Makefile-${CND_CONF}.mk util/cache.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/util/cache.o util/cache.cpp

${OBJECTDIR}/util/timerecord.o: nbproject/Makefile-${CND_CONF}.mk util/timerecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/util/timerecord.o util/timerecord.cpp

${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/common/util.o: nbproject/Makefile-${CND_CONF}.mk /home/cross/workspace/jaguar/jaguar/jaguar-server/common/util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/common/util.o /home/cross/workspace/jaguar/jaguar/jaguar-server/common/util.cpp

${OBJECTDIR}/util/threads.o: nbproject/Makefile-${CND_CONF}.mk util/threads.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/util/threads.o util/threads.cpp

${OBJECTDIR}/util/logger/logger.o: nbproject/Makefile-${CND_CONF}.mk util/logger/logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/util/logger
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/util/logger/logger.o util/logger/logger.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libcommon.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
