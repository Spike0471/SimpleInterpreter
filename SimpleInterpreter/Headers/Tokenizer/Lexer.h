#pragma once
#include <string>
#include <memory>
#include "Token.h"

class Lexer
{
private:
	size_t currentPos;
	std::string text;
	char currentChar;
private:
	void advance();
	void skipWhiteSpaces();
	void skipComments();
	TokenPtr number();
	bool isSpace(char c);
	bool isDigit(char c);
	void raiseError();
	char peek();
	TokenPtr id();
public:
	Lexer(std::string txt);
	TokenPtr getNextTokenPtr();
};

typedef std::shared_ptr<Lexer> LexerPtr;