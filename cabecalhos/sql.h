#ifndef TRABALHO__CMDSQL__H__
#define TRABALHO__CMDSQL__H__

#include "../cabecalhos/../cabecalhos/includes.h"

/**
 * @file sql.h
 * @author Yuri Serka e Thiago Matos
 * @date 18 de Junho de 2018
 * 
 * @brief Arquivos com as classes responsáveis pela manipulação do banco
 * de dados, no caso o SQLite.
 */

/**
 * @brief Essa função é necessaria para recuperar os elementos que estão nas
 * colunas das tabelas do banco de dados.
 * 
 */
class ElementoResultado {
 public:
  /**
   * @brief Seta o NomeColuna do objeto.
   * 
   * o nome coluna é nada mais do que o nome da coluna da tabela.
   * 
   * @param colname coluna que está sendo lida no momento.
   */
  inline void SetNomeColuna(const string &colname) {
    this->nome_coluna_ = colname;
  }

 /**
   * @brief Seta o ValorColuna do objeto.
   * 
   * o valor coluna é nada mais do que o valor da coluna que esta 
   * em nome_coluna_ da tabela.
   * 
   * @param colval valor da coluna que está sendo lida no momento.
   */
  inline void SetValorColuna(const string &colval) {
    this->valor_coluna_ = colval;
  }

  /**
   * @brief Retorna o nome_coluna_ da tabela.
   * 
   * @return string corresponde ao nome da coluna especifica.
   */
  inline string GetNomeColuna() const {
    return nome_coluna_;
  }

  /**
   * @brief Retorna o valor_coluna_ da tabela.
   * 
   * @return string corresponde ao valor da coluna especifica.
   */
  inline string GetValorColuna() const {
    return valor_coluna_;
  }

 private:
  string nome_coluna_;
  string valor_coluna_;
};

/**
 * @brief Classe principal de Execução dos comandos para o SQLite.
 * 
 */
class ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSQL, nele já é determinado
   * qual será o nome do banco de dados.
   *
   */
  ComandoSql() {
    nome_banco_de_dados_ = "databank.db";
  }

  /**
   * @brief Função responsavel por se conectar ao banco de dados, realizar o
   * comando e desconectar.
   * 
   */
  void Executar();

 protected:
  /**
   * @brief string que irá conter o comando que será passado para o SQlite. 
   * 
   */
  string cmdSql_;
  
  /**
   * @brief lista utilizada para recuperar os dados das tabelas do banco de dados.
   * 
   */
  static list<ElementoResultado> lista_resultado_;

 private:
  const char *nome_banco_de_dados_;
  sqlite3 *bd_;
  char *mensagem_;
  int rc_;
  void Conectar();
  void Desconectar();
  static int Callback(void *, int, char **, char **);
};

/**
 * @brief Classe de comando para Sql que cadastra um usuario no banco de dados.
 * 
 */
