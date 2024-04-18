#include "..\..\Headers\ASTNodes\BlockNode.h"

BlockNode::BlockNode(std::vector<ASTNodePtr> decls, CompoundNodePtr cNode)
{
	declarations.swap(decls);
	compoundNodePtr = cNode;
}

std::vector<ASTNodePtr> BlockNode::getDeclarations()
{
	return declarations;
}

CompoundNodePtr BlockNode::getCompound()
{
	return compoundNodePtr;
}
