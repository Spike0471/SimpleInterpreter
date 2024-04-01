#include "ASTNodes/CompoundNode.h"

CompoundNode::CompoundNode(std::vector<ASTNodePtr> children)
{
	childrenNodes.swap(children);
}

const std::vector<ASTNodePtr>& CompoundNode::getChildren()
{
	return childrenNodes;
}
