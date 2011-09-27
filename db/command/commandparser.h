#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H


class Command;
class InputStream;

class CommandParser
{
    public:
        /** Default constructor */
        CommandParser();
        /** Default destructor */
        virtual ~CommandParser();

        Command* parse(InputStream* stream);

    protected:
    private:
};

#endif // COMMANDPARSER_H
