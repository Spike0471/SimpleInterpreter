#include "Tokenizer/Token.h"

Token::Token(TokenType t, TokenValue v) :tokenType(t), tokenValue(v)
{
}

TokenType Token::getType()
{
	return tokenType;
}

TokenValue Token::getValue()
{
	return tokenValue;
}
