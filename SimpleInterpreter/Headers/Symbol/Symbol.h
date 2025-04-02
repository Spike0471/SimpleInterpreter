#pragma once
#include "Basics/OutputStreamTarget.h"
#include <string>
#include <memory>

class Symbol;
typedef std::shared_ptr<Symbol> SymbolPtr;
typedef Symbol *const SymbolRawPtr;

class Symbol : public OutputStreamTarget
{
protected:
	std::string symbolName;
	SymbolPtr symbolType;

public:
	virtual SymbolRawPtr getType() = 0;
	virtual std::string toString() const;
	std::string getName();
};