#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include "dbcontroller.h"
#include "outputstream.h"

using namespace std;

class BSONObj;

enum COMMANDTYPE {
    INSERT,
    UPDATE,
    FINDBYKEY,
    FINDBYFILTER,
    CLOSECONNECTION
};

class Command {
    public:
        Command(COMMANDTYPE commandType);

        Command(const Command& orig);
        virtual ~Command();

        virtual void execute() = 0;
        virtual void* result() = 0;

        virtual void writeResult(OutputStream* out) const = 0;

        DBController* dbController() const {
            return  _dbController;
        }

        void setDBController(DBController* dbController) {
            _dbController = dbController;
        }

        COMMANDTYPE commandType() const;

    private:
        COMMANDTYPE _commandType;
        DBController* _dbController;
};

class CloseCommand: public Command {
    public:
        CloseCommand();

        CloseCommand(const CloseCommand& orig);
        virtual ~CloseCommand();

        virtual void execute();

        virtual void* result() {
            return NULL;
        }

        virtual void writeResult(OutputStream* out) const {};
};

class InsertCommand: public Command {
    public:
        InsertCommand();

        virtual ~InsertCommand();
        InsertCommand(const InsertCommand& orig);

        void setNameSpace(const std::string* ns) {
            _namespace = ns;
        }
        const std::string* nameSpace() const {
            return _namespace;
        }

        void setBSON(BSONObj* bson) {
            _bson = bson;
        }

        BSONObj* bson() const {
            return _bson;
        }

        virtual void execute();
        virtual void* result();
        virtual void writeResult(OutputStream* out) const;

    private:
        const std::string* _namespace;
        BSONObj* _bson;

        BSONObj* _bsonResult;
};


#endif // COMMAND_H_INCLUDED
