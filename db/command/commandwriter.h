#ifndef COMMANDWRITER_H
#define COMMANDWRITER_H

#include "outputstream.h"
#include "command.h"

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
        OutputStream* _stream;
};

#endif // COMMANDWRITER_H
