#
# Gererated Makefile - do not edit!
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

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/util/threads.o \
	${OBJECTDIR}/util/util.o \
	${OBJECTDIR}/network/networkservice.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/util/cache.o \
	${OBJECTDIR}/util/timerecord.o \
	${OBJECTDIR}/util/logger/logger.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Release/GNU-Linux-x86/jaguar

dist/Release/GNU-Linux-x86/jaguar: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o dist/Release/GNU-Linux-x86/jaguar ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/util/threads.o: util/threads.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/util/threads.o util/threads.cpp

${OBJECTDIR}/util/util.o: util/util.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/util/util.o util/util.cpp

${OBJECTDIR}/network/networkservice.o: network/networkservice.cpp 
	${MKDIR} -p ${OBJECTDIR}/network
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/network/networkservice.o network/networkservice.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/util/cache.o: util/cache.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/util/cache.o util/cache.cpp

${OBJECTDIR}/util/timerecord.o: util/timerecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/util/timerecord.o util/timerecord.cpp

${OBJECTDIR}/util/logger/logger.o: util/logger/logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/util/logger
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/util/logger/logger.o util/logger/logger.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/jaguar

# Subprojects
.clean-subprojects:
