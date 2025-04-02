#pragma once
#include "NodeVisitor/NodeVisitor.h"
#include "Symbol/ScopedSymbolTable.h"
#include <exception>

class SemanticError : public std::exception
{
private:
	std::string errorMessage;

public:
	explicit SemanticError(std::string msg)
	{
		errorMessage = msg;
	}

	virtual const char *what() const noexcept override
	{
		return errorMessage.c_str();
	}
};

class SemanticAnalyzer : public NodeVisitor
{
private:
	ScopedSymbolTable scopedSymTable;

private:
	DECLARE_VISITOR(ProgramNode);
	DECLARE_VISITOR(BlockNode);
	DECLARE_VISITOR(BinOpNode);
	DECLARE_VISITOR(NumNode);
	DECLARE_VISITOR(UnaryOpNode);
	DECLARE_VISITOR(CompoundNode);
	DECLARE_VISITOR(NoOpNode);
	DECLARE_VISITOR(VarDeclNode);
	DECLARE_VISITOR(VarNode);
	DECLARE_VISITOR(TypeNode);
	DECLARE_VISITOR(AssignNode);
	DECLARE_VISITOR(ProcedureDeclNode);

	bool checkVariable(std::string varName);

public:
	SemanticAnalyzer();
	ScopedSymbolTable getSymbolTable() const;
};
