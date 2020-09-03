CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(C++PRACTICE)
ADD_DEFINITIONS(-std=c++11)

ADD_EXECUTABLE(BasicTest basic_knowledge/heapandstack.cpp)
ADD_EXECUTABLE(SmartPtr basic_knowledge/smartPtr.cpp)
ADD_EXECUTABLE(RightValue basic_knowledge/rightValuePractice.cpp)
ADD_EXECUTABLE(ContainerTest basic_knowledge/Container.cpp)
ADD_EXECUTABLE(ExceptionTest basic_knowledge/ForException.cpp)
ADD_EXECUTABLE(IteratorTest basic_knowledge/IteratorAndForloop.cpp)
ADD_EXECUTABLE(GoodFeatrueTest basic_knowledge/GoodFeature.cpp)