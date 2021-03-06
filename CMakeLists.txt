cmake_minimum_required(VERSION 3.13)
project(mile_stone1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(.)
include_directories(cmake-build-debug)

add_executable(mile_stone1
        main.cpp
        BinaryExpression.h
        Command.h
        CommandExpression.h
        ConditionParserCommand.cpp
        ConditionParserCommand.h
        Expression.h

        Lexer.h
        Lexer.cpp
        MathExpressions.h
        Num.h
        ShuntingYard.h
        ShuntingYard.cpp
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
        Exit.h Parser.cpp
        ServerCommand.cpp
        Var.h
        Equalize.cpp
        Equalize.h
        BindVar.h
        VarCreatorCommand.cpp
        VarCreatorCommand.h
        PrintCommand.h
        SleepCommand.cpp
        PrintCommand.cpp
        Var.cpp
        Observer.h
        Notifier.h
        Notifier.cpp ExpressionFactory.cpp ExpressionFactory.h RunProgram.h IfCommand.cpp WhileCommand.cpp RunProgram.cpp ClientCommand.cpp UpdateableExpression.h UntieVar.h)


#ClientServerCommands.h
#ClientServerCommands.cpp
#MathExpressions.h
#MathExpressions.cpp
#PrintSlpCmnds.h
#PrintSlpCmnds.cpp
#Utils.h
#Utils.cpp
#AddExp.h
