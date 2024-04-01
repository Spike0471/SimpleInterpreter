#pragma once
#include "AbstractSyntaxTreeNodeBase.h"
#include "ASTNodes/BlockNode.h"

class ProgramNode :public AbstractSyntaxTreeNodeBase
{
private:
	std::string programName;
	BlockNodePtr blockNode;
public:
	ProgramNode(std::string pName, BlockNodePtr node);
	std::string getProgramName();
	BlockNodePtr getBlockNodePtr();

	GET_CLASS_NAME(ProgramNode)
};

typedef std::shared_ptr<ProgramNode> ProgramNodePtr;
