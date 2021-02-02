#include <gtest/gtest.h>

#include "../src/Aluno.hpp"

TEST(AlunoUnitTest, AprovadoReprovado) {
  tm data;
  data.tm_mday = 24;
  data.tm_mon = 5 - 1;
  data.tm_year = 2000;
  Aluno paulo{"Paulo", "09189689925", data, "9o ano"};
  paulo.addMateria("geografia");

  paulo.materias[0].setFaltasB1(20);
  paulo.materias[0].setFaltasB2(10);
  paulo.materias[0].setFaltasB3(10);
  paulo.materias[0].setFaltasB4(10);

  paulo.materias[0].setNotaB1(70);
  paulo.materias[0].setNotaB2(60);
  paulo.materias[0].setNotaB3(65);
  paulo.materias[0].setNotaB4(60);
  paulo.materias[0].setNotaExame(85);
  EXPECT_TRUE(paulo.aprovado());
}