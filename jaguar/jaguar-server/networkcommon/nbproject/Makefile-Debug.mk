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
	${OBJECTDIR}/networkservice.o \
	${OBJECTDIR}/net/response.o \
	${OBJECTDIR}/net/requestprocessor.o \
	${OBJECTDIR}/net/controller.o \
	${OBJECTDIR}/net/request.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/libnetworkcommon.so

dist/Debug/GNU-Linux-x86/libnetworkcommon.so: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworkcommon.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/networkservice.o: nbproject/Makefile-${CND_CONF}.mk networkservice.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/home/cross/workspace/jaguar/jaguar/jaguar-server/common -I/home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/networkservice.o networkservice.cpp

${OBJECTDIR}/net/response.o: nbproject/Makefile-${CND_CONF}.mk net/response.cpp 
	${MKDIR} -p ${OBJECTDIR}/net
	${RM} $@.d
	$(COMPILE.cc) -g -I/home/cross/workspace/jaguar/jaguar/jaguar-server/common -I/home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/net/response.o net/response.cpp

${OBJECTDIR}/net/requestprocessor.o: nbproject/Makefile-${CND_CONF}.mk net/requestprocessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/net
	${RM} $@.d
	$(COMPILE.cc) -g -I/home/cross/workspace/jaguar/jaguar/jaguar-server/common -I/home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/net/requestprocessor.o net/requestprocessor.cpp

${OBJECTDIR}/net/controller.o: nbproject/Makefile-${CND_CONF}.mk net/controller.cpp 
	${MKDIR} -p ${OBJECTDIR}/net
	${RM} $@.d
	$(COMPILE.cc) -g -I/home/cross/workspace/jaguar/jaguar/jaguar-server/common -I/home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/net/controller.o net/controller.cpp

${OBJECTDIR}/net/request.o: nbproject/Makefile-${CND_CONF}.mk net/request.cpp 
	${MKDIR} -p ${OBJECTDIR}/net
	${RM} $@.d
	$(COMPILE.cc) -g -I/home/cross/workspace/jaguar/jaguar/jaguar-server/common -I/home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/net/request.o net/request.cpp

# Subprojects
.build-subprojects:
	cd /home/cross/workspace/jaguar/jaguar/jaguar-server/common && ${MAKE}  -f Makefile CONF=Debug
	cd /home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/libnetworkcommon.so

# Subprojects
.clean-subprojects:
	cd /home/cross/workspace/jaguar/jaguar/jaguar-server/common && ${MAKE}  -f Makefile CONF=Debug clean
	cd /home/cross/workspace/jaguar/jaguar/jaguar-server/dbjaguar && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
