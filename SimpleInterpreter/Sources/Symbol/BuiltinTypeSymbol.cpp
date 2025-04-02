#include "Symbol/BuiltinTypeSymbol.h"
#include <format>
BuiltinTypeSymbol::BuiltinTypeSymbol(std::string sName)
{
	symbolName = sName;
}

SymbolRawPtr BuiltinTypeSymbol::getType()
{
	return this;
}

std::string BuiltinTypeSymbol::toString() const
{
	return std::format("<BuiltinTypesSymbol(name=\"{}\")>", symbolName);
}
