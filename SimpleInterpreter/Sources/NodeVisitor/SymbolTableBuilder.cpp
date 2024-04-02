#include "NodeVisitor/SymbolTableBuilder.h"
#include "Symbol/VarSymbol.h"

#define SYM_TABLE_BUILDER_VISITOR(NODE_NAME) DEFINE_VISITOR(SymbolTableBuilder,NODE_NAME)

SymbolTableBuilder::SymbolTableBuilder()
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
	ADD_TO_VISIT_MAP(AssignNode);
}

SymbolTable SymbolTableBuilder::getSymbolTable() const
{
	return symTable;
}

SYM_TABLE_BUILDER_VISITOR(ProgramNode)
{
	auto node = std::dynamic_pointer_cast<ProgramNode>(nodePtr);
	return this->visit(node->getBlockNodePtr());
}

SYM_TABLE_BUILDER_VISITOR(BlockNode)
{
	auto node = std::dynamic_pointer_cast<BlockNode>(nodePtr);
	for (auto decl : node->getDeclarations()) 
	{
		this->visit(decl);
	}
	this->visit(node->getCompound());
	return NULL;
}

SYM_TABLE_BUILDER_VISITOR(BinOpNode) 
{
	auto node = std::dynamic_pointer_cast<BinOpNode>(nodePtr);
	this->visit(node->left());
	this->visit(node->right());
	return NULL;
}

SYM_TABLE_BUILDER_VISITOR(NumNode) 
{
	return NULL;
}


SYM_TABLE_BUILDER_VISITOR(UnaryOpNode)
{
	auto node = std::dynamic_pointer_cast<UnaryOpNode>(nodePtr);
	return this->visit(node->getRightNodePtr());
}

SYM_TABLE_BUILDER_VISITOR(CompoundNode)
{
	auto node = std::dynamic_pointer_cast<CompoundNode>(nodePtr);
	for (auto child : node->getChildren()) 
	{
		this->visit(child);
	}
	return NULL;
}

SYM_TABLE_BUILDER_VISITOR(NoOpNode)
{
	return NULL;
}

SYM_TABLE_BUILDER_VISITOR(VarDeclNode) 
{
	auto node = std::dynamic_pointer_cast<VarDeclNode>(nodePtr);
	auto typeName = std::get<std::string>(node->getType()->getTokenPtr()->getValue());
	auto typeSymbol = symTable.lookup(typeName);
	std::string varName = std::get<std::string>(node->getVar()->getTokenPtr()->getValue());
	symTable.define(std::make_shared<VarSymbol>(varName,typeSymbol));
	return NULL;
}

SYM_TABLE_BUILDER_VISITOR(VarNode)
{
	auto node = std::dynamic_pointer_cast<VarNode>(nodePtr);
	symTable.lookup(std::get<std::string>(node->getTokenPtr()->getValue()));
	return NULL;
}

SYM_TABLE_BUILDER_VISITOR(AssignNode)
{
	auto node = std::dynamic_pointer_cast<AssignNode>(nodePtr);
	auto varNode = std::dynamic_pointer_cast<VarNode>(node->getLeftPtr());
	std::string varName = std::get<std::string>(varNode->getTokenPtr()->getValue());
	symTable.lookup(varName);
	this->visit(node->getRightPtr());
	return NULL;
}
