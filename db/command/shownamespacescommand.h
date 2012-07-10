#ifndef SHOWNAMESPACES_COMMAND_H 
#define SHOWNAMESPACES_COMMAND_H

#include "command.h"
#include "bson.h"
#include <string>
#include <vector>

class ShownamespacesCommand: public Command {
    public:
        ShownamespacesCommand();

        virtual ~ShownamespacesCommand();
        ShownamespacesCommand(const ShownamespacesCommand& orig);

        virtual void execute();
        virtual void* result();
        virtual void writeCommand(OutputStream* out) const;
        virtual void writeResult(OutputStream* out) const;
        virtual void readResult(InputStream* is);

        void setDB(const std::string& db);
        const std::string* DB() const;
    private:
		  const std::string* _db;
		  std::vector<std::string>* _results;
};

#endif // DSHOWNAMESPACES_COMMAND_H
