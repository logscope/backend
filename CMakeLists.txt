cmake_minimum_required(VERSION 3.17)
project(logscope)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        logscope
        contract.h contract.cpp
        main.cpp
        testall.cpp
        src/util/util.cpp src/util/util.h
        src/ast/ast.cpp src/ast/ast.h
        src/engine/Event.cpp src/engine/Event.h
        src/engine/SpecObject.cpp src/engine/SpecObject.h
        src/engine/MonitorObject.cpp src/engine/MonitorObject.h
        src/engine/StateObject.cpp src/engine/StateObject.h
        src/engine/Binding.cpp src/engine/Binding.h
        src/engine/MonitorError.cpp src/engine/MonitorError.h
        src/engine/EndError.cpp src/engine/EndError.h
        src/engine/NextError.cpp src/engine/NextError.h
        src/engine/TransitionError.cpp src/engine/TransitionError.h
        src/engine/Option.h src/engine/Options.h
        src/engine/ErrorReport.h src/engine/ErrorReport.cpp
        src/csv/csvparser.h src/csv/csvparser.c
        test/suite1/contract.cpp test/suite1/contract.h test/suite1/test1.h
        test/suite2/contract.cpp test/suite2/contract.h test/suite2/test2.h
        test/suite3/contract.cpp test/suite3/contract.h test/suite3/test3.h
        test/suite4/contract.cpp test/suite4/contract.h test/suite4/test4.h
        test/suite5/contract.cpp test/suite5/contract.h test/suite5/test5.h
        test/suite6/contract.cpp test/suite6/contract.h test/suite6/test6.h
        test/suite7/contract.cpp test/suite7/contract.h test/suite7/test7.h
        test/suite8/contract.cpp test/suite8/contract.h test/suite8/test8.h
        examples/example1/example1.h
        examples/example2/example2.h
        examples/example3/example3.h
        examples/example4/example4.h
        examples/example5/example5.h
        examples/example6/example6.h
        examples/example7/example7.h
)
