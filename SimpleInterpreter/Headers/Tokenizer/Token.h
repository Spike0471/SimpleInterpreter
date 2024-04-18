#pragma once
#include <variant>
#include <string>
#include <memory>

typedef std::variant<int,float,std::string> TokenValue;

enum class TokenType {
	// reserved words
	TT_PROGRAM,
	TT_VAR,
	TT_INTEGER_DIV,
	TT_REAL,
	TT_INTEGER,
	TT_BEGIN,
	TT_END,
	TT_PROCEDURE,

	// consts
	TT_INTEGER_CONST,
	TT_REAL_CONST,

	// calc char
	TT_PLUS,
	TT_MINUS,
	TT_MULTI,
	TT_FLOAT_DIV,
	TT_LPAREN,
	TT_RPAREN,

	// syntax char
	TT_COLON,
	TT_COMMA,
	TT_SEMI,
	TT_DOT,
	TT_ASSIGN,

	// variable
	TT_ID,


	TT_EOF
};

class Token
{
private:
	TokenType tokenType;
	TokenValue tokenValue;
public:
	Token(TokenType t,TokenValue v);
	TokenType getType();
	TokenValue getValue();
};

typedef std::shared_ptr<Token> TokenPtr;

