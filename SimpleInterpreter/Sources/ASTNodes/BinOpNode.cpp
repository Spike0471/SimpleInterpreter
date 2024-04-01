#include "ASTNodes/BinOpNode.h"
#include <iostream>
#include <string>
using namespace std;

BinOpNode::BinOpNode(ASTNodePtr l, TokenPtr ptr, ASTNodePtr r)
{
	leftNodePtr = l;
	rightNodePtr = r;
	opTokenPtr = ptr;
}

TokenPtr BinOpNode::getOpTokenPtr()
{
	return opTokenPtr;
}

ASTNodePtr BinOpNode::left()
{
	return leftNodePtr;
}

ASTNodePtr BinOpNode::right()
{
	return rightNodePtr;
}