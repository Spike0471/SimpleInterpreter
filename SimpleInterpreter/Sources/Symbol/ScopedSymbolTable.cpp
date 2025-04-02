#include "Symbol/ScopedSymbolTable.h"
#include "Symbol/BuiltinTypeSymbol.h"
#include <vector>
#include <sstream>
#include <string>

ScopedSymbolTable::ScopedSymbolTable()
{
	define(std::make_shared<BuiltinTypeSymbol>("INTEGER"));
	define(std::make_shared<BuiltinTypeSymbol>("REAL"));
}

void ScopedSymbolTable::define(SymbolPtr symbolPtr)
{
	symbols[symbolPtr->getName()] = symbolPtr;
}

SymbolPtr ScopedSymbolTable::lookup(std::string symbolName)
{
	if (symbols.find(symbolName) == symbols.end())
	{
		return NULL;
	}
	return symbols[symbolName];
}

std::map<std::string, SymbolPtr> ScopedSymbolTable::getAll() const
{
	return symbols;
}

std::string ScopedSymbolTable::toString() const
{
	std::ostringstream oss;
	oss << "\nSCOPE (SCOPED SYMBOL TABLE)\n";
	oss << "============================\n";
	oss << "Scope Name: ";
	oss << scopeName;
	oss << "\n";
	oss << "Scope Level: ";
	oss << scopeLevel;
	oss << "\n";
	oss << "Scope (Scoped symbol table) contents\n";
	oss << "------------------------------------\n";
	for (auto const &pair : symbols)
	{
		oss << pair.first;
		oss << ": ";
		oss << pair.second->toString();
		oss << "\n";
	}
	return oss.str();
}
