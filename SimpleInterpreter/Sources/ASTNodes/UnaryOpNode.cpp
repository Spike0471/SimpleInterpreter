#include "ASTNodes/UnaryOpNode.h"

UnaryOpNode::UnaryOpNode(TokenPtr op, ASTNodePtr r)
{
	tokenPtr = op;
	rightNode = r;
}

TokenPtr UnaryOpNode::getOpTokenPtr()
{
	return tokenPtr;
}

ASTNodePtr UnaryOpNode::getRightNodePtr()
{
	return rightNode;
}
