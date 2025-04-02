#pragma once
#include <map>
#include <string>
#include "Symbol/Symbol.h"
#include "Basics/OutputStreamTarget.h"

class ScopedSymbolTable : public OutputStreamTarget
{
private:
	std::map<std::string, SymbolPtr> symbols;

public:
	std::string scopeName;
	int scopeLevel;

public:
	ScopedSymbolTable();
	void define(SymbolPtr symbolPtr);
	SymbolPtr lookup(std::string symbolName);
	std::map<std::string, SymbolPtr> getAll() const;
	std::string toString() const;
};
