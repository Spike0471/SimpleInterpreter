#include "ASTNodes/AssignNode.h"

AssignNode::AssignNode(ASTNodePtr l, TokenPtr op, ASTNodePtr r)
{
	left = l;
	opTokenPtr = op;
	right = r;
}

ASTNodePtr AssignNode::getLeftPtr()
{
	return left;
}

ASTNodePtr AssignNode::getRightPtr()
{
	return right;
}

TokenPtr AssignNode::getOpTokenPtr()
{
	return opTokenPtr;
}
