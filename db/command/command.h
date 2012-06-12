#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>

using namespace std;

class BSONObj;
class DBController;
class OutputStream;

enum COMMANDTYPE {
    INSERT,
    UPDATE,
    FIND,
    CLOSECONNECTION,
	 DROPNAMESPACE,
    SHUTDOWN
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



#endif // COMMAND_H_INCLUDED
