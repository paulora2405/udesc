#ifndef _MATERIA_HPP_
#define _MATERIA_HPP_

#include <algorithm>
#include <cmath>
#include <string>

class Materia {
private:
  std::string nomeMateria;
  int notaB1;
  int notaB2;
  int notaB3;
  int notaB4;
  int faltasB1;
  int faltasB2;
  int faltasB3;
  int faltasB4;

  int mediaFinal;
  int notaExame;
  int mediaPosExame;

public:
  Materia(std::string);
  ~Materia();

  int calculaMediaFinal();
  int calculaMediaPosExame();

  int getPorcentagemFrequencia();
  int getTotalPontos() const;
  int getTotalFaltas() const;
  std::string getNomeMateria() const;
  int getNotaB1() const;
  int getNotaB2() const;
  int getNotaB3() const;
  int getNotaB4() const;
  int getFaltasB1() const;
  int getFaltasB2() const;
  int getFaltasB3() const;
  int getFaltasB4() const;
  int getNotaExame() const;

  void setNotaB1(int);
  void setNotaB2(int);
  void setNotaB3(int);
  void setNotaB4(int);
  void setFaltasB1(int);
  void setFaltasB2(int);
  void setFaltasB3(int);
  void setFaltasB4(int);
  void setNotaExame(int);
};

#endif