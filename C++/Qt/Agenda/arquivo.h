#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "agendaui.h"
#include <fstream>
#include <QListWidget>

class Arquivo
{
public:
    Arquivo();
    static bool gravar(Lista<Contato> *agenda, string &pessoa);
    static bool agendaExiste(string &pessoa);
    static Lista<Contato> *lerArquivos(string &pessoa);
    static void listarAgendasUI(QListWidget *aux);
};

#endif // ARQUIVO_H
