#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

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



#endif // ENTITY_H_INCLUDED
