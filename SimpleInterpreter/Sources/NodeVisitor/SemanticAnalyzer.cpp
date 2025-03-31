#include "NodeVisitor/SemanticAnalyzer.h"
#include "ASTNodes/VarDeclNode.h"
#include "ASTNodes/ProgramNode.h"
#include "ASTNodes/BlockNode.h"
#include "ASTNodes/AssignNode.h"
#include "ASTNodes/BinOpNode.h"
#include "ASTNodes/UnaryOpNode.h"
#include "Symbol/VarSymbol.h"

#define SEMANTIC_ANALYZER_VISITOR(NODE_NAME) DEFINE_VISITOR(SemanticAnalyzer,NODE_NAME)

SEMANTIC_ANALYZER_VISITOR(ProgramNode)
{
	auto programNodePtr = std::dynamic_pointer_cast<ProgramNode>(nodePtr);
	this->visit(programNodePtr->getBlockNodePtr());
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(BlockNode)
{
	auto blockNodePtr = std::dynamic_pointer_cast<BlockNode>(nodePtr);
	for (auto declNode : blockNodePtr->getDeclarations())
	{
		this->visit(declNode);
	}
	this->visit(blockNodePtr->getCompound());
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(BinOpNode)
{
	auto binOpNodePtr = std::dynamic_pointer_cast<BinOpNode>(nodePtr);
	auto left = binOpNodePtr->left();
	auto right = binOpNodePtr->right();
	if (left->getClassName() == "VarNode") 
	{
		checkVariable(std::get<std::string>(this->visit(left)));
	}

	if (right->getClassName() == "VarNode")
	{
		checkVariable(std::get<std::string>(this->visit(right)));
	}
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(NumNode)
{
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(UnaryOpNode)
{
	auto unaryOpNodePtr = std::dynamic_pointer_cast<UnaryOpNode>(nodePtr);
	auto right = unaryOpNodePtr->getRightNodePtr();
	if (right->getClassName() == "VarNode")
	{
		checkVariable(std::get<std::string>(this->visit(right)));
	}
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(CompoundNode)
{
	auto compoundNodePtr = std::dynamic_pointer_cast<CompoundNode>(nodePtr);
	for (auto child : compoundNodePtr->getChildren())
	{
		this->visit(child);
	}
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(NoOpNode)
{
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(VarDeclNode)
{
	auto varDeclNodePtr = std::dynamic_pointer_cast<VarDeclNode>(nodePtr);
	auto varNodePtr = varDeclNodePtr->getVar();
	std::string varName = std::get<std::string>(this->visit(varNodePtr));
	auto typeNodePtr = varDeclNodePtr->getType();
	std::string typeName = std::get<std::string>(this->visit(typeNodePtr));
	auto typeSymbol = this->symTable.lookup(typeName);
	if (this->symTable.lookup(varName) != NULL)
	{
		throw SemanticError("Variable name redefined: " + varName);
		return TokenValue(0);
	}

	if (typeSymbol == NULL)
	{
		throw SemanticError("Type name not defined:" + typeName);
		return TokenValue(0);
	}

	symTable.define(std::make_shared<VarSymbol>(varName, typeSymbol));
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(VarNode)
{
	auto varNodePtr = std::dynamic_pointer_cast<VarNode>(nodePtr);
	return varNodePtr->getTokenPtr()->getValue();
}

SEMANTIC_ANALYZER_VISITOR(TypeNode)
{
	auto typeNodePtr = std::dynamic_pointer_cast<TypeNode>(nodePtr);
	return typeNodePtr->getTokenPtr()->getValue();
}

SEMANTIC_ANALYZER_VISITOR(AssignNode)
{
	auto assignNodePtr = std::dynamic_pointer_cast<AssignNode>(nodePtr);
	std::string varName = std::get<std::string>(this->visit(assignNodePtr->getLeftPtr()));
	checkVariable(varName);
	auto rightNodePtr = assignNodePtr->getRightPtr();
	if (rightNodePtr->getClassName() == "VarNode") 
	{
		checkVariable(std::get<std::string>(this->visit(rightNodePtr)));
	}
	else 
	{
		this->visit(rightNodePtr);
	}
	return TokenValue(0);
}

SEMANTIC_ANALYZER_VISITOR(ProcedureDeclNode)
{
	return TokenValue(0);
}

bool SemanticAnalyzer::checkVariable(std::string varName)
{
	if (symTable.lookup(varName) == NULL)
	{
		throw SemanticError("Variable not defined: " + varName);
		return false;
	}
	return true;
}

SemanticAnalyzer::SemanticAnalyzer()
{
	ADD_TO_VISIT_MAP(ProgramNode);
	ADD_TO_VISIT_MAP(BlockNode);
	ADD_TO_VISIT_MAP(BinOpNode);
	ADD_TO_VISIT_MAP(NumNode);
	ADD_TO_VISIT_MAP(UnaryOpNode);
	ADD_TO_VISIT_MAP(CompoundNode);
	ADD_TO_VISIT_MAP(NoOpNode);
	ADD_TO_VISIT_MAP(VarDeclNode);
	ADD_TO_VISIT_MAP(VarNode);
	ADD_TO_VISIT_MAP(TypeNode);
	ADD_TO_VISIT_MAP(AssignNode);
	ADD_TO_VISIT_MAP(ProcedureDeclNode);
}

SymbolTable SemanticAnalyzer::getSymbolTable() const
{
	return symTable;
}
