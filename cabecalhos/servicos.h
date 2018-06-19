#ifndef TRABALHO__SERVICOS__H__
#define TRABALHO__SERVICOS__H__

#include "../cabecalhos/../cabecalhos/includes.h"

class CtrlServicoControle : public InterfaceServicoControle {
 public:
  void Construir() override;
};

class CtrlServicoAutenticacao : public InterfaceServicoAutenticacao {
 public:
  Resultado Autenticar(const Email &, const Senha &) override;
};

class CtrlServicoCadastro : public InterfaceServicoCadastro {
 public:
  Resultado CadastrarLeitor(Leitor &, const Nome &,
                            const Sobrenome &, const Senha &,
                            const Email &) override;

  Resultado CadastrarDev(Desenvolvedor &, const Nome &,
                         const Sobrenome &, const Senha &, const Email &,
                         const Data &) override;

  Resultado CadastrarAdm(Administrador &, const Nome &,
                         const Sobrenome &, const Senha &, const Email &,
                         const Data &, const Telefone &,
                         const Address &) override;
};

class CtrlServicoUsuario : public InterfaceServicoUsuario {
 public:

  void Exibir(const Leitor &) override;
  void Exibir(const Desenvolvedor &) override;
  void Exibir(const Administrador &) override;

  ResultadoUsuario Editar(const Leitor &) override;
  ResultadoUsuario Editar(const Desenvolvedor &) override;
  ResultadoUsuario Editar(const Administrador &) override;

  Resultado Excluir(const Email &) override;
 private:
  ResultadoUsuario AtualizaLeitor(const Email &email);
  ResultadoUsuario AtualizaDesenvolvedor(const Email &email);
  ResultadoUsuario AtualizaAdministrador(const Email &email);
};

class CtrlServicoVocabulario : public InterfaceServicoVocabulario {
  /**
   * @brief função herdada que retorna todos os vocabulários armazenados.
   *
   * @return vector<VocabularioControlado> vetor que contém todos os vocabularios armazenados.
   */
  vector<VocabularioControlado> ConsultarVocabularios() override;

  /**
   * @brief função herdada que retorna todos os termos armazenados.
   *
   * @return vector<Termo> vetor que contém todos os termos armazenados.
   */
  vector<Termo> ConsultarTermos() override;

  /**
   * @brief função herdada que retorna todos os termos de determinado vocabulário.
   *
   * @return vector<Termo> vetor que contém os termos do vocabulário.
   */
  vector<Termo> ConsultarTermos(const VocabularioControlado &voc) override;

  /**
   * @brief função herdada que retorna a quantidade de termos associados a determinada definição.
   *
   * @return int quantidade de termos associados a definição.
   */
  int ConsultarTermos(const Definicao &) override;

  /**
   * @brief função herdada que retorna todas as definições armazenadas.
   *
   * @return vector<Definicao> vetor que contém todas as definições armazenadas.
   */
  vector<Definicao> ConsultarDefinicoes() override;

  /**
   * @brief função herdada que retorna todas as definições de determinado termo.
   *
   * @return vector<Definicao> vetor que contém todas as definições do termo.
   */
  vector<Definicao> ConsultarDefinicao(const Termo &) override;

  /**
   * @brief função herdada que retorna a definição de determinado vocabulário.
   *
   * @return Definicao definição do vocabulário.
   */
  Definicao ConsultarDefinicao(const VocabularioControlado &) override;

  /**
   * @brief função herdada que cadastra um usuário como administrador de determinado vocabulario.
   *
   * @return Resultado sucesso ou falha ao cadastrar o usuário.
   */
  Resultado CadastrarAdministrador(const VocabularioControlado &,
                                   const Email &) override;

  /**
   * @brief função herdada que cadastra um usuário como desenvolvedor de determinado vocabulario.
   *
   * @return Resultado sucesso ou falha ao cadastrar o usuário.
   */
  Resultado CadastrarDesenvolvedor(const VocabularioControlado &,
                                   const Email &) override;

  /**
   * @brief função herdada que retorna a quantidade de desenvolvedores de determinado vocabulário.
   *
   * @return int quantidade de desenvolvedores do vocabulário.
   */
  int ConsultarDesenvolvedores(const VocabularioControlado &) override;

  /**
   * @brief função herdada que cria um termo.
   *
   * @return Resultado sucesso ou falha ao criar o termo.
   */
  Resultado CriarTermo(Termo &,
                       const Nome &,
                       const ClasseDoTermo &,
                       const Data &,
                       const VocabularioControlado &) override;

  /**
   * @brief função herdada que edita um termo.
   *
   * @return Resultado sucesso ou falha ao editar o termo.
   */
  Resultado EditarTermo(Termo &, const Data &) override;

  /**
   * @brief função herdada que exclui um termo.
   *
   * @return Resultado sucesso ou falha ao excluir o termo.
   */
  Resultado ExcluirTermo(const Termo &) override;

  /**
   * @brief função herdada que cria uma definição.
   *
   * @return Resultado sucesso ou falha ao criar a definição.
   */
  Resultado CriarDefinicao(Definicao &,
                           const TextoDefinicao &,
                           const Data &) override;

  /**
   * @brief função herdada que edita uma definição.
   *
   * @return Resultado sucesso ou falha ao editar a definição.
   */
  Resultado EditarDefinicao(Definicao &, const Data &) override;

  /**
   * @brief função herdada que exclui uma definição.
   *
   * @return Resultado sucesso ou falha ao excluir a definição.
   */
  Resultado ExcluirDefinicao(const Definicao &) override;

  /**
   * @brief função herdada que cria um vocabulário.
   *
   * @return Resultado sucesso ou falha ao criar o vocabulário.
   */
  Resultado CriarVocabulario(VocabularioControlado &, const Nome &,
                             const Idioma &, const Data &, const Definicao &,
                             const Email &) override;

  /**
   * @brief função herdada que edita um vocabulário.
   *
   * @return Resultado sucesso ou falha ao editar o vocabulário.
   */
  Resultado EditarVocabulario(VocabularioControlado &, const Idioma &,
                              const Data &) override;

  /**
   * @brief função herdada que exclui um vocabulário.
   *
   * @return Resultado sucesso ou falha ao excluir o vocabulário.
   */
  Resultado ExcluirVocabulario(const VocabularioControlado &) override;

  /**
   * @brief função herdada que associa uma definição a um termo.
   *
   * @return Resultado sucesso ou falha ao associar a definição ao termo.
   */
  Resultado AssociarTermoDefinicao(const Termo &, const Definicao &) override;
};

#endif //TRABALHO__SERVICOS__H__