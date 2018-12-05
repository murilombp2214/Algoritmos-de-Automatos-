#ifndef MENUAF_EPSON_H
#define MENUAF_EPSON_H
#include<QString>
#include<QStringList>
#include<AF_Epson.h>

class MenuAF_Epson
{
private:
    QString nomeArqNoDisco;
    mumu::AF_Epson<QString> objAutomato;
    mumu::Estado<QString>retornaEstadoPorNome(QString nome,QList<mumu::Estado<QString>>*listaDeEstado );
public:
    MenuAF_Epson(){}
    MenuAF_Epson(QString nomeArqNoDisco):nomeArqNoDisco(nomeArqNoDisco){}

    void obtenhaAutomatoComArquivo();
    void mostrarAutomato(mumu::AFD<QString> *aut);
    void menu();
};

#endif // MENUAF_EPSON_H
