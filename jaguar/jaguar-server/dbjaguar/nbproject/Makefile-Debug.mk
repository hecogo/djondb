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
	${OBJECTDIR}/mysql/resulset.o \
	${OBJECTDIR}/dbjaguar.o \
	${OBJECTDIR}/mysql/connection.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/libdbjaguar.so

dist/Debug/GNU-Linux-x86/libdbjaguar.so: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdbjaguar.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/mysql/resulset.o: nbproject/Makefile-${CND_CONF}.mk mysql/resulset.cpp 
	${MKDIR} -p ${OBJECTDIR}/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/mysql/resulset.o mysql/resulset.cpp

${OBJECTDIR}/dbjaguar.o: nbproject/Makefile-${CND_CONF}.mk dbjaguar.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/dbjaguar.o dbjaguar.cpp

${OBJECTDIR}/mysql/connection.o: nbproject/Makefile-${CND_CONF}.mk mysql/connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/mysql/connection.o mysql/connection.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/libdbjaguar.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
