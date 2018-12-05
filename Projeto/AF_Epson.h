#ifndef AF_EPSON_H
#define AF_EPSON_H
#include<AFD.h>

#include<QString>

namespace mumu
{
template <class T>
class AF_Epson : public AFD<T>
{
private:
    T idVazio;
    bool ehDebug = true;
    void convertaDeAF_EpsnoParaAFD_Recursivo(AFD<T>*automato, Estado<T> est);
    void imprimir(QString msg){if(ehDebug)std::cout << msg.toStdString() << std::endl;}
public:
    AF_Epson(T idVazio)
        :AFD<T>(),
          idVazio(idVazio){}
    AF_Epson():AFD<T>() {}
    inline void setIdVazio(T idVazio) {this->idVazio = idVazio;}
    inline T getIdVazio(){return this->idVazio;}
    AFD<T>*convertaDeAF_EpsnoParaAFD();



};

template<class T>
void AF_Epson<T>::convertaDeAF_EpsnoParaAFD_Recursivo(AFD<T>*automato,Estado<T> estado)
{

    imprimir("****LACO RECURSIVO ****");
    //função anonima de nome de estado
    auto definirNomeEstado = [](QStringList list)
    {
        QString saida = "";
        for(int i = 0;i < list.count(); i++)
        {
            saida += ( i != 0 ? ";" + list[i] : list[i]);
        }
        return saida;
    };

    QStringList listaAlcanceEpson;


    imprimir("BFS do estado " + estado.getNome());

    foreach(QString item, estado.getNome().split(';'))
    {
        this->getObjArestaEstado().bfs_custumer(Estado<T>(item),idVazio,&listaAlcanceEpson);
    }

    listaAlcanceEpson.sort();

    imprimir("O Resultado o BFS foi " + definirNomeEstado(listaAlcanceEpson));

    //Roda o alfabeto para procurar novos estados
    foreach(QString itemDoAlfabeto, *this->getListaDeAlfabeto())
    {
        if(itemDoAlfabeto != idVazio)
        {
            QStringList listFunProgEst;

            //Roda os estados alcançados de acordo com a letra para a geração de novos estados
            for(int i = 0; i < listaAlcanceEpson.count(); ++i)
            {
                //Executa a função programa e encontra todos alcançaveis com a letra
                QList<Estado<T>> listFunProg = this->getObjArestaEstado().consulteListFuncaoProgramaEstendida(Estado<T>(listaAlcanceEpson[i]),itemDoAlfabeto);

                //Add os alcançaveis
                foreach(Estado<T>itemEstado,listFunProg)
                {
                    if(!listFunProgEst.contains(itemEstado.getNome()))
                    {
                        imprimir("Com a letra (" + itemDoAlfabeto + ") aparti de " + estado.getNome() + " foi encontrado o estado " + itemEstado.getNome());
                        listFunProgEst.push_back(itemEstado.getNome());
                    }//fim if
                }//fim foreach
            }//fim for

            listFunProgEst.sort();

            QString nomeEstado = definirNomeEstado(listFunProgEst);
            //define nome do estado
            if(nomeEstado != "")
            {
                Estado<T>est;
                est.setNome(nomeEstado);

                imprimir("Com a letra (" + itemDoAlfabeto + ") finalmente temos o estado " + nomeEstado);

                bool ehEstadoNovo = false;
                if(!automato->getObjArestaEstado().ehEstadoRepetido(est))
                {
                    //passa o estado para o automato
                    automato->getObjArestaEstado().incluirEstado(est);
                    ehEstadoNovo = true;
                }

                if(ehEstadoNovo)
                    imprimir("O Estado acima e novo");
                else
                    imprimir("O Estado acima não e novo");


                //liga o estado com o novo estado
                if(ehEstadoNovo)
                {
                    imprimir("chamada a busca recursiva com o estado " + est.getNome());

                    automato->getObjArestaEstado().ligarEstado(estado,est,itemDoAlfabeto);

                    imprimir("Ligando o estado " + estado.getNome() + " com o estado  " + est.getNome() + " com a letra " + itemDoAlfabeto);

                    //faz a buscar com o estado encontrado recursivamente
                    convertaDeAF_EpsnoParaAFD_Recursivo(automato,est);
                }
                else
                {
                    imprimir("Liga o estado " + estado.getNome() + " com ele mesmo, (" + est.getNome() + " ) " + " com a letra " + "(" + itemDoAlfabeto + ")");//****
                    automato->getObjArestaEstado().ligarEstado(estado,est,itemDoAlfabeto);
                }
            }
            else
            {
                imprimir("O Nome do novo estado apos percorrer a funcao programa esta vazio, devido a isso o mesmo foi ignorado!");
            }

        }//fim do if
    }//fim dfor
}




template<class T>
AFD<T> *AF_Epson<T>::convertaDeAF_EpsnoParaAFD()
{
    imprimir("Definindo estado inicial");

    this->definirEstadoInicial();
    //obetem o estado inicial
    Estado<T> estado = this->getObjArestaEstado().consulteEstadoPorNome(this->getNomeEstadoInicial());
    AFD<T>*automato = new AFD<T>();

    //alfabeto
    for(int i = 0; i < this->getListaDeAlfabeto()->count(); i++)
    {
        if(this->getListaDeAlfabeto()->at(i) != idVazio)
        {
            automato->getListaDeAlfabeto()->push_back(this->getListaDeAlfabeto()->at(i));
        }
    }

    //função anonima de nome de estado
    auto definirNomeEstado = [](QStringList list)
    {
        QString saida = "";
        for(int i = 0;i < list.count(); i++)
        {
            saida += ( i != 0 ? ";" + list[i] : list[i]);
        }
        return saida;
    };

    //inclui o primeiro estado S0
    automato->getObjArestaEstado().incluirEstado(estado);

    imprimir("incluido o estado " + estado.getNome() + " Como S0");

    QStringList listaAlcanceEpson;


    this->getObjArestaEstado().bfs_custumer(estado,idVazio,&listaAlcanceEpson);
    listaAlcanceEpson.sort();
    imprimir("BFS do estado " + estado.getNome());

    imprimir("O Resultado o BFS foi " + definirNomeEstado(listaAlcanceEpson));

    //Roda o alfabeto para procurar novos estados
    foreach(QString itemDoAlfabeto, *this->getListaDeAlfabeto())
    {
        if(itemDoAlfabeto != idVazio)
        {
            QStringList listFunProgEst;

            //Roda os estados alcançados de acordo com a letra para a geração de novos estados
            for(int i = 0; i < listaAlcanceEpson.count(); ++i)
            {
                //Executa a função programa e encontra todos alcançaveis com a letra
                QList<Estado<T>> listFunProg = this->getObjArestaEstado().consulteListFuncaoProgramaEstendida(Estado<T>(listaAlcanceEpson[i]),itemDoAlfabeto);

                //Add os alcançaveis
                foreach(Estado<T>itemEstado,listFunProg)
                {
                    if(!listFunProgEst.contains(itemEstado.getNome()))
                    {
                        imprimir("Com a letra (" + itemDoAlfabeto + ") aparti de " + estado.getNome() + " foi encontrado o estado " + itemEstado.getNome());
                        listFunProgEst.push_back(itemEstado.getNome());
                    }//fim if
                }//fim foreach
            }//fim for

            listFunProgEst.sort();

            //define nome do estado
            QString nomeEstado = definirNomeEstado(listFunProgEst);
            Estado<T>est;
            est.setNome(nomeEstado);

            imprimir("Com a letra (" + itemDoAlfabeto + ") finalmente temos o estado " + nomeEstado);

            bool ehEstadoNovo = false;
            if(!automato->getObjArestaEstado().ehEstadoRepetido(est))
            {
                //passa o estado para o automato
                automato->getObjArestaEstado().incluirEstado(est);
                ehEstadoNovo = true;
            }

            if(ehEstadoNovo)
                imprimir("O Estado acima e novo");
            else
                imprimir("O Estado acima não e novo");

            imprimir("Ligando o estado " + estado.getNome() + " com o estado  " + est.getNome() + " com a letra " + itemDoAlfabeto);

            //liga o estado com o novo estado
            if(ehEstadoNovo)
            {
                imprimir("Ligando o estado " + estado.getNome() + " com o estado  " + est.getNome() + " com a letra " + itemDoAlfabeto);
                automato->getObjArestaEstado().ligarEstado(estado,est,itemDoAlfabeto);


                 imprimir("chamada a busca recursiva com o estado " + est.getNome());

                //faz a buscar com o estado encontrado recursivamente
                convertaDeAF_EpsnoParaAFD_Recursivo(automato,est);
            }
            else
            {
                imprimir("Liga o estado " + estado.getNome() + " com ele mesmo, (" + est.getNome() + " ) " + " com a letra " + "(" + itemDoAlfabeto + ")");//****
                automato->getObjArestaEstado().ligarEstado(estado,est,itemDoAlfabeto);
            }
        }
    }

    return automato;
}


























}

#endif // AF_EPSON_H

