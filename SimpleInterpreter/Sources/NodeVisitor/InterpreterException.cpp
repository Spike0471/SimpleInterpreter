#include "NodeVisitor/InterpreterException.h"

InterpreterException::InterpreterException()
{
}

InterpreterException::InterpreterException(std::string content)
{
	errorContent = content;
}