class ComandoSqlCadastrar : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlCadastrar.
   *
   */
  ComandoSqlCadastrar() = default;

  /**
   * @brief Construtor da classe ComandoSqlCadastrar que recebe um leitor e 
   * o tipo da conta que no caso sera uma string "leitor".
   * 
   * @param leitor Leitor que será cadastrado
   * @param conta string "leitor"
   */
  explicit ComandoSqlCadastrar(const Leitor &leitor, string conta) {
    cmdSql_ = "INSERT or IGNORE INTO usuarios (nome, sobrenome, senha, email, conta)"\
      " VALUES (";
    cmdSql_ += "'" + leitor.GetNome().GetNome() + "', ";
    cmdSql_ += "'" + leitor.GetSobrenome().GetSobrenome() + "', ";
    cmdSql_ += "'" + leitor.GetSenha().GetSenha() + "', ";
    cmdSql_ += "'" + leitor.GetEmail().GetEmail() + "', ";
    cmdSql_ += "'" + conta + "');";
  }
  
  /**
   * @brief Construtor da classe ComandoSqlCadastrar que recebe um Desenvolvedor e 
   * o tipo da conta que no caso sera uma string "desenvolvedor".
   * 
   * @param dev desenvolvedor que será cadastrado
   * @param conta string "desenvolvedor"
   */
  explicit ComandoSqlCadastrar(const Desenvolvedor &dev, string conta) {
    cmdSql_ = "INSERT or IGNORE INTO usuarios (nome, sobrenome, senha, email, "\
      "nascimento, conta) VALUES (";
    cmdSql_ += "'" + dev.GetNome().GetNome() + "', ";
    cmdSql_ += "'" + dev.GetSobrenome().GetSobrenome() + "', ";
    cmdSql_ += "'" + dev.GetSenha().GetSenha() + "', ";
    cmdSql_ += "'" + dev.GetEmail().GetEmail() + "', ";
    cmdSql_ += "'" + dev.GetDataDeNascimento().GetData() + "', ";
    cmdSql_ += "'" + conta + "');";
  }
  
  /**
   * @brief Construtor da classe ComandoSqlCadastrar que recebe um Administrador e 
   * o tipo da conta que no caso sera uma string "administrador".
   * 
   * @param adm administrador que será cadastrado.
   * @param conta string "administrador"
   */
  explicit ComandoSqlCadastrar(const Administrador &adm, string conta) {
    cmdSql_ = "INSERT or IGNORE INTO usuarios (nome, sobrenome, senha, email, "\
      "nascimento, telefone, endereco, conta) VALUES (";
    cmdSql_ += "'" + adm.GetNome().GetNome() + "', ";
    cmdSql_ += "'" + adm.GetSobrenome().GetSobrenome() + "', ";
    cmdSql_ += "'" + adm.GetSenha().GetSenha() + "', ";
    cmdSql_ += "'" + adm.GetEmail().GetEmail() + "', ";
    cmdSql_ += "'" + adm.GetDataDeNascimento().GetData() + "', ";
    cmdSql_ += "'" + adm.GetTelefone().GetTelefone() + "', ";
    cmdSql_ += "'" + adm.GetEndereco().GetAddress() + "', ";
    cmdSql_ += "'" + conta + "');";
  }
  
  explicit ComandoSqlCadastrar(const VocabularioControlado &voc, const Definicao &def, const Email &email) {
    cmdSql_ = "INSERT or IGNORE INTO vocabularios (nome, idioma, data, definicao, administrador)"\
      "VALUES (";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "', ";
    cmdSql_ += "'" + voc.GetIdioma().GetIdioma() + "', ";
    cmdSql_ += "'" + voc.GetData().GetData() + "', ";
    cmdSql_ += "'" + def.GetDefinicao().GetDefinicao() + "', ";
    cmdSql_ += "'" + email.GetEmail() + "');";
  }

  explicit ComandoSqlCadastrar(const Termo &termo, const VocabularioControlado &voc) {
    cmdSql_ = "INSERT or IGNORE INTO termos (nome, classe, data, vocabulario)"\
      "VALUES (";
    cmdSql_ += "'" + termo.GetNome().GetNome() + "', ";
    cmdSql_ += "'" + termo.GetPreferencia().GetPreferencia() + "', ";
    cmdSql_ += "'" + termo.GetData().GetData() + "', ";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "');";
  }

  explicit ComandoSqlCadastrar(const Definicao &def) {
    cmdSql_ = "INSERT or IGNORE INTO definicoes (texto, data)"\
      "VALUES (";
    cmdSql_ += "'" + def.GetDefinicao().GetDefinicao() + "', ";
    cmdSql_ += "'" + def.GetData().GetData() + "');";
  }

  explicit ComandoSqlCadastrar(const VocabularioControlado &voc, const Desenvolvedor &dev) {
    cmdSql_ = "INSERT or IGNORE INTO vocabularios (nome, idioma, data, desenvolvedor)"\
      "VALUES (";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "', ";
    cmdSql_ += "'" + voc.GetIdioma().GetIdioma() + "', ";
    cmdSql_ += "'" + voc.GetData().GetData() + "', ";
    cmdSql_ += "'" + dev.GetEmail().GetEmail() + "');";
  }
};

