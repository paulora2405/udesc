#include "Aluno.hpp"

Aluno::Aluno(std::string nome, std::string cpf, tm dataNasci, std::string turma)
    : nome{nome}, cpf{cpf}, dataNascimento{dataNasci}, turma{turma} {}

Aluno::Aluno() {}

Aluno::~Aluno() {}

void Aluno::addMateria(std::string nomeMateria) {
  std::vector<Materia>::iterator it = materias.begin();
  while(it != materias.end()) {
    if((*it).getNomeMateria() == nomeMateria) {
      return;
    }
    it++;
  }
  materias.push_back(Materia{nomeMateria});
}

void Aluno::removeMateria(std::string nomeMateria) {
  std::vector<Materia>::iterator it = materias.begin();
  while(it != materias.end()) {
    if((*it).getNomeMateria() == nomeMateria) {
      materias.erase(it);
      break;
    }
    it++;
  }
}

void Aluno::clearMaterias() { materias.clear(); }

int Aluno::calculaPorcentagemGeral() {
  if(materias.empty()) return 0;

  int somaPorcentagem = 0;

  for(int i = 0; i < materias.size(); i++) {
    somaPorcentagem += materias[i].getPorcentagemFrequencia();
  }

  return nearbyint(somaPorcentagem / (int)materias.size());
}

bool Aluno::aprovado() {
  if(materias.empty()) return false;

  // reprovação por falta se presença por menor que 50%
  if(calculaPorcentagemGeral() < 50) return false;

  for(int i = 0; i < materias.size(); i++) {
    if(materias[i].calculaMediaFinal() < 70)
      if(materias[i].calculaMediaPosExame() < 70) return false;
  }

  return true;
}

std::vector<Materia> Aluno::getMaterias() { return materias; }
std::string Aluno::getNome() const { return nome; }
std::string Aluno::getCpf() const { return cpf; }
tm Aluno::getDataNascimento() const { return dataNascimento; }
std::string Aluno::getTurma() const { return turma; }
