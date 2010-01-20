#ifndef WFRUNTIME_H_INCLUDED
#define WFRUNTIME_H_INCLUDED

#include "metadata.h"
#include "engine/processinstance.h"

// creates a new instance from the process definition
ProcessInstance* createProcessInstance(long definition);
ProcessInstance* processToken(long idProcessInstance, long idToken);

#endif
