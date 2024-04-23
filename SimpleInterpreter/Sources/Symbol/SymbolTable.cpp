#include "Symbol/SymbolTable.h"
#include "Symbol/BuiltinTypeSymbol.h"
#include <iostream>

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
		return NULL;
	}
	return symbols[symbolName];
}

std::map<std::string, SymbolPtr> SymbolTable::getAll() const
{
	return symbols;
}

void SymbolTable::printAll()
{
	for (const auto pair : this->symbols)
	{
		std::cout << pair.first << " : " << pair.second->getType()->getName() << std::endl;
	}
}
