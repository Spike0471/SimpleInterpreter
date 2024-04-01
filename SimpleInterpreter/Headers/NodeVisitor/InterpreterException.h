#pragma once
#include <exception>
#include <string>

class InterpreterException :public std::exception
{
private:
	std::string errorContent;
public:
	InterpreterException();
	InterpreterException(std::string);
};

