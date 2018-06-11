#include "../cabecalhos/includes.h"

void CtrlServicoControle::Construir() {
  ComandoSql *servico_sql;
  servico_sql = new ComandoSqlCriarTabelas();
  servico_sql->Executar();
  
  InterfaceApresentacaoAutenticacao *ctrl_aa;
  InterfaceApresentacaoUsuario *ctrl_au;
  InterfaceApresentacaoVocabulario *ctrl_av;
  InterfaceApresentacaoCadastro *ctrl_ak;

  ctrl_aa = new CtrlApresentacaoAutenticacao();
  ctrl_au = new CtrlApresentacaoUsuario();
  ctrl_av = new CtrlApresentacaoVocabulario();
  ctrl_ak = new CtrlApresentacaoCadastro();

  InterfaceServicoAutenticacao *ctrl_sa;
  InterfaceServicoUsuario *ctrl_su;
  InterfaceServicoVocabulario *ctrl_sv;
  InterfaceServicoCadastro *ctrl_sk;

  ctrl_sa = new CtrlServicoAutenticacao();
  ctrl_su = new CtrlServicoUsuario();
  ctrl_sv = new CtrlServicoVocabulario();
  ctrl_sk = new CtrlServicoCadastro();

  ctrl_aa->SetCtrlServicoAutenticacao(ctrl_sa);
  ctrl_au->SetCtrlServicoUsuario(ctrl_su);
  ctrl_av->SetCtrlServicoVocabulario(ctrl_sv);
  ctrl_ak->SetCtrlServicoCadastro(ctrl_sk);

  InterfaceApresentacaoControle *ctrl_ac;

  ctrl_ac = new CtrlApresentacaoControle();

  ctrl_ac->SetCtrlApresentacaoAutenticacao(ctrl_aa);
  ctrl_ac->SetCtrlApresentacaoCadastro(ctrl_ak);
  ctrl_ac->SetCtrlApresentacaoUsuario(ctrl_au);
  ctrl_ac->SetCtrlApresentacaoVocabulario(ctrl_av);

  ctrl_ac->Inicializar();

  delete servico_sql;
  delete ctrl_aa;
  delete ctrl_au;
  delete ctrl_av;
  delete ctrl_ak;
  delete ctrl_sa;
  delete ctrl_su;
  delete ctrl_sv;
  delete ctrl_sk;
  delete ctrl_ac;
}


Resultado CtrlServicoAutenticacao::Autenticar(const Email &email, const Senha &senha) {
  ResultadoAutenticar resultado;
  ComandoSqlLerEmail *cmd = new ComandoSqlLerEmail(email);
  try {
    cmd->Executar();
    cmd->RecuperaEmail();
    delete cmd;
  } catch (ErroDePersistencia &e) {
    cout << "Email nao cadastrado\n";
    delete cmd;
    resultado.SetResultado(ResultadoAutenticar::kfalha_);
    return resultado;
  }

  ComandoSqlLerSenha *comando = new ComandoSqlLerSenha(email);
  try {
    comando->Executar();
    string senha_recuperada = comando->RecuperaSenha();
    if (senha.GetSenha() == senha_recuperada) {
      resultado.SetResultado(ResultadoAutenticar::ksucesso_);
    } else {
      resultado.SetResultado(ResultadoAutenticar::kfalha_);
    }
    delete comando;
  } catch (ErroDePersistencia &e) {
    resultado.SetResultado(ResultadoAutenticar::kfalha_);
    delete comando;
    throw invalid_argument("Erro de Sistema!\n");
  }
  
  return resultado;
}

ResultadoUsuario CtrlServicoCadastro::CadastrarLeitor(Leitor &novoleitor, 
                                        const Nome &nome,
                                        const Sobrenome &sobrenome, 
                                        const Senha &senha, 
                                        const Email &email) {
  ResultadoUsuario resultado;
  try {
    novoleitor = Leitor(nome, sobrenome, senha, email);
  }
  catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    system(PAUSE);
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }

  resultado.SetResultado(Resultado::ksucesso_);
  resultado.SetLeitorResultado(novoleitor);
  return resultado;
}

