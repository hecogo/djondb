#ifndef SHUTDOWNCOMMAND_H
#define SHUTDOWNCOMMAND_H

#include "command.h"
#include "bson.h"
#include <vector>

class ShutdownCommand : public Command
{
    public:
        /** Default constructor */
        ShutdownCommand();
        /** Default destructor */
        virtual ~ShutdownCommand();
        /** Copy constructor
         *  \param other Object to copy from
         */
        ShutdownCommand(const ShutdownCommand& other);

        virtual void execute();
        virtual void* result();

        virtual void writeResult(OutputStream* out) const;

};

#endif // SHUTDOWNCOMMAND_H
