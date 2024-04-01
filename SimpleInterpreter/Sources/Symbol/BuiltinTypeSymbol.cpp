#include "Symbol/BuiltinTypeSymbol.h"

BuiltinTypeSymbol::BuiltinTypeSymbol(std::string sName)
{
	symbolName = sName;
}

std::string BuiltinTypeSymbol::getType()
{
	return symbolName;
}
