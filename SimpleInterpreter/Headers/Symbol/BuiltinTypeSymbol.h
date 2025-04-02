#pragma once
#include "Symbol/Symbol.h"
#include "Basics/OutputStreamTarget.h"
class BuiltinTypeSymbol : public Symbol
{
public:
	BuiltinTypeSymbol(std::string sName);
	SymbolRawPtr getType();
	std::string toString() const;
};