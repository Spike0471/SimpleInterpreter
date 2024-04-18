#include "ASTNodes/ProcedureDeclNode.h"

ProcedureDeclNode::ProcedureDeclNode(std::string pName, BlockNodePtr blkNodeP)
{
	procName = pName;
	blockNodePtr = blkNodeP;
}

std::string ProcedureDeclNode::getProcName()
{
	return procName;
}

BlockNodePtr ProcedureDeclNode::getBlockNodePtr()
{
	return blockNodePtr;
}
