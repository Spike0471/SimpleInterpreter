#include <string>
#include "Parser/ASTParser.h"
#include "NodeVisitor/SimpleVisitor.h"
#include "NodeVisitor/Interpreter.h"
#include <iostream>
#include "Symbol/Symbol.h"
#include "Symbol/ScopedSymbolTable.h"
#include "Symbol/BuiltinTypeSymbol.h"
#include "Symbol/VarSymbol.h"
#include "NodeVisitor/SymbolTableBuilder.h"
#include "NodeVisitor/SemanticAnalyzer.h"

int main()
{
	std::string text = R"(
PROGRAM Part9;
VAR
   number : INTEGER;
   a, b   : INTEGER;
   y      : REAL;
   c      : INTEGER;

BEGIN {Part9}
   number := 2;
   a := number ;
   b := 10 * a + 10 * number DIV 4;
   y := 20 / 7 + 3.14;
   c := 1
END.  {Part9}
)";
	ASTParser parser(text);
	SemanticAnalyzer analyzer;
	try
	{
		analyzer.visit(parser.parse());
		std::cout << analyzer.getSymbolTable() << std::endl;
	}
	catch (SemanticError e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cin.get();

	return 0;
}