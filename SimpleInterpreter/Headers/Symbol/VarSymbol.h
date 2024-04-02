#pragma once
#include "Symbol/Symbol.h"

class VarSymbol : public Symbol
{
public:
	VarSymbol(std::string varName, SymbolPtr varType);
	SymbolRawPtr getType();
};

