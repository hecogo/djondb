#ifndef COMMANDWRITER_H
#define COMMANDWRITER_H

#include "outputstream.h"
#include "command.h"

class UpdateCommand;
class InsertCommand;
class FindByKeyCommand;


class CommandWriter
{
    public:
        /** Default constructor */
        CommandWriter(OutputStream* out);
        CommandWriter(const CommandWriter& orig);
        /** Default destructor */
        virtual ~CommandWriter();

        int writeCommand(Command* cmd);
    protected:
    private:
	int writeUpdate(UpdateCommand* cmd, OutputStream* out);
	int writeFindByKey(FindByKeyCommand* cmd, OutputStream* out);
	int writeInsert(InsertCommand* cmd, OutputStream* out);

    private:
        OutputStream* _stream;
};

#endif // COMMANDWRITER_H
