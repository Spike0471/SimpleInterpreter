#include <string>
#include "Parser/ASTParser.h"
#include "NodeVisitor/SimpleVisitor.h"
#include "NodeVisitor/Interpreter.h"
#include <iostream>
#include "Symbol/Symbol.h"
#include "Symbol/SymbolTable.h"
#include "Symbol/BuiltinTypeSymbol.h"
#include "Symbol/VarSymbol.h"
#include "NodeVisitor/SymbolTableBuilder.h"

int main()
{
	std::string text = R"(
PROGRAM test;
VAR
	x,y : INTEGER;
	a,b : REAL;
BEGIN
	x := 1;
	a := 2.2;
END.
)";
	Interpreter inter(text);
	inter.interpret();
	inter.printAllSymbols();
	std::cin.get();

	return 0;
}