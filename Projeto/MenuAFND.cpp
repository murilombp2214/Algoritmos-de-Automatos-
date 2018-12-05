#include "MenuAFND.h"
#include<iostream>
#include<fstream>


MenuAFND::MenuAFND()
{

}

void MenuAFND::obtenhaAutomatoComArquivo()
{

    QT_TRY
    {
        std::ifstream arquivo;
        arquivo.open(this->nomeArqNoDisco.toStdString().c_str());
        std::string linha;
        if(!arquivo)
            throw QString("Erro ao abrir o arquivo\n");
        int cont = 0;
        QStringList listaNomesAutomatos;
        QStringList listaAlfabeto;
        QStringList listaAssociacoes;
        QStringList listaDeEstadosFinIni;
        while(std::getline(arquivo,linha))
        {
            if(linha[0] != '-' && linha[1] != '-')//senão for comentario do arquivo
            {
                auto linhaArquivo = [](std::string line){return QString::fromStdString(line).split(';');};
                if(cont == 0)
                {
                    listaNomesAutomatos = linhaArquivo(linha);
                }
                else
                {
                    if(cont == 1)
                    {
                        listaAlfabeto =  linhaArquivo(linha);
                    }
                    else
                    {
                        if(cont == 2)
                        {
                            listaAssociacoes =  linhaArquivo(linha);
                        }
                        else
                        {
                            if(cont == 3)
                            {
                                listaDeEstadosFinIni  =  linhaArquivo(linha);
                            }
                            else
                            {
                                arquivo.close();
                            }
                        }

                    }
                }
            }
            cont++;
        }



        arquivo.close();

        //alfabeto
        foreach(QString item,listaAlfabeto)
        {
            objAutomato.adicionarLetraDoAlfabeto(item);

        }

        QList<mumu::Estado<QString>>*listaDeEstado = new QList<mumu::Estado<QString>>();
        //estados
        foreach(QString item,listaNomesAutomatos)
        {

            mumu::Estado<QString>estado;
            estado.setNome(item);

            if(listaDeEstadosFinIni.contains(item))
            {

                //marcandoo o estado
                for(int k = 0; k < listaDeEstadosFinIni.count(); k++)
                {
                    if(listaDeEstadosFinIni.at(k) == item)
                    {
                        if(not estado.getEhEstadoFinal())
                            estado.setEhEstadoFinal(listaDeEstadosFinIni.at(1 + k) == "EF");
                        if(not estado.getEhEstadoInicial())
                            estado.setEhEstadoInicial(listaDeEstadosFinIni.at(1 + k) == "EI");

                    }
                }

            }
            listaDeEstado->push_back(estado);
        }


        //associação fisica
        for(int i = 0; i < listaDeEstado->count();i++)
        {
            mumu::Estado<QString> estado = listaDeEstado->at(i);
            objAutomato.getObjArestaEstado().incluirEstado(estado);
        }


        //Ligando estados
        int i = 0;
        QString q0;
        QString q1;
        QString letra;
        foreach(QString item,listaAssociacoes)
        {

            switch (i)
            {
            case 0:
                q0 = item;
                break;
            case 1:
                letra = item;
                break;
            case 2:
                q1 = item;
                break;
            default:
                break;

            }


            if(i == 2)
            {
                i = 0;
                mumu::Estado<QString>e1 = retornaEstadoPorNome(q0,listaDeEstado);
                mumu::Estado<QString>e2 = retornaEstadoPorNome(q1,listaDeEstado);

                //                std::cout << e1.getNome().toStdString()  <<std::endl;
                //                std::cout << e2.getNome().toStdString()  <<std::endl;
                //                std::cout << letra.toStdString() <<std::endl;

                objAutomato.getObjArestaEstado().ligarEstado(e1,e2,letra);
            }
            else
            {
                i = i + 1;
            }
        }


        objAutomato.montarAutomato();
    }
    QT_CATCH(QString& erro)
    {
        std::cerr << erro.toStdString();
    }
    QT_CATCH(...)
    {
        std::cerr << "Um ou mais erros\n";
    }
}

mumu::Estado<QString> MenuAFND::retornaEstadoPorNome(QString nome,QList<mumu::Estado<QString>>*listaDeEstado )
{

    foreach(mumu::Estado<QString>item,*listaDeEstado)
    {
        if(item.getNome() == nome)
        {
            return item;
        }
    }

    throw QString("Erro com a mensagem '" + nome + "não foi encontrado '\n - MenuAFND.retornaEstadoPorNome");
}

void MenuAFND:: mostrarAutomato(mumu::AFD<QString> *aut)
{
    QMapIterator<QString,QList<mumu::Aresta<QString>>> colecao(aut->getMapObjAutomato());
    while(colecao.hasNext())
    {
        colecao.next();

        std::cout << "(" + colecao.key().toStdString() + ")"<< " -> ";
        for(int i = 0; i < colecao.value().count(); i++)
        {
            std::cout << colecao.value().at(i).getValor().toStdString() << " -> " << colecao.value().at(i).getQ1().getNome().toStdString() << " - >";
        }


        if(aut->getObjArestaEstado().consulteEstadoPorNome(colecao.key()).getEhEstadoInicial())
        {
            std::cout << "[EI]";
        }

        if(aut->getObjArestaEstado().consulteEstadoPorNome(colecao.key()).getEhEstadoFinal())
        {
            std::cout << "[EF]";
        }

        std::cout << "\n";
    }
}


void MenuAFND::menu()
{
    bool ehFimProg = false;

    while(not ehFimProg)
    {
        std::string resposta;
        std::cout << "0 - Voltar\n"
                     "1 - Converter AFND->AFD\n"
                     "2 - Ver Automato\n";
        std::cin >> (static_cast<void>(resposta = ""),resposta);
        switch(resposta[0])
        {
        case '0':
            ehFimProg = true;
            break;
        case '1':
        try
        {
            auto aux = this->objAutomato.convertaDeAFNDParaAFD();
            aux->montarAutomato();
            this->mostrarAutomato(aux);

        }
        catch (QString &erro)
        {
            std::cerr << erro.toStdString() + "\n";
        }
        catch (...)
        {
            std::cerr << "Um ou mais erros\n";
        }
            break;
        case '2':
            this->mostrarAutomato(&this->objAutomato);
            break;

        }
    }


}
