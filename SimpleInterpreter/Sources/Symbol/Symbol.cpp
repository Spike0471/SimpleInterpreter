#include "Symbol\Symbol.h"
#include <format>
std::string Symbol::getName()
{
	return symbolName;
}

std::string Symbol::toString() const
{
	return std::format("<Symbol(name={},type={})>", symbolName, symbolType->getName());
}