/**
 * @brief Classe responsavel por Atualizar os registros das Tabelas do banco de dados.
 * 
 */
class ComandoSqlAtualizar : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlAtualizar.
   *
   */
  ComandoSqlAtualizar() = default;

  /**
   * @brief Construtor da classe ComandoSqlAtualizar que recebe um leitor, 
   * este que terá seus dados gravados gravados no banco de dados de volta.
   * 
   * @param leitor Leitor que será atualizado
   */
  explicit ComandoSqlAtualizar(const Leitor &leitor) {
    cmdSql_ = "UPDATE usuarios ";
    cmdSql_ += "SET nome = '" + leitor.GetNome().GetNome();
    cmdSql_ += "', sobrenome = '" + leitor.GetSobrenome().GetSobrenome();
    cmdSql_ += "', senha = '" + leitor.GetSenha().GetSenha();
    cmdSql_ += "' WHERE email = '" + leitor.GetEmail().GetEmail() + "';";
  }

  /**
   * @brief Construtor da classe ComandoSqlAtualizar que recebe um Desenvolvedor, 
   * este que terá seus dados gravados gravados no banco de dados de volta.
   * 
   * @param dev Desenvolvedor que será atualizado
   */
  explicit ComandoSqlAtualizar(const Desenvolvedor &dev) {
    cmdSql_ = "UPDATE usuarios ";
    cmdSql_ += "SET nome = '" + dev.GetNome().GetNome();
    cmdSql_ += "', sobrenome = '" + dev.GetSobrenome().GetSobrenome();
    cmdSql_ += "', senha = '" + dev.GetSenha().GetSenha();
    cmdSql_ += "', nascimento = '" + dev.GetDataDeNascimento().GetData();
    cmdSql_ += "' WHERE email = '" + dev.GetEmail().GetEmail() + "';";
  }

  /**
   * @brief Construtor da classe ComandoSqlAtualizar que recebe um Administrador, 
   * este que terá seus dados gravados gravados no banco de dados de volta.
   * 
   * @param adm Administrador que será atualizado
   */
  explicit ComandoSqlAtualizar(const Administrador &adm) {
    cmdSql_ = "UPDATE usuarios ";
    cmdSql_ += "SET nome =      '" + adm.GetNome().GetNome();
    cmdSql_ += "', sobrenome =  '" + adm.GetSobrenome().GetSobrenome();
    cmdSql_ += "', senha =      '" + adm.GetSenha().GetSenha();
    cmdSql_ += "', nascimento = '" + adm.GetDataDeNascimento().GetData();
    cmdSql_ += "', telefone =   '" + adm.GetTelefone().GetTelefone();
    cmdSql_ += "', endereco =   '" + adm.GetEndereco().GetAddress();
    cmdSql_ += "' WHERE email = '" + adm.GetEmail().GetEmail() + "';";
  }

  explicit ComandoSqlAtualizar(const VocabularioControlado &voc) {
    cmdSql_ = "UPDATE vocabularios ";
    cmdSql_ += "SET idioma = '" + voc.GetIdioma().GetIdioma() + "', ";
    cmdSql_ += "data =       '" + voc.GetData().GetData() + "' ";
    cmdSql_ += "WHERE nome = '" + voc.GetNome().GetNome() + "';";
  }

  explicit ComandoSqlAtualizar(const Termo &termo) {
    cmdSql_ = "UPDATE termos ";
    cmdSql_ += "SET data =   '" + termo.GetData().GetData() + "' ";
    cmdSql_ += "WHERE nome = '" + termo.GetNome().GetNome() + "';";
  }

  explicit ComandoSqlAtualizar(const Definicao &def) {
    cmdSql_ = "UPDATE definicoes ";
    cmdSql_ += "SET data =    '" + def.GetData().GetData() + "'";
    cmdSql_ += "WHERE texto = '" + def.GetDefinicao().GetDefinicao() + "';";
  }

  explicit ComandoSqlAtualizar(const Administrador &dev, const VocabularioControlado &voc) {
    cmdSql_ = "UPDATE vocabularios ";
    cmdSql_ += "SET administrador = '" + dev.GetEmail().GetEmail();
    cmdSql_ += "' WHERE nome =      '" + voc.GetNome().GetNome() + "';";
  }
};

