#include "NodeVisitor/Interpreter.h"
#include "NodeVisitor/InterpreterException.h"
#include "ASTNodes/UnaryOpNode.h"
#include <iostream>

using namespace std;

#define INTERPRETER_VISITOR(NODE_NAME) DEFINE_VISITOR(Interpreter,NODE_NAME)

void Interpreter::raiseError(string content)
{
	throw InterpreterException(content);
}

INTERPRETER_VISITOR(NumNode)
{
	auto numNodePtr = dynamic_pointer_cast<NumNode>(nodePtr);
	return numNodePtr->getTokenPtr()->getValue();
}

template<typename LT, typename RT>
TokenValue calculateBinOp(LT left, TokenType opType, RT right)
{
	switch (opType)
	{
	case TokenType::TT_PLUS:
		return left + right;
	case TokenType::TT_MINUS:
		return left - right;
	case TokenType::TT_FLOAT_DIV:
		return (float)left / (float)right;
	case TokenType::TT_INTEGER_DIV:
		return (int)(left / right);
	case TokenType::TT_MULTI:
		return left * right;
	default:
		throw InterpreterException("Syntax error.");
		break;
	}

	return NULL;
}

INTERPRETER_VISITOR(BinOpNode)
{
	auto binOpNodePtr = dynamic_pointer_cast<BinOpNode>(nodePtr);
	ASTNodePtr leftNodePtr = binOpNodePtr->left();
	ASTNodePtr rightNodePtr = binOpNodePtr->right();
	TokenValue leftValue = this->visit(leftNodePtr);
	TokenValue rightValue = this->visit(rightNodePtr);

	if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
	{
		return calculateBinOp<int, int>(get<int>(leftValue), binOpNodePtr->getOpTokenPtr()->getType(), get<int>(rightValue));
	}
	else if (std::holds_alternative<int>(leftValue) && std::holds_alternative<float>(rightValue))
	{
		return calculateBinOp<int, float>(get<int>(leftValue), binOpNodePtr->getOpTokenPtr()->getType(), get<float>(rightValue));
	}
	else if (std::holds_alternative<float>(leftValue) && std::holds_alternative<int>(rightValue))
	{
		return calculateBinOp<float, int>(get<float>(leftValue), binOpNodePtr->getOpTokenPtr()->getType(), get<int>(rightValue));
	}
	else if (std::holds_alternative<float>(leftValue) && std::holds_alternative<float>(rightValue))
	{
		return calculateBinOp<float, float>(get<float>(leftValue), binOpNodePtr->getOpTokenPtr()->getType(), get<float>(rightValue));
	}

	raiseError("Syntax error.");
	return NULL;
}

INTERPRETER_VISITOR(UnaryOpNode)
{
	auto unaryOpNode = dynamic_pointer_cast<UnaryOpNode>(nodePtr);
	if (unaryOpNode->getOpTokenPtr()->getType() == TokenType::TT_PLUS)
	{
		return +get<int>(this->visit(unaryOpNode->getRightNodePtr()));
	}

	if (unaryOpNode->getOpTokenPtr()->getType() == TokenType::TT_MINUS)
	{
		return -get<int>(this->visit(unaryOpNode->getRightNodePtr()));
	}

	raiseError("Syntax error");
	return NULL;
}

INTERPRETER_VISITOR(CompoundNode)
{
	auto children = dynamic_pointer_cast<CompoundNode>(nodePtr)->getChildren();
	for (ASTNodePtr child : children)
	{
		this->visit(child);
	}
	return NULL;
}

INTERPRETER_VISITOR(NoOpNode)
{
	return NULL;
}

INTERPRETER_VISITOR(AssignNode)
{
	auto node = dynamic_pointer_cast<AssignNode>(nodePtr);
	auto varNode = dynamic_pointer_cast<VarNode>(node->getLeftPtr());
	auto rightValue = this->visit(node->getRightPtr());
	auto varName = get<std::string>(varNode->getTokenPtr()->getValue());
	auto sym = symtableBuilder.getSymbolTable().lookup(varName);
	if (sym->getType()->getName() == "INTEGER" && !std::holds_alternative<int>(rightValue)) 
	{
		raiseError("Symbol type error.");
	}
	if (sym->getType()->getName() == "REAL" && !std::holds_alternative<float>(rightValue))
	{
		raiseError("Symbol type error.");
	}
	globalVariables[varName] = rightValue;
	return NULL;
}

INTERPRETER_VISITOR(VarNode)
{
	auto varNode = dynamic_pointer_cast<VarNode>(nodePtr);
	auto varName = get<string>(varNode->getTokenPtr()->getValue());
	if (globalVariables.find(varName) == globalVariables.end())
	{
		raiseError("Name error");
	}
	return globalVariables[varName];
}

INTERPRETER_VISITOR(ProgramNode)
{
	auto node = dynamic_pointer_cast<ProgramNode>(nodePtr);
	return this->visit(node->getBlockNodePtr());
}

INTERPRETER_VISITOR(BlockNode)
{
	auto node = dynamic_pointer_cast<BlockNode>(nodePtr);
	for (auto decl : node->getDeclarations())
	{
		this->visit(decl);
	}
	this->visit(node->getCompound());
	return NULL;
}

INTERPRETER_VISITOR(VarDeclNode)
{
	return NULL;
}

INTERPRETER_VISITOR(TypeNode)
{
	return NULL;
}

Interpreter::Interpreter(std::string text)
{
	ADD_TO_VISIT_MAP(NumNode);
	ADD_TO_VISIT_MAP(BinOpNode);
	ADD_TO_VISIT_MAP(UnaryOpNode);
	ADD_TO_VISIT_MAP(CompoundNode);
	ADD_TO_VISIT_MAP(NoOpNode);
	ADD_TO_VISIT_MAP(AssignNode);
	ADD_TO_VISIT_MAP(VarNode);

	ADD_TO_VISIT_MAP(ProgramNode);
	ADD_TO_VISIT_MAP(BlockNode);
	ADD_TO_VISIT_MAP(VarDeclNode);
	ADD_TO_VISIT_MAP(TypeNode);
	astParserPtr = make_shared<ASTParser>(text);
}

TokenValue Interpreter::interpret()
{
	ASTNodePtr rootNode = astParserPtr->parse();
	symtableBuilder.visit(rootNode);
	return this->visit(rootNode);
}

void Interpreter::printAllSymbols()
{
	for (const auto pair : symtableBuilder.getSymbolTable().getAll())
	{
		cout << pair.first << " : " << pair.second->getType()->getName() << endl;
	}
	cout << endl;
	for (const auto pair : globalVariables)
	{
		auto varName = pair.first;
		auto varType = symtableBuilder.getSymbolTable().lookup(varName);
		string varValue = "";
		if (varType->getType()->getName() == "INTEGER")
		{
			varValue = std::to_string(get<int>(pair.second));
		}
		if (varType->getType()->getName() == "REAL")
		{
			varValue = std::to_string(get<float>(pair.second));
		}
		cout << pair.first << " = " << varValue << endl;
	}
}
