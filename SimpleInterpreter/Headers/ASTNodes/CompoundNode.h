#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include <vector>

class CompoundNode : public AbstractSyntaxTreeNodeBase
{
private:
	std::vector<ASTNodePtr> childrenNodes;
public:
	CompoundNode(std::vector<ASTNodePtr> children);
	const std::vector<ASTNodePtr>& getChildren();

	GET_CLASS_NAME(CompoundNode)
};

typedef std::shared_ptr<CompoundNode> CompoundNodePtr;