#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include "CompoundNode.h"
#include "VarDeclNode.h"

class BlockNode :public AbstractSyntaxTreeNodeBase
{
private:
	std::vector<VarDeclNodePtr> declarations;
	CompoundNodePtr compoundNodePtr;
public:
	BlockNode(std::vector<VarDeclNodePtr> decls, CompoundNodePtr cNode);
	std::vector<VarDeclNodePtr> getDeclarations();
	CompoundNodePtr getCompound();

	GET_CLASS_NAME(BlockNode)
};

typedef std::shared_ptr<BlockNode> BlockNodePtr;