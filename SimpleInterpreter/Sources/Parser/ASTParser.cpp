#include "Parser/ASTParser.h"
#include "Parser/ASTException.h"
#include "ASTNodes/UnaryOpNode.h"
#include "ASTNodes/CompoundNode.h"
#include "ASTNodes/VarNode.h"
#include "ASTNodes/AssignNode.h"
#include "ASTNodes/NoOpNode.h"
#include "ASTNodes/BlockNode.h"
#include <memory>
using namespace std;

void ASTParser::raiseError()
{
	throw ASTException();
}

void ASTParser::eat(TokenType type)
{
	if (currentTokenPtr->getType() != type)
	{
		raiseError();
		return;
	}
	currentTokenPtr = lexerPtr->getNextTokenPtr();
}

BlockNodePtr ASTParser::block()
{
	std::vector<VarDeclNodePtr> declarationNodes = declarations();
	CompoundNodePtr compoundStatementNode = compoundStatement();
	return std::make_shared<BlockNode>(declarationNodes, compoundStatementNode);
}

std::vector<VarDeclNodePtr> ASTParser::declarations()
{
	std::vector<VarDeclNodePtr> result;
	if (currentTokenPtr->getType() == TokenType::TT_VAR)
	{
		eat(TokenType::TT_VAR);
		while (currentTokenPtr->getType() == TokenType::TT_ID)
		{
			auto tmp = variableDeclaration();
			result.insert(result.end(), std::make_move_iterator(tmp.begin()), std::make_move_iterator(tmp.end()));
			eat(TokenType::TT_SEMI);
		}
	}
	return result;
}

std::vector<VarDeclNodePtr> ASTParser::variableDeclaration()
{
	std::vector<VarNodePtr> varNodes;
	VarNodePtr node = variable();
	varNodes.push_back(node);
	while (currentTokenPtr->getType() == TokenType::TT_COMMA)
	{
		eat(TokenType::TT_COMMA);
		VarNodePtr tmp = variable();
		varNodes.push_back(tmp);
	}
	eat(TokenType::TT_COLON);
	TypeNodePtr typeNode = typeSpec();

	std::vector<VarDeclNodePtr> result;

	for (auto varNode : varNodes)
	{
		result.push_back(make_shared<VarDeclNode>(varNode, typeNode));
	}

	return result;
}

TypeNodePtr ASTParser::typeSpec()
{
	TokenPtr token = currentTokenPtr;
	if (currentTokenPtr->getType() == TokenType::TT_INTEGER)
	{
		eat(TokenType::TT_INTEGER);
		return make_shared<TypeNode>(token);
	}

	if (currentTokenPtr->getType() == TokenType::TT_REAL)
	{
		eat(TokenType::TT_REAL);
		return make_shared<TypeNode>(token);
	}

	raiseError();
	return  NULL;
}

ProgramNodePtr ASTParser::program()
{
	eat(TokenType::TT_PROGRAM);
	VarNodePtr programVar = variable();
	string programName = get<string>(programVar->getTokenPtr()->getValue());
	eat(TokenType::TT_SEMI);
	BlockNodePtr blockNode = block();
	ProgramNodePtr programNode = make_shared<ProgramNode>(programName, blockNode);
	eat(TokenType::TT_DOT);
	return programNode;
}

CompoundNodePtr ASTParser::compoundStatement()
{
	eat(TokenType::TT_BEGIN);
	CompoundNodePtr root = make_shared<CompoundNode>(statementList());
	eat(TokenType::TT_END);
	return root;
}

std::vector<ASTNodePtr> ASTParser::statementList()
{
	ASTNodePtr node = statement();
	std::vector<ASTNodePtr> result = { node };
	while (currentTokenPtr->getType() == TokenType::TT_SEMI)
	{
		eat(TokenType::TT_SEMI);
		result.push_back(statement());
	}
	if (currentTokenPtr->getType() != TokenType::TT_END)
	{
		raiseError();
	}
	return result;
}

ASTNodePtr ASTParser::statement()
{
	if (currentTokenPtr->getType() == TokenType::TT_BEGIN)
	{
		return compoundStatement();
	}

	if (currentTokenPtr->getType() == TokenType::TT_ID)
	{
		return assignStatement();
	}

	return empty();
}

ASTNodePtr ASTParser::assignStatement()
{
	ASTNodePtr left = variable();
	TokenPtr opToken = currentTokenPtr;
	eat(TokenType::TT_ASSIGN);
	ASTNodePtr right = expr();
	return make_shared<AssignNode>(left, opToken, right);
}

VarNodePtr ASTParser::variable()
{
	VarNodePtr varNode = make_shared<VarNode>(currentTokenPtr);
	eat(TokenType::TT_ID);
	return varNode;
}

ASTNodePtr ASTParser::empty()
{
	return make_shared<NoOpNode>();
}

ASTParser::ASTParser(std::string txt)
{
	lexerPtr = make_shared<Lexer>(txt);
	currentTokenPtr = lexerPtr->getNextTokenPtr();
}

ASTNodePtr ASTParser::parse()
{
	ProgramNodePtr programNode = program();
	if (currentTokenPtr->getType() != TokenType::TT_EOF)
	{
		raiseError();
	}
	return programNode;
}

ASTNodePtr ASTParser::expr()
{
	ASTNodePtr node = term();
	while (currentTokenPtr->getType() == TokenType::TT_PLUS ||
		currentTokenPtr->getType() == TokenType::TT_MINUS)
	{
		TokenPtr tokenPtr = currentTokenPtr;
		eat(tokenPtr->getType());
		node = make_shared<BinOpNode>(node, tokenPtr, term());
	}
	return node;
}

ASTNodePtr ASTParser::term()
{
	ASTNodePtr node = factory();
	while (currentTokenPtr->getType() == TokenType::TT_MULTI ||
		currentTokenPtr->getType() == TokenType::TT_INTEGER_DIV ||
		currentTokenPtr->getType() == TokenType::TT_FLOAT_DIV)
	{
		TokenPtr tokenPtr = currentTokenPtr;
		eat(currentTokenPtr->getType());
		node = make_shared<BinOpNode>(node, tokenPtr, factory());
	}
	return node;
}

ASTNodePtr ASTParser::factory()
{
	TokenPtr tokenPtr = currentTokenPtr;
	if (tokenPtr->getType() == TokenType::TT_PLUS ||
		tokenPtr->getType() == TokenType::TT_MINUS)
	{
		eat(tokenPtr->getType());
		return make_shared<UnaryOpNode>(tokenPtr, factory());
	}

	if (tokenPtr->getType() == TokenType::TT_INTEGER_CONST)
	{
		eat(TokenType::TT_INTEGER_CONST);
		return make_shared<NumNode>(tokenPtr);
	}

	if (tokenPtr->getType() == TokenType::TT_REAL_CONST)
	{
		eat(TokenType::TT_REAL_CONST);
		return make_shared<NumNode>(tokenPtr);
	}

	if (tokenPtr->getType() == TokenType::TT_LPAREN)
	{
		eat(TokenType::TT_LPAREN);
		ASTNodePtr result = expr();
		eat(TokenType::TT_RPAREN);
		return result;
	}

	if (tokenPtr->getType() == TokenType::TT_ID)
	{
		return variable();
	}

	raiseError();
	return NULL;
}