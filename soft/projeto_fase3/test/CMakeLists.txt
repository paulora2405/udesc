include(Dart)
cmake_minimum_required(VERSION 3.8)

set(This Soft_fase3_tests)

set(Sources
  AlunoUnitTest.cpp
  ProfessorUnitTest.cpp
  MateriaUnitTest.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
  gtest_main
  Soft_fase3
)

add_test(
  NAME ${This}
  COMMAND ${This}
)