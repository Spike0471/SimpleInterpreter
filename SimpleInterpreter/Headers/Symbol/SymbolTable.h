#pragma once
#include <map>
#include <string>
#include "Symbol/Symbol.h"

class SymbolTable
{
private:
	std::map<std::string, SymbolPtr> symbols;
public:
	SymbolTable();
	void define(SymbolPtr symbolPtr);
	SymbolPtr lookup(std::string symbolName);
	std::map<std::string, SymbolPtr> getAll() const;
};

