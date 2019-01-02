cmake_minimum_required(VERSION 3.13)
project(mile_stone1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(.)
include_directories(cmake-build-debug)

add_executable(mile_stone1
        main.cpp
        BinaryExpression.h

        CommandFactory.h
        CommandFactory.cpp
        Command.h
        CommandExpression.h
        ConditionParserCommand.cpp
        ConditionParserCommand.h
        Expression.h
        ExpsCollection.h
        ExpsCollection.cpp
        Interpreter.cpp
        Interpreter.h

        Lexer.h
        Lexer.cpp
        MathExpressions.h
        MathExpressions.cpp
        Num.h
        ShuntingYard.h
        ShuntingYard.cpp
        Threads.h
        Threads.cpp
        UnaryExpression.h
        ServerCommand.h
        Parser.h
        WhileCommand.h
        ClientCommand.h
        TcpClient.cpp
        TcpClient.h
        TcpServer.cpp
        TcpServer.h
        SleepCommand.h
        ReadData.cpp
        ReadData.h
        Enterc.h
        IfCommand.h
        Exit.h Parser.cpp ServerCommand.cpp Var.h Equalize.cpp Equalize.h bindVar.h VarDataCommand.cpp VarDataCommand.h Print.h)


#ClientServerCommands.h
#ClientServerCommands.cpp
#MathExpressions.h
#MathExpressions.cpp
#PrintSlpCmnds.h
#PrintSlpCmnds.cpp
#Utils.h
#Utils.cpp
#AddExp.h
