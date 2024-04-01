#pragma once
#include "AbstractSyntaxTreeNodeBase.h"

class UnaryOpNode :public AbstractSyntaxTreeNodeBase
{
private:
	TokenPtr tokenPtr;
	ASTNodePtr rightNode;
public:
	UnaryOpNode(TokenPtr op,ASTNodePtr r);
	TokenPtr getOpTokenPtr();
	ASTNodePtr getRightNodePtr();

	GET_CLASS_NAME(UnaryOpNode)
};

