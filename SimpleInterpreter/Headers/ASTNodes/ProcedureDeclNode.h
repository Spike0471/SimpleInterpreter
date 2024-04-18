#pragma once
#include "ASTNodes/AbstractSyntaxTreeNodeBase.h"
#include "ASTNodes/BlockNode.h"

class ProcedureDeclNode : public AbstractSyntaxTreeNodeBase
{
private:
	std::string procName;
	BlockNodePtr blockNodePtr;
public:
	ProcedureDeclNode(std::string pName,BlockNodePtr blkNodeP);
	std::string getProcName();
	BlockNodePtr getBlockNodePtr();
	GET_CLASS_NAME(ProcedureDeclNode)
};

typedef std::shared_ptr<ProcedureDeclNode> ProcedureDeclNodePtr;
