#include "ASTNodes/VarNode.h"

VarNode::VarNode(TokenPtr ptr)
{
	tokenPtr = ptr;
}

TokenPtr VarNode::getTokenPtr()
{
	return tokenPtr;
}
