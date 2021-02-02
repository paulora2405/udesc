#ifndef _ALUNO_HPP_
#define _ALUNO_HPP_

#include <time.h>

#include <list>
#include <string>
#include <vector>

#include "Materia.hpp"

class Aluno {
private:
  std::string nome;
  std::string cpf;
  tm dataNascimento;
  std::string turma;

public:
  std::vector<Materia> materias;
  /**
   * Construtor parametrizado.
   * @param[in] nome Nome.
   * @param[in] cpf CPF.
   * @param[in] dataNascimento Data nascimento.
   * @param[in] turma Lista de materias.
   */
  Aluno(std::string, std::string, tm, std::string);

  /**
   * Construtor vazio.
   */
  Aluno();
  ~Aluno();

  void addMateria(std::string);
  void removeMateria(std::string);
  void clearMaterias();
  int calculaPorcentagemGeral();
  bool aprovado();

  std::vector<Materia> getMaterias();
  std::string getNome() const;
  std::string getCpf() const;
  tm getDataNascimento() const;
  std::string getTurma() const;
};

#endif