ResultadoUsuario CtrlServicoCadastro::CadastrarDev(Desenvolvedor &novodev,
                                     const Nome &nome,
                                     const Sobrenome &sobrenome,
                                     const Senha &senha,
                                     const Email &email,
                                     const Data &data) {
  ResultadoUsuario resultado;
  try {
    novodev = Desenvolvedor(nome, sobrenome, senha, email, data);
  }
  catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    system(PAUSE);
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }

  resultado.SetResultado(Resultado::ksucesso_);
  resultado.SetDevResultado(novodev);
  return resultado;
}

ResultadoUsuario CtrlServicoCadastro::CadastrarAdm(Administrador &novoadm, 
                                     const Nome &nome,
                                     const Sobrenome &sobrenome, 
                                     const Senha &senha,
                                     const Email &email, 
                                     const Data &data, 
                                     const Telefone &telefone, 
                                     const Address &endereco) {
  ResultadoUsuario resultado;
  try {
    novoadm = Administrador(nome, sobrenome, senha, email, data, telefone, endereco);
  }
  catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    system(PAUSE);
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }

  resultado.SetResultado(Resultado::ksucesso_);
  resultado.SetAdmResultado(novoadm);
  return resultado;
}

void CtrlServicoUsuario::Exibir(const Leitor &leitor) {
  cout << "Nome: " << leitor.GetNome().GetNome() << " ";
  cout << leitor.GetSobrenome().GetSobrenome() << "\n";
  cout << "Email: " << leitor.GetEmail().GetEmail() << "\n";
  cout << "Senha: " << leitor.GetSenha().GetSenha() << "\n";
}

void CtrlServicoUsuario::Exibir(const Desenvolvedor &desenvolvedor) {
  cout << "Nome: " << desenvolvedor.GetNome().GetNome() << " ";
  cout << desenvolvedor.GetSobrenome().GetSobrenome() << "\n";
  cout << "Email: " << desenvolvedor.GetEmail().GetEmail() << "\n";
  cout << "Senha: " << desenvolvedor.GetSenha().GetSenha() << "\n";
  cout << "Data de Nascimento: " << desenvolvedor.GetDataDeNascimento().GetData() << "\n";
}

void CtrlServicoUsuario::Exibir(const Administrador &administrador) {
  cout << "Nome: " << administrador.GetNome().GetNome() << " ";
  cout << administrador.GetSobrenome().GetSobrenome() << "\n";
  cout << "Email: " << administrador.GetEmail().GetEmail() << "\n";
  cout << "Senha: " << administrador.GetSenha().GetSenha() << "\n";
  cout << "Data de Nascimento: " << administrador.GetDataDeNascimento().GetData() << "\n";
  cout << "Telefone: " << administrador.GetTelefone().GetTelefone() << "\n";
  cout << "Endereco: " << administrador.GetEndereco().GetAddress() << "\n";
}

ResultadoUsuario CtrlServicoUsuario::Editar(const Leitor &leitor) {
  ResultadoUsuario resultado;
  resultado = AtualizaLeitor(leitor.GetEmail());
  return resultado;
}

ResultadoUsuario CtrlServicoUsuario::Editar(const Desenvolvedor &dev) {
  ResultadoUsuario resultado;
  resultado = AtualizaDesenvolvedor(dev.GetEmail());
  return resultado;
}

ResultadoUsuario CtrlServicoUsuario::Editar(const Administrador &adm) {
  ResultadoUsuario resultado;
  resultado = AtualizaAdministrador(adm.GetEmail());
  return resultado;
}

ResultadoUsuario CtrlServicoUsuario::AtualizaLeitor(const Email &email) {
  Leitor novoleitor;
  ResultadoUsuario resultado;

  string inome, isobrenome, isenha;
  Nome nome;
  Sobrenome sobrenome;
  Senha senha;

  do {
    try {
      system(CLEAR);
      cout << "Digite seu Nome: ";
      cin >> inome;
      nome = Nome(inome);

      cout << "Digite seu Sobrenome: ";
      cin >> isobrenome;
      sobrenome = Sobrenome(isobrenome);

      cout << "Digite sua Senha: ";
      cin >> isenha;
      senha = Senha(isenha);

      break;
    }
    catch (exception &e) {
      cout << "\n\t" << e.what() << "\n";
      system(PAUSE);
    }
  } while (true);

  try {
    novoleitor = Leitor(nome, sobrenome, senha, email);
  }
  catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }

  resultado.SetResultado(Resultado::ksucesso_);
  resultado.SetLeitorResultado(novoleitor);

  return resultado;
}

