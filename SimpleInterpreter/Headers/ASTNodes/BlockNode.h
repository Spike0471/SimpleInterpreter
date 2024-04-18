#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include "CompoundNode.h"
#include "VarDeclNode.h"

class BlockNode :public AbstractSyntaxTreeNodeBase
{
private:
	std::vector<ASTNodePtr> declarations;
	CompoundNodePtr compoundNodePtr;
public:
	BlockNode(std::vector<ASTNodePtr> decls, CompoundNodePtr cNode);
	std::vector<ASTNodePtr> getDeclarations();
	CompoundNodePtr getCompound();

	GET_CLASS_NAME(BlockNode)
};

typedef std::shared_ptr<BlockNode> BlockNodePtr;