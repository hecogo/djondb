#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T23:00:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = workflow
TEMPLATE = lib

DESTDIR = ../../lib

DEFINES += WORKFLOW_LIBRARY

INCLUDEPATH += . \
    ../common \
    ../dbjaguar \
    ../networkcommon \
    ../networkservice

SOURCES += \
    workflowcontroller.cpp \
    wfruntime.cpp \
    metadata.cpp \
    engine/tokenfacade.cpp \
    engine/token.cpp \
    engine/processinstance.cpp \
    metadata/masterentity.cpp \
    metadata/commonconnector.cpp

HEADERS +=\
        workflow_global.h \
    workflowcontroller.h \
    wfruntime.h \
    wfcommon.h \
    version.h \
    metadata.h \
    engine/tokenvo.h \
    engine/tokenfacade.h \
    engine/token.h \
    engine/taskvo.h \
    engine/processinstancevo.h \
    engine/processinstance.h \
    engine/defs.h \
    metadata/usertask.h \
    metadata/task.h \
    metadata/startevent.h \
    metadata/servicetask.h \
    metadata/sequenceflow.h \
    metadata/scripttask.h \
    metadata/role.h \
    metadata/referencetask.h \
    metadata/property.h \
    metadata/processdefinition.h \
    metadata/pool.h \
    metadata/participant.h \
    metadata/masterentity.h \
    metadata/manualtask.h \
    metadata/lane.h \
    metadata/expression.h \
    metadata/entitynotfoundexception.h \
    metadata/entity.h \
    metadata/endevent.h \
    metadata/defs.h \
    metadata/connectortargetable.h \
    metadata/connectorsourceable.h \
    metadata/commonevent.h \
    metadata/commonconnector.h \
    metadata/assignment.h \
    metadata/activitycommon.h
