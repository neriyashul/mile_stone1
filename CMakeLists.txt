cmake_minimum_required(VERSION 3.13)
project(mile_stone1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(.)
include_directories(cmake-build-debug)

add_executable(mile_stone1
        main.cpp
        Command.h
        CommandExpression.h
        ConditionParserCommand.cpp
        ConditionParserCommand.h
        Expression.h
        AddExp.h
        BinaryExpression.h
        DivExp.h
        MinusExp.h
        MulExp.h
        Num.h
        ShuntingYard.h
        ShuntingYard.cpp
        UnaryExpression.h
        OpenServerCommand.h
        TheParser.h
        WhileCommand.h OpenClientCommand.h OpenTcpClientCommand.cpp OpenTcpClientCommand.h OpenTcpServer.cpp OpenTcpServer.h SleepCommand.h ReadData.cpp ReadData.h Interpreter.cpp Interpreter.h LexerParser.cpp Enterc.h IfCommand.h Exit.h)
