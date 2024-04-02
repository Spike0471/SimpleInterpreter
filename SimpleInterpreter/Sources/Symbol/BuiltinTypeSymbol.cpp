#include "Symbol/BuiltinTypeSymbol.h"

BuiltinTypeSymbol::BuiltinTypeSymbol(std::string sName)
{
	symbolName = sName;
}

SymbolRawPtr BuiltinTypeSymbol::getType()
{
	return this;
}
