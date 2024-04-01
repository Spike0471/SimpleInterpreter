#pragma once
#include <map>
#include <string>
#include "ASTNodes/AbstractSyntaxTreeNodeBase.h"
#include "Tokenizer/Token.h"
#include <functional>

#define DECLARE_VISITOR(NODE_NAME) TokenValue visit##NODE_NAME(ASTNodePtr nodePtr)
#define DEFINE_VISITOR(CLASS_NAME,NODE_NAME) TokenValue CLASS_NAME::visit##NODE_NAME(ASTNodePtr nodePtr)

#define ADD_TO_VISIT_MAP(NODE_NAME) visitMap[#NODE_NAME] = \
[this](ASTNodePtr nodePtr) -> TokenValue \
{ \
	return this->visit##NODE_NAME(nodePtr); \
}

class NodeVisitor
{
protected:
	std::map<std::string, std::function<TokenValue(ASTNodePtr)>> visitMap;
public:
	TokenValue visit(ASTNodePtr nodePtr);
};