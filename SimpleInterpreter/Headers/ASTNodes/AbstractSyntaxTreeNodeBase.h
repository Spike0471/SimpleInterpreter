#pragma once
#include <memory>
#include <string>
#include "Tokenizer/Token.h"

#define GET_CLASS_NAME(CLASS_NAME) std::string getClassName(){ return #CLASS_NAME; }

class AbstractSyntaxTreeNodeBase
{
public:
	virtual std::string getClassName() = 0;
};

typedef std::shared_ptr<AbstractSyntaxTreeNodeBase> ASTNodePtr;