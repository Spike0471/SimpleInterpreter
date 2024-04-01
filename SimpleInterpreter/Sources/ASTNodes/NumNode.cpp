#include "ASTNodes/NumNode.h"
#include <iostream>
#include <variant>
using namespace std;

NumNode::NumNode(TokenPtr p)
{
	tokenPtr = p;
}

TokenPtr NumNode::getTokenPtr()
{
	return tokenPtr;
}