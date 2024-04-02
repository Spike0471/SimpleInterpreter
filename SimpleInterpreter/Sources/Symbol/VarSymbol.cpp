#include "Symbol/VarSymbol.h"

VarSymbol::VarSymbol(std::string varName, SymbolPtr varType)
{
	symbolName = varName;
	symbolType = varType;
}

SymbolRawPtr VarSymbol::getType()
{
	return symbolType->getType();
}
