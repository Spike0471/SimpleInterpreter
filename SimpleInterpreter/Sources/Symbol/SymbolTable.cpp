#include "Symbol/SymbolTable.h"
#include "Symbol/BuiltinTypeSymbol.h"

SymbolTable::SymbolTable()
{
	define(std::make_shared<BuiltinTypeSymbol>("INTEGER"));
	define(std::make_shared<BuiltinTypeSymbol>("REAL"));
}

void SymbolTable::define(SymbolPtr symbolPtr)
{
	symbols[symbolPtr->getName()] = symbolPtr;
}

SymbolPtr SymbolTable::lookup(std::string symbolName)
{
	if (symbols.find(symbolName) == symbols.end()) 
	{
		throw "symbol error";
	}
	return symbols[symbolName];
}