class ComandoSqlAssociar : public ComandoSql {
 public:
  ComandoSqlAssociar() = default;
  explicit ComandoSqlAssociar(const Email &email, const VocabularioControlado &voc) {
    cmdSql_ = "INSERT or IGNORE INTO desenvolvedor_vocabulario (desenvolvedor, vocabulario)"\
      " VALUES (";
    cmdSql_ += "'" + email.GetEmail() + "', ";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "');";
  }

  explicit ComandoSqlAssociar(const Termo &termo, const Definicao &def) {
    cmdSql_ = "INSERT or IGNORE INTO termo_definicao (termo, definicao)"\
      " VALUES (";
    cmdSql_ += "'" + termo.GetNome().GetNome() + "', ";
    cmdSql_ += "'" + def.GetDefinicao().GetDefinicao() + "');";
  }
};

/**
 * @brief Classe reponsavel pela inicialização de todas as tabelas do banco de dados.
 * 
 */
class ComandoSqlCriarTabelas : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlCriarTabelas.
   * 
   * Será contruida as tabelas de usuarios, vocabularios, termos, definicoes,
   * termo_definicoes e desenvolvedor_vocabulario.
   *
   */
  explicit ComandoSqlCriarTabelas();
};

/**
 * @brief Classe reponsavel por recuperar a senha do banco de dados.
 * 
 */
class ComandoSqlLerSenha : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlLerSenha.
   *
   */
  ComandoSqlLerSenha() = default;

   /**
   * @brief Construtor da classe ComandoSqlLerSenha que recebe um Email e 
   * retorna qual a senha associada a este email.
   * 
   * @param email email que servirá de base para a pesquisa da senha.
   */
  explicit ComandoSqlLerSenha(const Email &email) {
    cmdSql_ = "SELECT senha FROM usuarios WHERE email = ";
    cmdSql_ += "'" + email.GetEmail() + "';";
  }
  
  /**
   * @brief Faz uma varredura na tabela de acordo com o comando para o sql e 
   * retorna a senha que esta associada ao email que foi passado no construtor.
   * 
   * @return string Senha cadastrada no banco de dados.
   */
  string RecuperaSenha() const;
};

/**
 * @brief Classe reponsavel por recuperar o Email do banco de dados.
 * 
 */
class ComandoSqlLerEmail : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlLerEmail.
   *
   */
  ComandoSqlLerEmail() = default;

  /**
   * @brief Construtor da classe ComandoSqlLerEmail que recebe um Email e 
   * retorna o email.
   * 
   * Essa função serve para verificar se o email já está cadastrado no banco de dados.
   * 
   * @param email email que servirá de base para a pesquisa do email.
   */
  explicit ComandoSqlLerEmail(const Email &email) {
    cmdSql_ = "SELECT email FROM usuarios WHERE email = ";
    cmdSql_ += "'" + email.GetEmail() + "';";
  }

  /**
   * @brief Faz uma varredura na tabela de acordo com o comando para o sql e 
   * retorna o email que esta associado ao email que foi passado no construtor.
   * 
   * @return string Email cadastrada no banco de dados, caso o email passado não
   * esteja cadastrado, é lançada uma exceção.
   */
  string RecuperaEmail() const;
};

/**
 * @brief Classe reponsavel por recuperar o tipo da Conta do banco de dados.
 * 
 */
