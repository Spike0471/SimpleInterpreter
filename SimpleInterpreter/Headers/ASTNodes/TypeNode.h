#pragma once
#include "AbstractSyntaxTreeNodeBase.h"

class TypeNode :public AbstractSyntaxTreeNodeBase
{
private:
	TokenPtr tokenPtr;
public:
	TypeNode(TokenPtr token);
	TokenPtr getTokenPtr();

	GET_CLASS_NAME(TypeNode)
};

typedef std::shared_ptr<TypeNode> TypeNodePtr;