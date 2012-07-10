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
        virtual void writeCommand(OutputStream* out) const;
        virtual void writeResult(OutputStream* out) const;
        virtual void readResult(InputStream* is);

        void setNameSpace(const std::string& ns);
        const std::string* nameSpace() const;
        void setDB(const std::string& db);
        const std::string* DB() const;
    private:
        const std::string* _namespace;
		  const std::string* _db;
		  bool _result;
};

#endif // DROPNAMESPACECOMMAND_H
