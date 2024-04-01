#include "Tokenizer/LexerException.h"

LexerException::LexerException()
{
}

LexerException::LexerException(std::string content)
{
	errorContent = content;
}
