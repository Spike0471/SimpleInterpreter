#pragma once
#include "NodeVisitor.h"
#include "Parser/ASTParser.h"
#include "ASTNodes/CompoundNode.h"
#include "ASTNodes/NoOpNode.h"
#include "ASTNodes/AssignNode.h"
#include "ASTNodes/VarNode.h"
#include "ASTNodes/ProgramNode.h"
#include "ASTNodes/BlockNode.h"
#include "ASTNodes/VarDeclNode.h"
#include "ASTNodes/TypeNode.h"
#include "NodeVisitor/SymbolTableBuilder.h"
#include <string>

class Interpreter : public NodeVisitor
{
private:
	ASTParserPtr astParserPtr;
	SymbolTableBuilder symtableBuilder;
private:
	void raiseError(std::string content);

	DECLARE_VISITOR(NumNode);
	DECLARE_VISITOR(BinOpNode);
	DECLARE_VISITOR(UnaryOpNode);
	DECLARE_VISITOR(CompoundNode);
	DECLARE_VISITOR(NoOpNode);
	DECLARE_VISITOR(AssignNode);
	DECLARE_VISITOR(VarNode);

	DECLARE_VISITOR(ProgramNode);
	DECLARE_VISITOR(BlockNode);
	DECLARE_VISITOR(VarDeclNode);
	DECLARE_VISITOR(TypeNode);
	DECLARE_VISITOR(ProcedureDeclNode);
public:
	std::map<std::string, TokenValue> globalVariables;
public:
	Interpreter(std::string text);
	TokenValue interpret();
	void printAllSymbols();
};

