#pragma once
#include "AbstractSyntaxTreeNodeBase.h"

class AssignNode : public AbstractSyntaxTreeNodeBase
{
private:
	ASTNodePtr left;
	ASTNodePtr right;
	TokenPtr opTokenPtr;
public:
	AssignNode(ASTNodePtr l, TokenPtr op, ASTNodePtr r);
	ASTNodePtr getLeftPtr();
	ASTNodePtr getRightPtr();
	TokenPtr getOpTokenPtr();

	GET_CLASS_NAME(AssignNode)
};