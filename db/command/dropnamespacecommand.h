#ifndef DROPNAMESPACECOMMAND_H 
#define DROPNAMESPACECOMMAND_H

#include "command.h"
#include "bson.h"

class DropnamespaceCommand: public Command {
    public:
        DropnamespaceCommand();

        virtual ~DropnamespaceCommand();
        DropnamespaceCommand(const DropnamespaceCommand& orig);

        virtual void execute();
        virtual void* result();
        virtual void writeResult(OutputStream* out) const;

        void setNameSpace(const std::string ns);
        const std::string* nameSpace() const;
    private:
        const std::string* _namespace;
};

#endif // DROPNAMESPACECOMMAND_H
