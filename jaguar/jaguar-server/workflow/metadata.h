/*
 * File:   metadata.h
 * Author: cross
 *
 * Created on November 22, 2008, 11:54 PM
 */

#include "wfcommon.h"
#include "metadata/processdefinition.h"

#include "dbjaguar.h"
#include "util.h"

using namespace dbjaguar;
// Forward declarations
/*
class ActivityCommon;
class Assignment;
class ConnectorSourceable;
class ConnectorTargetable;
class CommonConector;
class CommonEvent;
class Entity;
class Expression;
class Lane;
class Participant;
class ProcessDefinition;
class Property;
class Pool;
class Role;
class Task;
*/




/** General functions
*/

ProcessDefinition* getProcessDefinition(long id) throw (WorkflowException);
void loadProcessDefinitions(Connection* con);
void unloadProcessDefinitions();
