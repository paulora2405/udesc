#include "Materia.hpp"

Materia::Materia(std::string nome) : nomeMateria{nome} {}

Materia::~Materia() {}

int Materia::calculaMediaFinal() {
  mediaFinal = nearbyint((notaB1 + notaB2 + notaB3 + notaB4) / 4);
  return mediaFinal;
}

int Materia::calculaMediaPosExame() {
  if(calculaMediaFinal() >= 70) return 0;
  // peso da media final = 6 e peso da nota do exame = 4
  mediaPosExame = nearbyint((calculaMediaFinal() * 6 + notaExame * 4) / 10);
  return mediaPosExame;
}

int Materia::getPorcentagemFrequencia() {
  // 200 dias letivos no total
  return (int)nearbyint(((200 - getTotalFaltas()) * 100) / 200);
}
int Materia::getTotalPontos() const { return notaB1 + notaB2 + notaB3 + notaB4; }
int Materia::getTotalFaltas() const { return faltasB1 + faltasB2 + faltasB3 + faltasB4; }
std::string Materia::getNomeMateria() const { return nomeMateria; }
int Materia::getNotaB1() const { return notaB1; }
int Materia::getNotaB2() const { return notaB2; }
int Materia::getNotaB3() const { return notaB3; }
int Materia::getNotaB4() const { return notaB4; }
int Materia::getFaltasB1() const { return faltasB1; }
int Materia::getFaltasB2() const { return faltasB2; }
int Materia::getFaltasB3() const { return faltasB3; }
int Materia::getFaltasB4() const { return faltasB4; }
int Materia::getNotaExame() const { return notaExame; }

void Materia::setNotaB1(int x) { notaB1 = x; }
void Materia::setNotaB2(int x) { notaB2 = x; }
void Materia::setNotaB3(int x) { notaB3 = x; }
void Materia::setNotaB4(int x) { notaB4 = x; }
void Materia::setFaltasB1(int x) { faltasB1 = x; }
void Materia::setFaltasB2(int x) { faltasB2 = x; }
void Materia::setFaltasB3(int x) { faltasB3 = x; }
void Materia::setFaltasB4(int x) { faltasB4 = x; }
void Materia::setNotaExame(int x) { notaExame = x; }