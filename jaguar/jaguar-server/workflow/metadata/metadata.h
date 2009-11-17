/*
 * File:   metadata.h
 * Author: cross
 *
 * Created on November 22, 2008, 11:54 PM
 */

#include <vector>
#include "../wfcommon.h"
#include "dbjaguar.h"
#include "util/util.h"

using namespace std;
using namespace dbjaguar;

enum ActivityStatus {
    NONE_ACTIVITYSTATUS,
    READY_ACTIVITYSTATUS,
    ACTIVE_ACTIVITYSTATUS,
    CANCELLED_ACTIVITYSTATUS,
    ABORTING_ACTIVITYSTATUS,
    ABORTED_ACTIVITYSTATUS,
    COMPLETING_ACTIVITYSTATUS,
    COMPLETED_ACTIVITYSTATUS
};

enum ActivityType {
    TASK_ACTIVITYTYPE,
    SUBPROCESS_ACTIVITYTYPE
};

enum AssignTime {
    START_ASSIGNTIME,
    END_ASSIGNTIME
};

enum ConditionType {
    NONE_CONDITIONTYPE,
    EXPRESSION_CONDITIONTYPE,
    DEFAULT_CONDITIONTYPE
};

enum EventType {
    START_EVENTTYPE,
    END_EVENTTYPE,
    INTERMEDIATE_EVENTTYPE
};

enum LoopType {
    NONE_LOOPTYPE,
    STANDARD_LOOPTYPE,
    MULTIINSTANCE_LOOPTYPE
};

enum ParticipantType {
    ROLE_PARTICIPANTTYPE,
    ENTITY_PARTICIPANTTYPE
};

enum ProcessType {
    NONE_PROCESSTYPE,
    PRIVATE_PROCESSTYPE,
    ABSTRACT_PROCESSTYPE,
    COLLABORATION_PROCESSTYPE
};

enum PropertyType {
    INT_PROPERTYTYPE,
    STRING_PROPERTYTYPE,
    SET_PROPERTYTYPE
};

enum TaskType {
    SERVICE_TASKTYPE,
    RECEIVE_TASKTYPE,
    SEND_TASKTYPE,
    USER_TASKTYPE,
    SCRIPT_TASKTYPE,
    MANUAL_TASKTYPE,
    REFERENCE_TASKTYPE,
    NONE_TASKTYPE
};

enum Trigger {
    NONE_TRIGGER,
    MESSAGE_TRIGGER,
    TIMER_TRIGGER,
    RULE_TRIGGER,
    LINK_TRIGGER,
    MULTIPLE_TRIGGER
};

// Forward declarations
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

class ActivityCommon {
private:
    long id;
    ActivityType* activityType;
    ActivityStatus* status;
    int startQuantity; // Number of tokens required to start the activity
    LoopType* loopType;
    ProcessDefinition* processDefinition;

public:
    ActivityCommon() {
        startQuantity = 1;
    }

    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    ActivityType* getActivityType() {
        return activityType;
    }

    void setActivityType(ActivityType* _activityType) {
        activityType = _activityType;
    }

    ActivityStatus* getStatus() {
        return status;
    }

    void setStatus(ActivityStatus* _status) {
        status = _status;
    }

    int getStartQuantity() {
        return startQuantity;
    }

    void setStartQuantity(int _startQuantity) {
        startQuantity = _startQuantity;
    }

    LoopType* getLoopType() {
        return loopType;
    }

    void setLoopType(LoopType* _loopType) {
        loopType = _loopType;
    }

    ProcessDefinition* getProcessDefinition() {
        return processDefinition;
    }

    void setProcessDefinition(ProcessDefinition* _processDefinition) {
        processDefinition = _processDefinition;
    }
};

class Assignment {
private:
    long id;
    Property* assignmentTo;
    Expression* assignmentFrom;
    AssignTime* assignTime;
    Expression* expression;
    CommonEvent* event;

public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    Property* getAssignmentTo() {
        return assignmentTo;
    }

    void setAssignmentTo(Property* _assignmentTo) {
        assignmentTo = _assignmentTo;
    }

    Expression* getAssignmentFrom() {
        return assignmentFrom;
    }

    void setAssignmentFrom(Expression* _assignmentFrom) {
        assignmentFrom = _assignmentFrom;
    }

    AssignTime* getAssignTime() {
        return assignTime;
    }

    void setAssignTime(AssignTime* _assignTime) {
        assignTime = _assignTime;
    }

    Expression* getExpression() {
        return expression;
    }

    void setExpression(Expression* _expression) {
        expression = _expression;
    }

