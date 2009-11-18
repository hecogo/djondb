#ifndef PARTICIPANT_H_INCLUDED
#define PARTICIPANT_H_INCLUDED

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



#endif // PARTICIPANT_H_INCLUDED
