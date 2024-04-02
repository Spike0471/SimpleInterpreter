#pragma once
#include <string>
#include <memory>

class Symbol;
typedef std::shared_ptr<Symbol> SymbolPtr;
typedef Symbol* const SymbolRawPtr;

class Symbol
{
protected:
	std::string symbolName;
	SymbolPtr symbolType;
public:
	virtual SymbolRawPtr getType() = 0;
	std::string getName();
};