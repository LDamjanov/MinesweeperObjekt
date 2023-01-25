cmake_minimum_required(VERSION 3.5)

project(Praktikum4Aufgabe13 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Praktikum4Aufgabe13 main.cpp funktion.cpp kopf.h)

install(TARGETS Praktikum4Aufgabe13
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
