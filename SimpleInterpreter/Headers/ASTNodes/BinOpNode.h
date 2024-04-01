#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include "Tokenizer/Token.h"

class BinOpNode : public AbstractSyntaxTreeNodeBase
{
private:
	ASTNodePtr leftNodePtr;
	ASTNodePtr rightNodePtr;
	TokenPtr opTokenPtr;
public:
	BinOpNode(ASTNodePtr l,TokenPtr ptr, ASTNodePtr r);
	TokenPtr getOpTokenPtr();
	ASTNodePtr left();
	ASTNodePtr right();

	GET_CLASS_NAME(BinOpNode)
};

