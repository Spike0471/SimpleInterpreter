#include "NodeVisitor/SimpleVisitor.h"
#include <iostream>
using namespace std;

#define SIMPLE_VISITOR(NODE_NAME) DEFINE_VISITOR(SimpleVisitor,NODE_NAME)

SIMPLE_VISITOR(ProgramNode)
{
	auto node = dynamic_pointer_cast<ProgramNode>(nodePtr);
	cout << node->getProgramName() << endl;
	this->visit(node->getBlockNodePtr());
	return NULL;
}

SIMPLE_VISITOR(BlockNode)
{
	auto node = dynamic_pointer_cast<BlockNode>(nodePtr);
	for (auto varDeclNode : node->getDeclarations()) 
	{
		this->visit(varDeclNode);
	}
	return NULL;
}

SIMPLE_VISITOR(TypeNode)
{
	auto node = dynamic_pointer_cast<TypeNode>(nodePtr);
	cout << get<string>(node->getTokenPtr()->getValue()) << endl;
	return NULL;
}

SIMPLE_VISITOR(VarNode)
{
	auto node = dynamic_pointer_cast<VarNode>(nodePtr);
	cout << get<string>(node->getTokenPtr()->getValue()) << endl;
	return NULL;
}

SIMPLE_VISITOR(VarDeclNode)
{
	auto node = dynamic_pointer_cast<VarDeclNode>(nodePtr);
	this->visit(node->getType());
	this->visit(node->getVar());
	return NULL;
}

SIMPLE_VISITOR(CompoundNode)
{
	auto node = dynamic_pointer_cast<CompoundNode>(nodePtr);
	for (auto child : node->getChildren()) 
	{
		this->visit(child);
	}
	return NULL;
}

SimpleVisitor::SimpleVisitor(ASTParserPtr p)
{
	ADD_TO_VISIT_MAP(ProgramNode);
	ADD_TO_VISIT_MAP(VarDeclNode);
	ADD_TO_VISIT_MAP(VarNode);
	ADD_TO_VISIT_MAP(TypeNode);
	ADD_TO_VISIT_MAP(BlockNode);
	ADD_TO_VISIT_MAP(ProgramNode);
	ADD_TO_VISIT_MAP(CompoundNode);
	parserPtr = p;
}

void SimpleVisitor::printAll()
{
	this->visit(parserPtr->parse());
}
