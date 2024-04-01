#pragma once
#include <string>
#include <memory>

class Symbol;
typedef std::shared_ptr<Symbol> SymbolPtr;

class Symbol
{
protected:
	std::string symbolName;
	SymbolPtr symbolType;
public:
	virtual std::string getType() = 0;
	std::string getName();
};