#include "ASTNodes/TypeNode.h"

TypeNode::TypeNode(TokenPtr token)
{
	tokenPtr = token;
}

TokenPtr TypeNode::getTokenPtr()
{
	return tokenPtr;
}
