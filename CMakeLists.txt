cmake_minimum_required(VERSION 3.10.0)
project(SimpleInterpreter VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(SimpleInterpreter/Headers)
file(GLOB AST_NODES_CPP "SimpleInterpreter/Sources/ASTNodes/*.cpp")
file(GLOB NODE_VISITOR_CPP "SimpleInterpreter/Sources/NodeVisitor/*.cpp")
file(GLOB PARSER_CPP "SimpleInterpreter/Sources/Parser/*.cpp")
file(GLOB SYMBOL_CPP "SimpleInterpreter/Sources/Symbol/*.cpp")
file(GLOB TOKENIZER_CPP "SimpleInterpreter/Sources/Tokenizer/*.cpp")
add_executable(
    SimpleInterpreter 
    SimpleInterpreter/test.cpp
    ${AST_NODES_CPP}
    ${NODE_VISITOR_CPP}
    ${PARSER_CPP}
    ${SYMBOL_CPP}
    ${TOKENIZER_CPP}
    )

