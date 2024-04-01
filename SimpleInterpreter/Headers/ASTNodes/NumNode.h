#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include "Tokenizer/Token.h"

class NumNode : public AbstractSyntaxTreeNodeBase
{
private:
	TokenPtr tokenPtr;
public:
	NumNode(TokenPtr p);
	TokenPtr getTokenPtr();

	GET_CLASS_NAME(NumNode)
};

