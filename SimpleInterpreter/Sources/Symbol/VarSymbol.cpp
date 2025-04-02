#include "Symbol/VarSymbol.h"
#include <format>
VarSymbol::VarSymbol(std::string varName, SymbolPtr varType)
{
	symbolName = varName;
	symbolType = varType;
}

SymbolRawPtr VarSymbol::getType()
{
	return symbolType->getType();
}

std::string VarSymbol::toString() const
{
	return std::format("<VarSymbol(name=\"{}\",type=\"{}\")>", symbolName, symbolType->toString());
}