ResultadoUsuario CtrlServicoUsuario::AtualizaDesenvolvedor(const Email &email) {
  Desenvolvedor novodev;
  ResultadoUsuario resultado;

  string inome, isobrenome, isenha, idata;
  Nome nome;
  Sobrenome sobrenome;
  Senha senha;
  Data data;

  do {
    try {
      system(CLEAR);
      cout << "Digite seu Nome: ";
      cin >> inome;
      nome = Nome(inome);

      cout << "Digite seu Sobrenome: ";
      cin >> isobrenome;
      sobrenome = Sobrenome(isobrenome);

      cout << "Digite sua Data de Nascimento: ";
      cin >> idata;
      data = Data(idata);

      cin.clear();
      cin.ignore();

      cout << "Digite sua Senha: ";
      cin >> isenha;
      senha = Senha(isenha);

      break;
    }
    catch (exception &e) {
      cout << "\n\t" << e.what() << "\n";
      system(PAUSE);
    }
  } while (true);

  try {
    novodev = Desenvolvedor(nome, sobrenome, senha, email, data);
  }
  catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }

  resultado.SetResultado(Resultado::ksucesso_);
  resultado.SetDevResultado(novodev);

  return resultado;
}

ResultadoUsuario CtrlServicoUsuario::AtualizaAdministrador(const Email &email) {
  Administrador novoadm;
  ResultadoUsuario resultado;

  string inome, isobrenome, isenha, idata, iaddres, itelefone;
  Nome nome;
  Sobrenome sobrenome;
  Senha senha;
  Data data;
  Address endereco;
  Telefone telefone;

  do {
    try {
      system(CLEAR);
      cout << "Digite seu Nome: ";
      cin >> inome;
      nome = Nome(inome);

      cout << "Digite seu Sobrenome: ";
      cin >> isobrenome;
      sobrenome = Sobrenome(isobrenome);

      cout << "Digite sua Data de Nascimento: ";
      cin >> idata;
      data = Data(idata);

      cin.clear();
      cin.ignore();

      cout << "Digite seu Telefone: ";
      getline(cin, itelefone);
      telefone = Telefone(itelefone);

      cout << "Digite seu Endereco: ";
      getline(cin, iaddres);
      endereco = Address(iaddres);

      cout << "Digite sua Senha: ";
      cin >> isenha;
      senha = Senha(isenha);

      break;
    }
    catch (exception &e) {
      cout << "\n\t" << e.what() << "\n";
      system(PAUSE);
    }
  } while (true);

  try {
    novoadm = Administrador(nome, sobrenome, senha, email, data, telefone, endereco);
  }
  catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }

  resultado.SetResultado(Resultado::ksucesso_);
  resultado.SetAdmResultado(novoadm);

  return resultado;
}

Resultado CtrlServicoUsuario::Excluir(const Email &email) {
  string isenha;
  Senha senha;
  Resultado resultado;
  system(CLEAR);
  cout << "Digite sua senha para confirmar: ";
  try {
    ComandoSqlLerSenha *comando;
    cin >> isenha;
    senha = Senha(isenha);
    comando = new ComandoSqlLerSenha(email);
    comando->Executar();
    string senha_recuperada = comando->RecuperaSenha();
    if (senha.GetSenha() == senha_recuperada) {
      resultado.SetResultado(ResultadoAutenticar::ksucesso_);
    } else {
      resultado.SetResultado(ResultadoAutenticar::kfalha_);
    }
    delete comando;
  } catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
  }

  if (resultado.GetResultado() == ResultadoAutenticar::kfalha_) {
    cout << "Falha de autenticacao!\n";
    return resultado;
  } 

  try {
    ComandoSqlRemover *comando = new ComandoSqlRemover(email);
    comando->Executar();
    delete comando;
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }
  resultado.SetResultado(Resultado::ksucesso_);
  return resultado;
}

vector<VocabularioControlado> CtrlServicoVocabulario::ConsultarVocabularios() {
  ComandoSqlConsultarVocabs *comando;
  comando = new ComandoSqlConsultarVocabs();
  vector<VocabularioControlado> vocabularios;
  try {
    comando->Executar();
    vocabularios = comando->GetVocabs();
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
  }
  
  delete comando;
  return vocabularios;
}

