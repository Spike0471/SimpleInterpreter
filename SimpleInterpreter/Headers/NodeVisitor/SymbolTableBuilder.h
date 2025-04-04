#pragma once
#include "NodeVisitor/NodeVisitor.h"
#include "ASTNodes/ProgramNode.h"
#include "ASTNodes/BlockNode.h"
#include "ASTNodes/BinOpNode.h"
#include "ASTNodes/NumNode.h"
#include "ASTNodes/UnaryOpNode.h"
#include "ASTNodes/CompoundNode.h"
#include "ASTNodes/NoOpNode.h"
#include "ASTNodes/VarDeclNode.h"
#include "ASTNodes/VarNode.h"
#include "ASTNodes/AssignNode.h"
#include "Symbol/ScopedSymbolTable.h"
#include "ASTNodes/ProcedureDeclNode.h"

class SymbolTableBuilder : public NodeVisitor
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
	DECLARE_VISITOR(AssignNode);
	DECLARE_VISITOR(ProcedureDeclNode);
public:
	SymbolTableBuilder();
	ScopedSymbolTable getSymbolTable() const;
};

