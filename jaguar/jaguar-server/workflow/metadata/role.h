#ifndef ROLE_H_INCLUDED
#define ROLE_H_INCLUDED

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



#endif // ROLE_H_INCLUDED
