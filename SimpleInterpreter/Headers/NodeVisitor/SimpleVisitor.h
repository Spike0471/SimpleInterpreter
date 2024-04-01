#pragma once
#include "NodeVisitor/NodeVisitor.h"
#include "Parser/ASTParser.h"
#include "ASTNodes/ProgramNode.h"
#include "ASTNodes/BlockNode.h"
#include "ASTNodes/VarDeclNode.h"
#include "ASTNodes/TypeNode.h"
#include "ASTNodes/VarNode.h"
#include "ASTNodes/CompoundNode.h"
#include <memory>

class SimpleVisitor :public NodeVisitor
{
private:
	ASTParserPtr parserPtr;
private:
	DECLARE_VISITOR(ProgramNode);
	DECLARE_VISITOR(BlockNode);
	DECLARE_VISITOR(VarDeclNode);
	DECLARE_VISITOR(TypeNode);
	DECLARE_VISITOR(VarNode);
	DECLARE_VISITOR(CompoundNode);
public:
	SimpleVisitor(ASTParserPtr p);
	void printAll();
};

