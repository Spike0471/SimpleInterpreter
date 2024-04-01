#include "Symbol/VarSymbol.h"

VarSymbol::VarSymbol(std::string varName, SymbolPtr varType)
{
	symbolName = varName;
	symbolType = varType;
}

std::string VarSymbol::getType()
{
	return "<" + symbolName + ":" + symbolType->getType() + ">";
}
