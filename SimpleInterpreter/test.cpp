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
	x := 2.2;
END.
)";
	ASTParser parser(text);
	SymbolTableBuilder stb;
	stb.visit(parser.parse());

	std::cin.get();

	return 0;
}