#ifndef MENUAFND_H
#define MENUAFND_H
#include<QString>
#include<AFND.h>



class MenuAFND
{
private:
    mumu::AFND<QString> objAutomato;
    QString nomeArqNoDisco;
    mumu::Estado<QString>retornaEstadoPorNome(QString nome,QList<mumu::Estado<QString>>*listaDeEstado );
public:
    MenuAFND();
    MenuAFND(QString nomeArqNoDisco)
        :nomeArqNoDisco(nomeArqNoDisco){}

    void obtenhaAutomatoComArquivo();
    void mostrarAutomato(mumu::AFD<QString> *aut);
    void menu();





};

#endif // MENUAFND_H
