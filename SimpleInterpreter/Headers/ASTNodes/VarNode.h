#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include "Tokenizer/Token.h"

class VarNode : public AbstractSyntaxTreeNodeBase
{
private:
	TokenPtr tokenPtr;
public:
	VarNode(TokenPtr ptr);
	TokenPtr getTokenPtr();

	GET_CLASS_NAME(VarNode)
};

typedef std::shared_ptr<VarNode> VarNodePtr;