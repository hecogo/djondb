#ifndef INSERTCOMMAND_H
#define INSERTCOMMAND_H

#include "command.h"
#include "bson.h"

class InsertCommand: public Command {
    public:
        InsertCommand();

        virtual ~InsertCommand();
        InsertCommand(const InsertCommand& orig);


        virtual void execute();
        virtual void* result();
        virtual void writeResult(OutputStream* out) const;

        void setNameSpace(const std::string ns);
        const std::string* nameSpace() const;
        void setBSON(const BSONObj bson);
        BSONObj* bson() const;
    private:
        const std::string* _namespace;
        BSONObj* _bson;

        BSONObj* _bsonResult;
};

#endif // INSERTCOMMAND_H