    CommonEvent* getEvent() {
        return event;
    }

    void setEvent(CommonEvent* _event) {
        event = _event;
    }
};

class ConnectorSourceable {
};

class ConnectorTargetable {
};


class CommonConector {
private:
    long id;
    string* connectorName;
    Task* taskSource;
    Task* taskTarget;
    CommonEvent* eventSource;
    CommonEvent* eventTarget;

public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getConnectorName() {
        return connectorName;
    }

    void setConnectorName(string* _connectorName) {
        connectorName = _connectorName;
    }

    Task* getTaskSource() {
        return taskSource;
    }

    void setTaskSource(Task* _taskSource) {
        taskSource = _taskSource;
    }

    Task* getTaskTarget() {
        return taskTarget;
    }

    void setTaskTarget(Task* _taskTarget) {
        taskTarget = _taskTarget;
    }

    CommonEvent* getEventSource() {
        return eventSource;
    }

    void setEventSource(CommonEvent* _eventSource) {
        eventSource = _eventSource;
    }

    CommonEvent* getEventTarget() {
        return eventTarget;
    }

    void setEventTarget(CommonEvent* _eventTarget) {
        eventTarget = _eventTarget;
    }
};

class CommonEvent : public ConnectorSourceable , public ConnectorTargetable {
private:
    vector<CommonConector*>* sequenceFlows;
    long id;
    EventType* eventType;
    vector<Assignment*>* assigments;
    Pool* pool;
    ProcessDefinition* processDefinition;

public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    EventType* getEventType() {
        return eventType;
    }

    void setEventType(EventType* _eventType) {
        eventType = _eventType;
    }

    Pool* getPool() {
        return pool;
    }

    void setPool(Pool* _pool) {
        pool = _pool;
    }

    vector<CommonConector*>* getSequenceFlows() {
        return sequenceFlows;
    }

    void setSequenceFlows(vector<CommonConector*>* _sequenceFlows) {
        sequenceFlows = _sequenceFlows;
    }

    vector<Assignment*>* getAssigments() {
        return assigments;
    }

    void setAssigments(vector<Assignment*>* _assigments) {
        assigments = _assigments;
    }

    ProcessDefinition* getProcessDefinition() {
        return processDefinition;
    }

    void setProcessDefinition(ProcessDefinition* _processDefinition) {
        processDefinition = _processDefinition;
    }
};

class EndEvent : CommonEvent {
public:
    EndEvent() {}
};

class Entity {
private:
    long id;
    string* entityName;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getEntityName() {
        return entityName;
    }

    void setEntityName(string* _entityName) {
        entityName = _entityName;
    }
};

class EntityNotFoundException : public exception  {
private:
    string* message;
public:
    EntityNotFoundException(string *_message);
    virtual const char* what() const throw ();
};

class Expression {
private:
    long id;
    string* expression;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getExpression() {
        return expression;
    }

    void setExpression(string* _expression) {
        expression = _expression;
    }
};

class ProcessDefinition {
private:
    long id;
    string* definitionName;
    ProcessType* processType;
    vector<Property*>* properties;
    vector<CommonEvent*>* events;
    vector<Pool*>* pools;
    vector<ActivityCommon*>* tasks;
    string* masterEntity;
public:
    ProcessType* getProcessType() {
        return processType;
    }

    void setProcessType(ProcessType* _processType) {
        processType = _processType;
    }

    vector<Property*>* getProperties() {
        return properties;
    }

    void setProperties(vector<Property*>* _properties) {
        properties = _properties;
    }

    vector<Pool*>* getPools() {
        return pools;
    }

    void setPools(vector<Pool*>* _pools) {
        pools = _pools;
    }

    string* getDefinitionName() {
        return definitionName;
    }

    void setDefinitionName(string* _definitionName) {
        definitionName = _definitionName;
    }

    vector<ActivityCommon*>* getTasks() {
        return tasks;
    }

    void setTasks(vector<ActivityCommon*>* _tasks) {
        tasks = _tasks;
    }

    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    vector<CommonEvent*>* getEvents() {
        return events;
    }

    void setEvents(vector<CommonEvent*>* _events) {
        events = _events;
    }

    string* getMasterEntity() {
        return masterEntity;
    }

    void setMasterEntity(string* _masterEntity) {
        masterEntity = _masterEntity;
    }
};

class Property {
private:
    long id;
    string* propertyName;
    PropertyType* propertyType;
    ProcessDefinition* processDefinition;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getPropertyName() {
        return propertyName;
    }

    void setPropertyName(string* _propertyName) {
        propertyName = _propertyName;
    }

