#include <gtest/gtest.h>

#include "../src/Materia.hpp"

TEST(MateriaUnitTest, Medias) {
  Materia m{"Geografia"};
  m.setNotaB1(70);
  m.setNotaB2(60);
  m.setNotaB3(65);
  m.setNotaB4(60);
  m.setNotaExame(80);
  int mediaFinal = m.calculaMediaFinal();
  int expMediaFinal = nearbyint(70 + 60 + 65 + 60) / 4;
  EXPECT_EQ(expMediaFinal, mediaFinal);
  int mediaPosExame = m.calculaMediaPosExame();
  int expMediaPosExame = nearbyint((expMediaFinal * 6 + 80 * 4) / 10);
  EXPECT_EQ(expMediaPosExame, mediaPosExame);
}

TEST(MateriaUnitTest, Frequencias) {
  Materia m{"Geografia"};
  m.setFaltasB1(2);
  m.setFaltasB2(3);
  m.setFaltasB3(4);
  m.setFaltasB4(1);

  int expPorcentagem = 95;
  int porcentagem = m.getPorcentagemFrequencia();

  EXPECT_EQ(expPorcentagem, porcentagem);
}