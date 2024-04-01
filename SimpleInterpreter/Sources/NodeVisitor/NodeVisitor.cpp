#include "NodeVisitor/NodeVisitor.h"

TokenValue NodeVisitor::visit(ASTNodePtr nodePtr)
{
	if (visitMap.find(nodePtr->getClassName()) == visitMap.end())
	{
		throw "";
	}

	return visitMap[nodePtr->getClassName()](nodePtr);
}
