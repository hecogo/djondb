#ifndef FINDBYKEYCOMMAND_H
#define FINDBYKEYCOMMAND_H

#include "command.h"
#include "bson.h"

class FindByKeyCommand : public Command
{
    public:
        /** Default constructor */
        FindByKeyCommand();
        /** Default destructor */
        virtual ~FindByKeyCommand();
        /** Copy constructor
         *  \param other Object to copy from
         */
        FindByKeyCommand(const FindByKeyCommand& other);

        virtual void execute();
        virtual void* result();

        virtual void writeResult(OutputStream* out) const;

        void setNameSpace(std::string ns);
        std::string nameSpace();
        void setBSON(BSONObj bson);
        BSONObj* bson() const;
    protected:
    private:
    private:
        std::string _namespace;
        BSONObj* _bson;

        BSONObj* _bsonResult;
};

#endif // FINDBYKEYCOMMAND_H
