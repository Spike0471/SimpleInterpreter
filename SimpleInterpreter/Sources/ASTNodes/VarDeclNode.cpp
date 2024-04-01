#include "ASTNodes/VarDeclNode.h"

VarDeclNode::VarDeclNode(VarNodePtr vNode, TypeNodePtr tNode)
{
	varNodePtr = vNode;
	typeNodePtr = tNode;
}

VarNodePtr VarDeclNode::getVar()
{
	return varNodePtr;
}

TypeNodePtr VarDeclNode::getType()
{
	return typeNodePtr;
}
