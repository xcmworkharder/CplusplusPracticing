CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(C++PRACTICE)
ADD_DEFINITIONS(-std=c++11)

ADD_EXECUTABLE(BasicTest basic_knowledge/heapandstack.cpp)
ADD_EXECUTABLE(SmartPtr basic_knowledge/smartPtr.cpp)