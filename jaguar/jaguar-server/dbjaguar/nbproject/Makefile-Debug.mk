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
	${OBJECTDIR}/mysql/mysqlcommon.o \
	${OBJECTDIR}/mysql/mysqlresulset.o \
	${OBJECTDIR}/mysql/mysqlstatement.o \
	${OBJECTDIR}/mysql/mysqlconnection.o \
	${OBJECTDIR}/dbjaguar.o

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

${OBJECTDIR}/mysql/mysqlcommon.o: nbproject/Makefile-${CND_CONF}.mk mysql/mysqlcommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/mysql/mysqlcommon.o mysql/mysqlcommon.cpp

${OBJECTDIR}/mysql/mysqlresulset.o: nbproject/Makefile-${CND_CONF}.mk mysql/mysqlresulset.cpp 
	${MKDIR} -p ${OBJECTDIR}/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/mysql/mysqlresulset.o mysql/mysqlresulset.cpp

${OBJECTDIR}/mysql/mysqlstatement.o: nbproject/Makefile-${CND_CONF}.mk mysql/mysqlstatement.cpp 
	${MKDIR} -p ${OBJECTDIR}/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/mysql/mysqlstatement.o mysql/mysqlstatement.cpp

${OBJECTDIR}/mysql/mysqlconnection.o: nbproject/Makefile-${CND_CONF}.mk mysql/mysqlconnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/mysql
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/mysql/mysqlconnection.o mysql/mysqlconnection.cpp

${OBJECTDIR}/dbjaguar.o: nbproject/Makefile-${CND_CONF}.mk dbjaguar.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/mysql -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/dbjaguar.o dbjaguar.cpp

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