    PropertyType* getPropertyType() {
        return propertyType;
    }

    void setPropertyType(PropertyType* _propertyType) {
        propertyType = _propertyType;
    }
};

class Lane {
private:
    long id;
    Pool* parentPool;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    Pool* getParentPool() {
        return parentPool;
    }

    void setParentPool(Pool* _parentPool) {
        parentPool = _parentPool;
    }

};

class Pool {
private:
    long id;
    string* poolName;
    vector<Lane*>* lanes;
    Participant* participant;
    ProcessDefinition* processDefinition;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getPoolName() {
        return poolName;
    }

    void setPoolName(string* _poolName) {
        poolName = _poolName;
    }

    vector<Lane*>* getLanes() {
        return lanes;
    }

    void setLanes(vector<Lane*>* _lanes) {
        lanes = _lanes;
    }

    Participant* getParticipant() {
        return participant;
    }

    void setParticipant(Participant* _participant) {
        participant = _participant;
    }

    ProcessDefinition* getProcessDefinition() {
        return processDefinition;
    }

    void setProcessDefinition(ProcessDefinition* _processDefinition) {
        processDefinition = _processDefinition;
    }
};

class Participant {
private:
    long id;
    ParticipantType* participantType;
    Role* participantRole;
    Entity* entity;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    ParticipantType* getParticipantType() {
        return participantType;
    }

    void setParticipantType(ParticipantType* _participantType) {
        participantType = _participantType;
    }

    Role* getParticipantRole() {
        return participantRole;
    }

    void setParticipantRole(Role* _participantRole) {
        participantRole = _participantRole;
    }

    Entity* getEntity() {
        return entity;
    }

    void setEntity(Entity* _entity) {
        entity = _entity;
    }
};

class Role {
private:
    long id;
    string* roleName;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getRoleName() {
        return roleName;
    }

    void setRoleName(string* _roleName) {
        roleName = _roleName;
    }
};

class Task : public ConnectorSourceable, public ConnectorTargetable, public ActivityCommon {
private:
    vector<CommonConector*>* sequenceFlows;
    TaskType* taskType;
    string* taskName;
public:
    TaskType* getTaskType() {
        return taskType;
    }

    void setTaskType(TaskType* _taskType) {
        taskType = _taskType;
    }

    vector<CommonConector*>* getSequenceFlows() {
        return sequenceFlows;
    }

    void setSequenceFlows(vector<CommonConector*>* _sequenceFlows) {
        sequenceFlows = _sequenceFlows;
    }

    string* getTaskName() {
        return taskName;
    }

    void setTaskName(string* _taskName) {
        taskName = _taskName;
    }

};

class ManualTask : public Task {
private:
    vector<void*>* performers;
public:
    vector<void*>* getPerformers() {
        return performers;
    }

    void setPerformers(vector<void*>* _performers) {
        performers = _performers;
    }
};

class ReferenceTask : Task {
private:
    Task* taskRef;
public:
    Task* getTaskRef() {
        return taskRef;
    }

    void setTaskRef(Task* _taskRef) {
        taskRef = _taskRef;
    }
};

class ScriptTask : Task {
private:
    string* script;
public:
    string* getScript() {
        return script;
    }

    void setScript(string* _script) {
        script = _script;
    }
};

class SequenceFlow : CommonConector {
private:
    ConditionType* conditionType;
    Expression* conditionExpression;
    int quantity;
public:
    ConditionType* getConditionType() {
        return conditionType;
    }

    void setConditionType(ConditionType* _conditionType) {
        conditionType = _conditionType;
    }

    Expression* getConditionExpression() {
        return conditionExpression;
    }

    void setConditionExpression(Expression* _conditionExpression) {
        conditionExpression = _conditionExpression;
    }

    int getQuantity() {
        return quantity;
    }

    void setQuantity(int _quantity) {
        quantity = _quantity;
    }
};

class ServiceTask : public Task {
};

class StartEvent : public CommonEvent {
private:
    Trigger* startTrigger;
public:
    StartEvent() {};
    Trigger* getStartTrigger() {
        return startTrigger;
    }

    void setStartTrigger(Trigger* _startTrigger) {
        startTrigger = _startTrigger;
    }
};

class UserTask : public Task {
private:
    vector<void*>* performers;
public:
    vector<void*>* getPerformers() {
        return performers;
    }

    void setPerformers(vector<void*>* _performers) {
        performers = _performers;
    }
};


/** General functions
*/

ProcessDefinition* getProcessDefinition(long id) throw (WorkflowException);
void loadProcessDefinitions(Connection* con);
