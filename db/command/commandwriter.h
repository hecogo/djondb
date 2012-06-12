#ifndef COMMANDWRITER_H
#define COMMANDWRITER_H

#include "outputstream.h"
#include "command.h"

class UpdateCommand;
class InsertCommand;
class FindCommand;
class DropnamespaceCommand;
class ShutdownCommand;

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
		int writeFind(FindCommand* cmd, OutputStream* out);
		int writeInsert(InsertCommand* cmd, OutputStream* out);
		int writeDropnamespace(DropnamespaceCommand* cmd, OutputStream* out);
		int writeShutdown(ShutdownCommand* cmd, OutputStream* out);

	private:
		OutputStream* _stream;
};

#endif // COMMANDWRITER_H
