cmake_minimum_required(VERSION 3.13)
project(mile_stone1)

set(CMAKE_CXX_STANDARD 14)

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
        ner.h
        WhileCommand.h OpenClientCommand.h OpenTcpClient.cpp OpenTcpClient.h OpenTcpServer.cpp OpenTcpServer.h OpenServerCommand.h)
