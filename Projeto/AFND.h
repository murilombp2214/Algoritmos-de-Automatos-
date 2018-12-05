#ifndef AFND_H
#define AFND_H

#include<ArestaEstado.h>
#include<AFD.h>
#include<Aresta.h>
#include<Estado.h>

namespace mumu{
template<class  T>
class AFND : public AFD<T>
{
private:
    void convertaDeAFNDParaAFD_Recursivo(AFD<T> *automato,QMap<QString,QMap<QString,QList<QString>>> mapNovoAutomato
                                         , bool estadoInicial);
    bool debugAFND = true;
public:
    AFND():AFD<T>(){}
    AFD<T>*convertaDeAFNDParaAFD();
};

template<class T>
AFD<T> *AFND<T>::convertaDeAFNDParaAFD()
{
    QMapIterator<QString,QList<mumu::Aresta<QString>>> colecao(this->getMapObjAutomato());
    QMap<QString,QMap<QString,QList<QString>>> mapNovoAutomato;
    this->definirEstadoInicial();


    //Monta um mapa da seguinte maneira
    ///key = nome do estado principal
    ///value = QMap {key  = "LETRA","ESTADOS"}
    while(colecao.hasNext())
    {
        colecao.next();
        if(this->getNomeEstadoInicial() == colecao.key())
        {
            for(int i = 0; i < colecao.value().count(); i++)
            {
                //estado
                QString key = colecao.key();

                //letra
                QString key_2 = colecao.value().at(i).getValor();

                //estados que leva a letra
                QString value = colecao.value().at(i).getQ1().getNome();

                mapNovoAutomato[key][key_2].push_back(value);
            }
        }
    }

    QMapIterator<QString,QMap<QString,QList<QString>>>col(mapNovoAutomato);

    if(debugAFND)
        std::cout << "CHEGOU\n";
    while (debugAFND && col.hasNext())
    {
        std::cout << "entrou\n";
        col.next();
        QMapIterator<QString,QList<QString>>col2(col.value());

        std::cout << "\nESTADO = " + col.key().toStdString();
        while(col2.hasNext())
        {
            col2.next();
            std::cout << "  LETRA = " + col2.key().toStdString();
            foreach(QString item,col2.value())
            {
                std::cout << " " + item.toStdString()  + " - ";
            }
            std::cout << std::endl;

        }
    }
    AFD<T> *automato = new AFD<T>();

    for(int i = 0; i < this->getListaDeAlfabeto()->count(); i++)
    {
        automato->adicionarLetraDoAlfabeto(this->getListaDeAlfabeto()->at(i));
    }

    convertaDeAFNDParaAFD_Recursivo(automato,mapNovoAutomato,true);
    return automato;
}






template<class T>
void AFND<T>::convertaDeAFNDParaAFD_Recursivo(AFD<T> *automato, QMap<QString, QMap<QString, QList<QString> > > mapNovoAutomato, bool estadoInicial)
{
    if(debugAFND)
        std::cout << "Entrou em convertaDeAFNDParaAFD_Recursivo \n";

    //Proximo mapa
    QList<QMap<QString, QMap<QString, QList<QString> >>> listMapsProximo;

    //Funções anonimas
    auto conjuntoDeEstado = [](QList<QString>list)
    {
        list.sort(Qt::CaseSensitive);
        QString saida("");
        foreach(QString item,list)
            saida = saida == "" ? item : saida + ";" + item;
        return saida;
    };


    //Auxiliares
    QMapIterator<QString,QMap<QString,QList<QString>>>colecaoNovoAutomato(mapNovoAutomato);

    bool existeProxomoMapa = false;
    while(colecaoNovoAutomato.hasNext())
    {
        colecaoNovoAutomato.next();

        Estado<T>est;
        est.setNome(colecaoNovoAutomato.key());
        est.setEhEstadoInicial(estadoInicial);

        //verifica se o inicial também é final
        if(estadoInicial)
        {
            QStringList listAux = colecaoNovoAutomato.key().split(';');
            for(int i = 0; i < listAux.count(); i++)
            {
                if(this->getObjArestaEstado().consulteEstadoPorNome(listAux.at(i)).getEhEstadoFinal())
                {
                    est.setEhEstadoFinal(true);
                    i = listAux.count()+2;
                }
            }
        }


        if(debugAFND)
            std::cout << "Estado principal = " + est.getNome().toStdString() + "\n";

        //Se o estado não existir no automato, então o mesmo é criado
        if(not automato->getObjArestaEstado().ehEstadoRepetido(est))
        {
            if(debugAFND)
                std::cout << "Estado principal não existia no automato\n";
            automato->getObjArestaEstado().incluirEstado(est);
        }

        //Cria o iterador da coleção do VALUE principal
        QMapIterator<QString,QList<QString>>colecaoMapList(colecaoNovoAutomato.value());

        while(colecaoMapList.hasNext())
        {
            colecaoMapList.next();

            QString letraAlfabeto = colecaoMapList.key();
            QString nomeNovoEstado = conjuntoDeEstado(colecaoMapList.value());

            if(debugAFND)
            {
                std::cout << "Letra do alfabeto = " + letraAlfabeto.toStdString() + "\n";

                std::cout << "Nome do novo estado = " + nomeNovoEstado.toStdString() + "\n";
            }


            //Cria um estado com o nome do conjunto de estado lista
            Estado<T>estadoNovo;
            estadoNovo.setNome(nomeNovoEstado);

            //Se o estado não existir no automato, então o mesmo é criado
            if(not automato->getObjArestaEstado().ehEstadoRepetido(estadoNovo))
            {
                QStringList listAux = estadoNovo.getNome().split(';');
                for(int i = 0; i < listAux.count(); i++)
                {
                    if(this->getObjArestaEstado().consulteEstadoPorNome(listAux.at(i)).getEhEstadoFinal())
                    {
                        estadoNovo.setEhEstadoFinal(true);
                        i = listAux.count()+2;
                    }
                }


                automato->getObjArestaEstado().incluirEstado(estadoNovo);
                existeProxomoMapa = true;
                if(debugAFND)
                    std::cout << "estado = " + nomeNovoEstado.toStdString() + "não existia no automato \n";
            }

            automato->getObjArestaEstado().ligarEstado(est,estadoNovo,letraAlfabeto);

            if(debugAFND)
            {
                std::cout << "Estado " + est.getNome().toStdString() + " -> "
                             + estadoNovo.getNome().toStdString()
                             + " com a letra " + letraAlfabeto.toStdString() + "\n";
            }

            ///Criandos os novos mapas
            ///  key = nomeNovoEstado
            ///     key2 = letraAlfabeto
            ///         value =  listEstadoNovoEstado


            //gera o mapa aparti do alfabeto
            for(int merda = 0; merda < automato->getListaDeAlfabeto()->count(); merda++)
            {
                letraAlfabeto = automato->getListaDeAlfabeto()->at(merda);
                QMap<QString, QMap<QString, QList<QString> >>mapSaida;

                QStringList listEstado = nomeNovoEstado.split(';');
                QList<QString>listEstadoNovoEstado;

                if(debugAFND)
                    std::cout << "\n\n Iniciando Varredura de estados\n";

                //varre os estados que apareceram e cria o novo mapa
                for(int i = 0; i < listEstado.count();i++)
                {
                    if(debugAFND)
                        std::cout <<"Estado "<< i + 1 << " :  = " + listEstado[i].toStdString() + "\n";

                    //consulta um estado para ver onde ele leva
                    QList<Estado<QString>>listEst =
                            this->getObjArestaEstado()
                            .consulteListFuncaoProgramaEstendida(listEstado[i],letraAlfabeto);


                    //preenche a lista do novo mapa
                    for(int j = 0; j < listEst.count(); j++)
                    {
                        if(debugAFND)
                            std::cout << "Encontrado o estado " + listEst.at(j).getNome().toStdString() + "\n";
                        if(not listEstadoNovoEstado.contains(listEst.at(j).getNome()))
                        {

                            if(debugAFND)
                                std::cout << "O estado " + listEst.at(j).getNome().toStdString() + " Foi inserido na lista  \n";
                            listEstadoNovoEstado.push_back(listEst.at(j).getNome());
                        }
                    }
                }

                if(automato->getObjArestaEstado()
                        .consulteListFuncaoProgramaEstendida(Estado<T>(nomeNovoEstado),letraAlfabeto)
                        .count() == 0 )
                {
                    listEstadoNovoEstado.sort();
                    mapSaida[nomeNovoEstado][letraAlfabeto] = listEstadoNovoEstado;
                    listMapsProximo.push_back(mapSaida);
                }

            }

        }
    }


    //caso ache algum novo mapa então recursivamente cria novos estados e os liga pelo alfabeto
    if(existeProxomoMapa)
    {
        for(int i = 0; i < listMapsProximo.count(); i++)
        {
            convertaDeAFNDParaAFD_Recursivo(automato,listMapsProximo[i],false);
        }
    }
}

}

#endif // AFND_H
