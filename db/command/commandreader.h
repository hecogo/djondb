#ifndef COMMANDREADER_H
#define COMMANDREADER_H

#include "inputstream.h"
#include "command.h"

class CommandReader
{
    public:
        /** Default constructor */
        CommandReader(InputStream* stream);
        CommandReader(const CommandReader& orig);

        /** Default destructor */
        virtual ~CommandReader();

        Command* readCommand();
    protected:
    private:
        InputStream* _stream;
};

#endif // COMMANDREADER_H
