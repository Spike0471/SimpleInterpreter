#include "ASTNodes/ProgramNode.h"

ProgramNode::ProgramNode(std::string pName, BlockNodePtr node)
{
	programName = pName;
	blockNode = node;
}

std::string ProgramNode::getProgramName()
{
	return programName;
}

BlockNodePtr ProgramNode::getBlockNodePtr()
{
	return blockNode;
}
