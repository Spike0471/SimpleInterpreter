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
PROGRAM Part11;
VAR
   number : INTEGER;
   a, b   : INTEGER;
   y      : REAL;

BEGIN {Part11}
   number := 2;
   a := number ;
   b := 10 * a + 10 * number DIV 4;
   y := 20 / 7 + 3.14
END.  {Part11}
)";
	Interpreter inter(text);
	inter.interpret();
	inter.printAllSymbols();
	std::cin.get();

	return 0;
}