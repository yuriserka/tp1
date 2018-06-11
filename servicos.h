#ifndef TRABALHO__SERVICOS__H__
#define TRABALHO__SERVICOS__H__

#include "includes.h"

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
  ResultadoUsuario CadastrarLeitor(Leitor &, const Nome &,
                            const Sobrenome &, const Senha &, const Email &) override;
                            
  ResultadoUsuario CadastrarDev(Desenvolvedor &, const Nome &,
                         const Sobrenome &, const Senha &, const Email &, const Data &) override;

  ResultadoUsuario CadastrarAdm(Administrador &, const Nome &,
                         const Sobrenome &, const Senha &, const Email &, const Data &,
                         const Telefone &, const Address &) override;
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
  vector<VocabularioControlado> ConsultarVocabularios() override;

  vector<Termo> ConsultarTermos(const VocabularioControlado &voc) override;

  vector<Definicao> ConsultarDefinicao(const Termo &) override;

  Resultado CadastrarDesenvolvedor(const VocabularioControlado &, const Email &) override;

  Resultado CadastrarAdministrador(const VocabularioControlado &, const Email &) override;

/*
  Resultado CriarTermo(Termo &, 
                      const Nome &, 
                      const ClasseDoTermo &,
                      const Data &) override;

  Resultado EditarTermo(Termo &, 
                        const Nome &, 
                        const ClasseDoTermo &, 
                        const Data &) override;

  Resultado ExcluirTermo(const Termo &) override;

  Resultado CriarDefinicao(Definicao &, 
                          const TextoDefinicao &, 
                          const Data &) override;

  Resultado EditarDefinicao(Definicao &, 
                          const TextoDefinicao &, 
                          const Data &) override;

  Resultado ExcluirDefinicao(const Definicao &) override;
*/
  Resultado CriarVocabulario(VocabularioControlado &, const Nome &,
                        const Idioma &, const Data &, const Email &) override;

  Resultado EditarVocabulario(VocabularioControlado &, const Nome &,
                              const Idioma &, const Data &) override;

  Resultado ExcluirVocabulario(const VocabularioControlado &) override;
};

#endif //TRABALHO__SERVICOS__H__