vector<Termo> CtrlServicoVocabulario::ConsultarTermos(const VocabularioControlado &voc) {
  ComandoSqlConsultarTermos *comando;
  comando = new ComandoSqlConsultarTermos(voc);
  vector<Termo> termos;
  try {
    comando->Executar();
    termos = comando->GetTermos();
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
  }

  delete comando;  
  return termos;
}

vector<Definicao> CtrlServicoVocabulario::ConsultarDefinicao(const Termo &termo) {
  ComandoSqlConsultarDefinicao *comando;
  comando = new ComandoSqlConsultarDefinicao(termo);
  vector<Definicao> defs;
  try {
    comando->Executar();
    defs = comando->GetDefinicoes();
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
  }
  delete comando;
  return defs;
}

Resultado CtrlServicoVocabulario::CadastrarDesenvolvedor(const VocabularioControlado &voc, const Email &email) {
  Resultado resultado;
  ComandoSqlPesquisarUsuario *comando_pesquisar;
  ComandoSql *comando_att;
  try {
    comando_pesquisar = new ComandoSqlPesquisarUsuario(email);
    comando_pesquisar->Executar();
    Desenvolvedor dev = comando_pesquisar->GetDev();
    comando_att = new ComandoSqlAtualizar(dev, voc);
    comando_att->Executar(); 
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }
  resultado.SetResultado(Resultado::ksucesso_);
  delete comando_att;
  delete comando_pesquisar;
  return resultado;
}


Resultado CtrlServicoVocabulario::CadastrarAdministrador(const VocabularioControlado &voc, const Email &email) {
  Resultado resultado;
  ComandoSqlPesquisarUsuario *comando_pesquisar;
  ComandoSql *comando_att;
  try {
    comando_pesquisar = new ComandoSqlPesquisarUsuario(email);
    comando_pesquisar->Executar();
    Administrador adm = comando_pesquisar->GetAdm();
    comando_att = new ComandoSqlAtualizar(adm, voc);
    comando_att->Executar(); 
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }
  resultado.SetResultado(Resultado::ksucesso_);
  delete comando_att;
  delete comando_pesquisar;
  return resultado;
}

Resultado CtrlServicoVocabulario::CriarVocabulario(VocabularioControlado &voc, const Nome &nome, 
                  const Idioma &idioma, const Data &data, const Email &email) {
  Resultado resultado;
  try {
    voc = VocabularioControlado(nome, idioma, data);
  } catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  } 
  string tipo_conta;
  ComandoSqlTipoConta *comando_tc = new ComandoSqlTipoConta(email);
  try {
    comando_tc->Executar();
    tipo_conta = comando_tc->RecuperaConta();
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }
  delete comando_tc;
  ComandoSqlPesquisarUsuario *comando;
  ComandoSqlCadastrar *comando_k;
  try {
    comando = new ComandoSqlPesquisarUsuario(email);
    comando->Executar();
    Administrador adm = comando->GetAdm();
    comando_k = new ComandoSqlCadastrar(voc, adm);
    comando_k->Executar();
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }

  resultado.SetResultado(Resultado::ksucesso_);
  delete comando;
  delete comando_k;
  return resultado;
}

Resultado CtrlServicoVocabulario::EditarVocabulario(VocabularioControlado &voc, 
                    const Nome &nome, const Idioma &idioma, const Data &data) {
  Resultado resultado;
  try {
    voc = VocabularioControlado(nome, idioma, data);
  } catch (exception &e) {
    cout << "\n\t" << e.what() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }
  ComandoSqlAtualizar *comando;
  try {
    comando = new ComandoSqlAtualizar(voc);
    comando->Executar(); 
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    return resultado;
  }
  
  resultado.SetResultado(Resultado::ksucesso_);
  delete comando;
  return resultado;
}

Resultado CtrlServicoVocabulario::ExcluirVocabulario(const VocabularioControlado &voc) {
  Resultado resultado;
  ComandoSqlRemover *comando;
  try {
    comando = new ComandoSqlRemover(voc);
    comando->Executar();
  } catch (ErroDePersistencia &e) {
    cout << "\n\t" << e.GetMsg() << "\n";
    resultado.SetResultado(Resultado::kfalha_);
    delete comando;
    return resultado;
  }
  delete comando;
  resultado.SetResultado(Resultado::ksucesso_);
  return resultado;
}