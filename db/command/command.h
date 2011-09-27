#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>

using namespace std;

class BSONObj;

enum COMMANDTYPE {
    INSERT,
    UPDATE,
    FINDBYKEY,
    FINDBYFILTER
};

class Command {
    public:
        Command(COMMANDTYPE commandType);

        Command(const Command& orig);
        virtual ~Command();

        virtual void execute() = 0;

        COMMANDTYPE commandType() const;

    private:
        COMMANDTYPE _commandType;
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

    private:
        const std::string* _namespace;
        BSONObj* _bson;
};


#endif // COMMAND_H_INCLUDED
