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
LDLIBSOPTIONS=-Wl,-rpath ../common/dist/Debug/GNU-Linux-x86 -L../common/dist/Debug/GNU-Linux-x86 -lcommon -Wl,-rpath ../dbjaguar/dist/Debug/GNU-Linux-x86 -L../dbjaguar/dist/Debug/GNU-Linux-x86 -ldbjaguar -Wl,-rpath ../networkcommon/dist/Debug/GNU-Linux-x86 -L../networkcommon/dist/Debug/GNU-Linux-x86 -lnetworkcommon -Wl,-rpath ../workflow/dist/Debug/GNU-Linux-x86 -L../workflow/dist/Debug/GNU-Linux-x86 -lworkflow

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/tester

dist/Debug/GNU-Linux-x86/tester: ../common/dist/Debug/GNU-Linux-x86/libcommon.so

dist/Debug/GNU-Linux-x86/tester: ../dbjaguar/dist/Debug/GNU-Linux-x86/libdbjaguar.so

dist/Debug/GNU-Linux-x86/tester: ../networkcommon/dist/Debug/GNU-Linux-x86/libnetworkcommon.so

dist/Debug/GNU-Linux-x86/tester: ../workflow/dist/Debug/GNU-Linux-x86/libworkflow.so

dist/Debug/GNU-Linux-x86/tester: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lcpptest -lpthread -lmysqlclient -lz -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tester ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../common -I../dbjaguar -I../networkcommon -I../workflow -I/usr/include/mysql -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../common && ${MAKE}  -f Makefile CONF=Debug
	cd ../dbjaguar && ${MAKE}  -f Makefile CONF=Debug
	cd ../networkcommon && ${MAKE}  -f Makefile CONF=Debug
	cd ../workflow && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/tester

# Subprojects
.clean-subprojects:
	cd ../common && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../dbjaguar && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../networkcommon && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../workflow && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
