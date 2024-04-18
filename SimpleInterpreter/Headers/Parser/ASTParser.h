#pragma once
#include <string>
#include <vector>
#include "ASTNodes/BinOpNode.h"
#include "ASTNodes/NumNode.h"
#include "Tokenizer/Lexer.h"
#include "ASTNodes/VarDeclNode.h"
#include "ASTNodes/BlockNode.h"
#include "ASTNodes/ProgramNode.h"

class ASTParser
{
private:
	LexerPtr lexerPtr;
	TokenPtr currentTokenPtr;
private:
	void raiseError();
	void eat(TokenType type);

	BlockNodePtr block();
	std::vector<ASTNodePtr> declarations();
	std::vector<VarDeclNodePtr> variableDeclaration();
	TypeNodePtr typeSpec();

	ProgramNodePtr program();
	CompoundNodePtr compoundStatement();
	std::vector<ASTNodePtr> statementList();
	ASTNodePtr statement();
	ASTNodePtr assignStatement();
	VarNodePtr variable();
	ASTNodePtr empty();

	ASTNodePtr expr();
	ASTNodePtr term();
	ASTNodePtr factory();
public:
	ASTParser(std::string txt);
	ASTNodePtr parse();
};

typedef std::shared_ptr<ASTParser> ASTParserPtr;

