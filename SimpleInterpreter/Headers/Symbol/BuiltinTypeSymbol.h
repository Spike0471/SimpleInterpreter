#pragma once
#include "Symbol/Symbol.h"

class BuiltinTypeSymbol : public Symbol
{
public:
	BuiltinTypeSymbol(std::string sName);
	SymbolRawPtr getType();
};