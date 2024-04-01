#pragma once
#include <string>

class LexerException
{
private:
	std::string errorContent;
public:
	LexerException();
	LexerException(std::string content);
};

