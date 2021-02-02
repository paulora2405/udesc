#ifndef _PROFESSOR_HPP_
#define _PROFESSOR_HPP_

#include <time.h>

#include <list>
#include <string>

class Professor {
private:
  std::string nome;
  std::string cpf;
  tm dataNascimento;
  std::list<std::string> materias;

public:
  /**
   * Construtor parametrizado.
   * @param[in] nome Nome.
   * @param[in] cpf CPF.
   * @param[in] dataNascimento Data nascimento.
   * @param[in] materias Lista de materias.
   */
  Professor(std::string, std::string, tm, std::list<std::string>);

  /**
   * Construtor vazio.
   */
  Professor();
  ~Professor();

  std::string getNome() const;
  std::string getCpf() const;
  tm getDataNascimento() const;
  std::list<std::string> getMaterias() const;
  void addMaterias(std::string);
  void removeMaterias(std::string);
};

#endif