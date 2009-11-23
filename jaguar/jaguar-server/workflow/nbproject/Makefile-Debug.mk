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
	${OBJECTDIR}/engine/tokenfacade.o \
	${OBJECTDIR}/metadata/masterentity.o \
	${OBJECTDIR}/engine/processinstance.o \
	${OBJECTDIR}/engine/token.o \
	${OBJECTDIR}/workflowcontroller.o \
	${OBJECTDIR}/wfruntime.o \
	${OBJECTDIR}/metadata.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/libworkflow.so

dist/Debug/GNU-Linux-x86/libworkflow.so: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libworkflow.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/engine/tokenfacade.o: nbproject/Makefile-${CND_CONF}.mk engine/tokenfacade.cpp 
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/engine/tokenfacade.o engine/tokenfacade.cpp

${OBJECTDIR}/metadata/masterentity.o: nbproject/Makefile-${CND_CONF}.mk metadata/masterentity.cpp 
	${MKDIR} -p ${OBJECTDIR}/metadata
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/metadata/masterentity.o metadata/masterentity.cpp

${OBJECTDIR}/engine/processinstance.o: nbproject/Makefile-${CND_CONF}.mk engine/processinstance.cpp 
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/engine/processinstance.o engine/processinstance.cpp

${OBJECTDIR}/engine/token.o: nbproject/Makefile-${CND_CONF}.mk engine/token.cpp 
	${MKDIR} -p ${OBJECTDIR}/engine
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/engine/token.o engine/token.cpp

${OBJECTDIR}/workflowcontroller.o: nbproject/Makefile-${CND_CONF}.mk workflowcontroller.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/workflowcontroller.o workflowcontroller.cpp

${OBJECTDIR}/wfruntime.o: nbproject/Makefile-${CND_CONF}.mk wfruntime.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/wfruntime.o wfruntime.cpp

${OBJECTDIR}/metadata.o: nbproject/Makefile-${CND_CONF}.mk metadata.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/metadata.o metadata.cpp

# Subprojects
.build-subprojects:
	cd ../common && ${MAKE}  -f Makefile CONF=Debug
	cd ../dbjaguar && ${MAKE}  -f Makefile CONF=Debug
	cd ../networkcommon && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/libworkflow.so

# Subprojects
.clean-subprojects:
	cd ../common && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../dbjaguar && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../networkcommon && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