class ComandoSqlTipoConta : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlTipoConta.
   *
   */
  ComandoSqlTipoConta() = default;

  /**
   * @brief Construtor da classe ComandoSqlTipoConta que recebe um Email e 
   * retorna o tipo da conta deste email, ou seja, desenvolvedor, administrador ou leitor.
   * 
   * @param email email que servirá de base para a pesquisa do tipo da conta.
   */
  explicit ComandoSqlTipoConta(const Email &email) {
    cmdSql_ = "SELECT conta FROM usuarios WHERE email = ";
    cmdSql_ += "'" + email.GetEmail() + "';";
  }

  /**
   * @brief Faz uma varredura na tabela de acordo com o comando para o sql e 
   * retorna o tipo da conta que esta associada ao email que foi passado no construtor.
   * 
   * @return string Tipo da conta cadastrada no banco de dados.
   */
  string RecuperaConta() const;
};

/**
 * @brief Classe reponsavel por recuperar todos os dados de um usuario 
 * do banco de dados.
 * 
 */
class ComandoSqlPesquisarUsuario : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlPesquisarUsuario.
   *
   */
  ComandoSqlPesquisarUsuario() = default;

  /**
   * @brief Construtor da classe ComandoSqlPesquisarUsuario que recebe um Email e 
   * retorna ou um leitor, ou um desenvolvedor ou um administrador essa função é usada em 
   * conjunto com o ComandoSqlTipoConta.
   * 
   * @param email email que servirá de base para a pesquisa do usuario.
   */
  explicit ComandoSqlPesquisarUsuario(const Email &email) {
    cmdSql_ = "SELECT * FROM usuarios WHERE email = ";
    cmdSql_ += "'" + email.GetEmail() + "';";
  }

  /**
   * @brief Faz uma varredura na tabela de acordo com o comando para o sql e 
   * retorna o usuario que esta associada ao email que foi passado no construtor.
   * 
   * @return Leitor leitor que será construido com os argumentos vindos do banco de dados.
   */
  Leitor GetLeitor() const;

  /**
   * @brief Faz uma varredura na tabela de acordo com o comando para o sql e 
   * retorna o usuario que esta associada ao email que foi passado no construtor.
   * 
   * @return Desenvolvedor desenvolvedor que será construido com os argumentos vindos do banco de dados.
   */
  Desenvolvedor GetDev() const;

  /**
   * @brief Faz uma varredura na tabela de acordo com o comando para o sql e 
   * retorna o usuario que esta associada ao email que foi passado no construtor.
   * 
   * @return Administrador administrador que será construido com os argumentos vindos do banco de dados.
   */
  Administrador GetAdm() const;
};

class ComandoSqlConsultarVocabs : public ComandoSql {
 public:
  explicit ComandoSqlConsultarVocabs() {
    cmdSql_ = "SELECT nome, idioma, data FROM vocabularios;";
  }

  explicit ComandoSqlConsultarVocabs(const Administrador &adm) {
    cmdSql_ = "SELECT nome, idioma, data FROM vocabularios WHERE administrador = ";
    cmdSql_ += "'" + adm.GetEmail().GetEmail() + "';";
  }

  explicit ComandoSqlConsultarVocabs(const Email &email) {
    cmdSql_ = "SELECT nome, idioma, data FROM vocabularios WHERE administrador = ";
    cmdSql_ += "'" + email.GetEmail() + "';";
  }

  vector<VocabularioControlado> GetVocabs();
};

class ComandoSqlConsultarTermos : public ComandoSql {
 public:
  explicit ComandoSqlConsultarTermos() {
    cmdSql_ = "SELECT nome, classe, data FROM termos;";
  }

  explicit ComandoSqlConsultarTermos(const VocabularioControlado &voc) {
    cmdSql_ = "SELECT nome, classe, data FROM termos WHERE vocabulario = ";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "';";
  }

