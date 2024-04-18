#include "Tokenizer/Lexer.h"
#include "Tokenizer/LexerException.h"
#include <ctype.h>
#include <map>
using namespace std;

static const std::map<std::string, TokenPtr> RESERVED_WORDS =
{
	{"PROGRAM",make_shared<Token>(TokenType::TT_PROGRAM,"PROGRAM")},
	{"VAR",make_shared<Token>(TokenType::TT_VAR,"VAR")},
	{"DIV",make_shared<Token>(TokenType::TT_INTEGER_DIV,"DIV")},
	{"INTEGER",make_shared<Token>(TokenType::TT_INTEGER,"INTEGER")},
	{"REAL",make_shared<Token>(TokenType::TT_REAL,"REAL")},
	{"BEGIN",make_shared<Token>(TokenType::TT_BEGIN,"BEGIN")},
	{"END",make_shared<Token>(TokenType::TT_END,"END") },
	{"PROCEDURE",make_shared<Token>(TokenType::TT_PROCEDURE,"PROCEDURE") },
};

void Lexer::advance()
{
	currentPos += 1;
	if (currentPos >= strlen(text.c_str()))
	{
		currentChar = '\0';
		return;
	}
	currentChar = text.c_str()[currentPos];
}

void Lexer::skipWhiteSpaces()
{
	while (isSpace(currentChar))
	{
		advance();
	}
}

void Lexer::skipComments()
{
	while (currentChar != '}') 
	{
		advance();
	}
	advance();
}

TokenPtr Lexer::number()
{
	std::string result = "";
	while (isDigit(currentChar)) 
	{
		result += currentChar;
		advance();
	}
	if (currentChar == '.') 
	{
		result += currentChar;
		advance();
		while (isDigit(currentChar))
		{
			result += currentChar;
			advance();
		}
		return make_shared<Token>(TokenType::TT_REAL_CONST,std::stof(result));
	}
	return make_shared<Token>(TokenType::TT_INTEGER_CONST,std::stoi(result));
}

bool Lexer::isSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

bool Lexer::isDigit(char c)
{
	return c >= '0' && c <= '9';
}

void Lexer::raiseError()
{
	throw LexerException();
}

char Lexer::peek()
{
	if (currentPos + 1 >= strlen(text.c_str()))
	{
		return NULL;
	}
	return text.c_str()[currentPos + 1];
}

TokenPtr Lexer::id()
{
	std::string result = "";
	while (isalnum(currentChar)) 
	{
		result += currentChar;
		advance();
	}
	if (RESERVED_WORDS.find(result) == RESERVED_WORDS.end()) 
	{
		return make_shared<Token>(TokenType::TT_ID,result);
	}
	else 
	{
		return RESERVED_WORDS.at(result);
	}
}

Lexer::Lexer(std::string txt) :text(txt)
{
	currentChar = txt.c_str()[0];
	currentPos = 0;
}

TokenPtr Lexer::getNextTokenPtr()
{
	while (currentChar != '\0' && currentPos < strlen(text.c_str()))
	{
		if (isSpace(currentChar))
		{
			skipWhiteSpaces();
		}

		if (currentChar == '{') 
		{
			advance();
			skipComments();
			continue;
		}

		if (currentChar == '\0') 
		{
			return make_shared<Token>(TokenType::TT_EOF,NULL);
		}

		TokenType tokenType;
		TokenValue tokenValue;

		if (isDigit(currentChar))
		{
			return number();
		}

		if (isalpha(currentChar)) 
		{
			return id();
		}

		switch (currentChar)
		{
		case ',':
			tokenType = TokenType::TT_COMMA;
			tokenValue = ",";
			break;
		case '.':
			tokenType = TokenType::TT_DOT;
			tokenValue = ".";
			break;
		case ':':
			if (peek() == '=') 
			{
				advance();
				tokenType = TokenType::TT_ASSIGN;
				tokenValue = ":=";
			}
			else 
			{
				tokenType = TokenType::TT_COLON;
				tokenValue = ":";
			}
			break;
		case ';':
			tokenType = TokenType::TT_SEMI;
			tokenValue = ";";
			break;
		case '+':
			tokenType = TokenType::TT_PLUS;
			tokenValue = "+";
			break;
		case '-':
			tokenType = TokenType::TT_MINUS;
			tokenValue = "-";
			break;
		case '*':
			tokenType = TokenType::TT_MULTI;
			tokenValue = "*";
			break;
		case '/':
			tokenType = TokenType::TT_FLOAT_DIV;
			tokenValue = "/";
			break;
		case '(':
			tokenType = TokenType::TT_LPAREN;
			tokenValue = "(";
			break;
		case ')':
			tokenType = TokenType::TT_RPAREN;
			tokenValue = ")";
			break;
		default:
			raiseError();
			break;
		}

		advance();
		return make_shared<Token>(tokenType, tokenValue);
	}
	return make_shared<Token>(TokenType::TT_EOF, NULL);
}
