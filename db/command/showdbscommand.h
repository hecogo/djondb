#ifndef SHOWDBS_COMMAND_H 
#define SHOWDBS_COMMAND_H

#include "command.h"
#include "bson.h"
#include <string>
#include <vector>

class ShowdbsCommand: public Command {
    public:
        ShowdbsCommand();

        virtual ~ShowdbsCommand();
        ShowdbsCommand(const ShowdbsCommand& orig);

        virtual void execute();
        virtual void* result();
        virtual void writeCommand(OutputStream* out) const;
        virtual void writeResult(OutputStream* out) const;
        virtual void readResult(InputStream* is);
    private:
		  std::vector<std::string>* _results;
};

#endif // SHOWDBS_COMMAND_H
