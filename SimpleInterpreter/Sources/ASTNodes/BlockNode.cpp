#include "..\..\Headers\ASTNodes\BlockNode.h"

BlockNode::BlockNode(std::vector<VarDeclNodePtr> decls, CompoundNodePtr cNode)
{
	declarations.swap(decls);
	compoundNodePtr = cNode;
}

std::vector<VarDeclNodePtr> BlockNode::getDeclarations()
{
	return declarations;
}

CompoundNodePtr BlockNode::getCompound()
{
	return compoundNodePtr;
}
