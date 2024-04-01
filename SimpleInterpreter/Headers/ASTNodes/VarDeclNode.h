#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include "VarNode.h"
#include "TypeNode.h"

class VarDeclNode : public AbstractSyntaxTreeNodeBase
{
private:
	VarNodePtr varNodePtr;
	TypeNodePtr typeNodePtr;
public:
	VarDeclNode(VarNodePtr vNode, TypeNodePtr tNode);
	VarNodePtr getVar();
	TypeNodePtr getType();

	GET_CLASS_NAME(VarDeclNode)
};

typedef std::shared_ptr<VarDeclNode> VarDeclNodePtr;