  explicit ComandoSqlConsultarTermos(const Definicao &def) {
    cmdSql_ = "SELECT termo FROM termo_definicao WHERE definicao = ";
    cmdSql_ += "'" + def.GetDefinicao().GetDefinicao() + "';";
  }

  vector<Termo> GetTermos();
  vector<Nome> GetNomes();
};

class ComandoSqlConsultarDefinicao : public ComandoSql {
 public:
  explicit ComandoSqlConsultarDefinicao() {
    cmdSql_ = "SELECT texto, data FROM definicoes;";
  }

  explicit ComandoSqlConsultarDefinicao(const Termo &termo) {
    cmdSql_ = "SELECT definicoes.texto, definicoes.data ";
    cmdSql_ += "FROM definicoes JOIN termo_definicao ";
    cmdSql_ += "ON definicoes.texto = termo_definicao.definicao ";
    cmdSql_ += "JOIN termos ";
    cmdSql_ += "ON termos.nome = termo_definicao.termo and termos.nome = ";
    cmdSql_ += "'" + termo.GetNome().GetNome() + "';";
  }

  explicit ComandoSqlConsultarDefinicao(const VocabularioControlado &voc) {
    cmdSql_ = "SELECT texto, data FROM definicoes WHERE texto = ";
    cmdSql_ += "(SELECT definicao FROM vocabularios WHERE nome = ";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "');";
  }

  vector<Definicao> GetDefinicoes();
  Definicao GetDefinicao();
};

class ComandoSqlConsultarDevs : public ComandoSql {
 public:
  ComandoSqlConsultarDevs() = default;

  explicit ComandoSqlConsultarDevs(const VocabularioControlado &voc) {
    cmdSql_ = "SELECT desenvolvedor FROM desenvolvedor_vocabulario WHERE vocabulario = ";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "';";
  }

  vector<Email> GetDevs();
};

class ComandoSqlRemover : public ComandoSql {
 public:
  /**
   * @brief Construtor padrão da classe ComandoSqlRemover.
   *
   */
  ComandoSqlRemover() = default;
  
  /**
   * @brief Construtor da classe ComandoSqlRemover que recebe um Email e 
   * exclui os dados desta conta, caso seja um administrador todos os vabularios
   * sao excluidos juntos e os termos associados a estes vacabularios tambem.
   * 
   * @param email email que servirá de base para a remoção do usuario.
   */
  explicit ComandoSqlRemover(const Email &email) {
    cmdSql_ = "DELETE FROM desenvolvedor_vocabulario WHERE desenvolvedor = ";
    cmdSql_ += "'" + email.GetEmail() + "'; ";
    cmdSql_ += "DELETE FROM usuarios WHERE email = ";
    cmdSql_ += "'" + email.GetEmail() + "'; ";
  }
  
  explicit ComandoSqlRemover(const VocabularioControlado &voc) {
    cmdSql_ = "DELETE FROM desenvolvedor_vocabulario WHERE vocabulario = ";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "';";
    cmdSql_ += "DELETE FROM vocabularios WHERE nome = ";
    cmdSql_ += "'" + voc.GetNome().GetNome() + "';";
  }

  explicit ComandoSqlRemover(const Termo &termo) {
    cmdSql_ = "DELETE FROM termo_definicao WHERE termo = ";
    cmdSql_ += "'" + termo.GetNome().GetNome() + "'; ";
    cmdSql_ += "DELETE FROM termos WHERE nome =           ";
    cmdSql_ += "'" + termo.GetNome().GetNome() + "'; ";
  }

  explicit ComandoSqlRemover(const Definicao &def) {
    cmdSql_ = "DELETE FROM termo_definicao WHERE definicao =  ";
    cmdSql_ += "'" + def.GetDefinicao().GetDefinicao() + "'; ";
    cmdSql_ += "DELETE FROM definicoes WHERE texto =           ";
    cmdSql_ += "'" + def.GetDefinicao().GetDefinicao() + "';";
  }
};

#endif  //TRABALHO__CMDSQL__H__
