#include "Professor.hpp"

Professor::Professor(std::string nome, std::string cpf, tm dataNasci,
                     std::list<std::string> materias)
    : nome{nome}, cpf{cpf}, dataNascimento{dataNasci}, materias{materias} {}

Professor::Professor() {}

Professor::~Professor() {}

bool same(std::string first, std::string second) { return (first == second); }

void Professor::addMaterias(std::string materiaNova) {
  materias.push_back(materiaNova);
  materias.unique(same);
}

void Professor::removeMaterias(std::string materia) { materias.remove(materia); }

std::string Professor::getNome() const { return nome; }
std::string Professor::getCpf() const { return cpf; }
tm Professor::getDataNascimento() const { return dataNascimento; }
std::list<std::string> Professor::getMaterias() const { return materias; }
