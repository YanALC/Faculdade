#include "arquivo.h"

Arquivo::Arquivo()
{}

bool Arquivo::gravar(Lista<Contato> *agenda, string &pessoa)
{
    try{
        ofstream agendas;
        agendas.open("Agendas.txt",fstream::out);
        agendas<<pessoa<<endl;
        agendas.close();
        ofstream nomes;
        nomes.open(pessoa+"Contatos.txt", fstream::out);
        ofstream telefones;
        telefones.open(pessoa+"Telefones.txt", fstream::out);
        ofstream emails;
        emails.open(pessoa+"Emails.txt", fstream::out);
        ofstream enderecos;
        enderecos.open(pessoa+"Enderecos.txt", fstream::out);
        if(nomes.is_open()&&telefones.is_open()&&emails.is_open()&&enderecos.is_open()){
            Contato *contatoAux = new Contato;
            while(!agenda->listaVazia()){
                contatoAux = agenda->removerInicio();
                nomes<<contatoAux->getNome()<<";";
                Telefone *telefoneAux = new Telefone;
                while(!contatoAux->getTelefones()->listaVazia()){
                    telefoneAux = contatoAux->getTelefones()->removerInicio();
                    telefones<<telefoneAux->getDDD()<<";"
                           <<telefoneAux->getTelefone()<<";"
                          <<telefoneAux->getTipo()<<";";
                }telefones<<endl;
                telefoneAux=NULL;
                delete telefoneAux;
                Email *emailAux = new Email;
                while(!contatoAux->getEmails()->listaVazia()){
                    emailAux = contatoAux->getEmails()->removerInicio();
                    emails<<emailAux->getEmailID()<<";"
                        <<emailAux->getEmailDominio()<<";";
                }emails<<endl;
                emailAux=NULL;
                delete emailAux;
                Endereco *enderecoAux = new Endereco;
                while(!contatoAux->getEnderecos()->listaVazia()){
                    enderecoAux = contatoAux->getEnderecos()->removerInicio();
                    enderecos<<enderecoAux->getLogradouro()<<";"
                           <<enderecoAux->getNumero()<<";"
                          <<enderecoAux->getCep()<<";"
                         <<enderecoAux->getTipo()<<";";
                }enderecos<<endl;
                enderecoAux=NULL;
                delete enderecoAux;
            }
            nomes.close();
            telefones.close();
            emails.close();
            enderecos.close();
            return true;
        }else throw QString("Erro na criação do arquivo!");
    }
    catch(QString &erro){
        throw erro;
    }
    catch(bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

bool Arquivo::agendaExiste(string &pessoa)
{
    try{
        string aux;
        ifstream agendas;
        agendas.open("Agendas.txt",ios::in);
        if(agendas.is_open()){
            getline(agendas,aux);
            if(aux==pessoa) return true;
            while(!agendas.eof()){
                if(aux==pessoa) return true;
                getline(agendas,aux);
            }return false;
        }else return false;
    }
    catch(QString &erro){
        throw erro;
    }
    catch(bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

Lista<Contato> *Arquivo::lerArquivos(string &pessoa)
{
    try{
        ifstream nomes;
        nomes.open(pessoa+"Contatos.txt", ios::in);
        if(nomes.is_open()){
            Lista<Contato> *agenda = new Lista<Contato>;
            int i=0;
            string aux;
            getline(nomes,aux);
            QStringList entrada = QString::fromStdString(aux).split(";",QString::SkipEmptyParts);
            while(entrada.size()!=0){
                Contato *contatoAux = new Contato;
                contatoAux->setNome((entrada.takeFirst()).toStdString());
                string aux2;
                QStringList entrada2;
                ifstream telefones;
                telefones.open(pessoa+"Telefones.txt", ios::in);
                if(telefones.is_open()){
                    for(int i2=0;getline(telefones,aux2) && i2<i;i2++);
                    entrada2 = QString::fromStdString(aux2).split(";",QString::SkipEmptyParts);
                    while(entrada2.size()!=0){
                        Telefone *telefoneAux = new Telefone;
                        telefoneAux->setDDD(entrada2.takeFirst().toInt());
                        telefoneAux->setTelefone(entrada2.takeFirst().toLong());
                        telefoneAux->setTipo(entrada2.takeFirst().toInt());
                        contatoAux->setTelefone(telefoneAux);
                        telefoneAux=NULL;
                        delete telefoneAux;
                    }
                    telefones.close();
                }else throw QString("Erro na abertura do arquivo!");
                ifstream emails;
                emails.open(pessoa+"Emails.txt", ios::in);
                if(emails.is_open()){
                    for(int i2=0;getline(emails,aux2) && i2<i;i2++);
                    entrada2 = QString::fromStdString(aux2).split(";",QString::SkipEmptyParts);
                    while(entrada2.size()!=0){
                        Email *emailAux = new Email;
                        emailAux->setEmailID(entrada2.takeFirst().toStdString());
                        emailAux->setEmailDominio(entrada2.takeFirst().toStdString());
                        contatoAux->setEmail(emailAux);
                        emailAux=NULL;
                        delete emailAux;
                    }
                    emails.close();
                }else throw QString("Erro na abertura do arquivo!");
                ifstream enderecos;
                enderecos.open(pessoa+"Enderecos.txt", ios::in);
                if(enderecos.is_open()){
                    for(int i2=0;getline(enderecos,aux2) && i2<i;i2++);
                    entrada2 = QString::fromStdString(aux2).split(";",QString::SkipEmptyParts);
                    while(entrada2.size()!=0){
                        Endereco *enderecoAux = new Endereco;
                        enderecoAux->setLogradouro(entrada2.takeFirst().toStdString());
                        enderecoAux->setNumero(entrada2.takeFirst().toInt());
                        enderecoAux->setCep(entrada2.takeFirst().toLong());
                        enderecoAux->setTipo(entrada2.takeFirst().toInt());
                        contatoAux->setEndereco(enderecoAux);
                        enderecoAux=NULL;
                        delete enderecoAux;
                    }
                    enderecos.close();
                }else throw QString("Erro na abertura do arquivo!");
                agenda->inserirOrdenado(contatoAux);
                contatoAux=NULL;
                delete contatoAux;
                i++;
            }
            nomes.close();
            return agenda;
        }else throw QString("Erro na abertura do arquivo!");
    }
    catch(QString &erro){
        throw erro;
    }
    catch(bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

void Arquivo::listarAgendasUI(QListWidget *aux)
{
    try{
        string pessoa;
        fstream agendas;
        agendas.open("Agendas.txt",ios::in);
        if(agendas.is_open()){
            getline(agendas,pessoa);
            while(!agendas.eof()){
                aux->addItem(QString::fromStdString(pessoa));
                getline(agendas,pessoa);
            }
        }else throw QString("Erro na abertura do arquivo!");//Não há agendas
    }
    catch(QString &erro){
        throw erro;
    }
    catch(bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}
