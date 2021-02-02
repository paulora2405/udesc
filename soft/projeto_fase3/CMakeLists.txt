cmake_minimum_required(VERSION 3.8)

set(This Soft_fase3)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
  src/Professor.hpp
  src/Aluno.hpp
  src/Materia.hpp
)

set(Sources
  src/Professor.cpp
  src/Aluno.cpp
  src/Materia.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)