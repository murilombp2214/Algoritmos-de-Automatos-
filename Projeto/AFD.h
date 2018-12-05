#ifndef AFD_H
#define AFD_H

#include<ArestaEstado.h>


#include<QString>
#include<QList>
#include<QMap>

#include<tuple>

namespace mumu
{

template <class T>
class AFD
{
private:

    ///<summary>
    /// Alfabeto  do Automato
    /// <summary/>
    QList<T> *listaDeAlfabeto;

    ///<summary>
    /// Objeto que guarda todas arestas e estados do automato
    /// <summary/>
    ArestaEstado<T> objArestaEstado;

    ///<summary>
    /// Estado Inicial do automato
    /// <summary/>
    Estado<T> objEstadoInicial;

    ///<summary>
    ///     KEY = Nome do Estado
    ///     VALUE = Lista de aresta que sai do estado
    /// <summary/>
    QMap<QString, QList<Aresta<T>> > mapObjAutomato;









public:
    AFD<T>()
    {
        this->listaDeAlfabeto = new QList<T>();
        this->listaDeAlfabeto->clear();
    }
    ~AFD<T>() {delete listaDeAlfabeto;}

    int definirEstadoInicial();

    inline QList<T> *getListaDeAlfabeto() const{return this->listaDeAlfabeto;}

    ArestaEstado<T> getObjArestaEstado();

    inline QString getNomeEstadoInicial(){return this->objEstadoInicial.getNome();}

    QString desenharAutomato();

    void adicionarLetraDoAlfabeto(T letra);

    void montarAutomato();

    bool submeterPalavra(QString palavra);

    bool ehSensoEstrito();

    bool dsf(bool *visitados, QString q0);

    AFD<T> *mininmizar();



    inline QMap<T, QList<Aresta<T>>> getMapObjAutomato() const{return this->mapObjAutomato;}
};


template <class T>
ArestaEstado<T> AFD<T>::getObjArestaEstado()
{
    if(this->listaDeAlfabeto->count() == 0)
        throw QString("Erro com a mensagem 'Alfabeto ainda não foi criado'\n  AFD.getObjArestaEstado 1");
    return objArestaEstado;
}

template <class T>
QString AFD<T>::desenharAutomato()
{
    QMap<QString,QString> mapDeAutomatos;
    QString saida = "";

    bool erro = true;
    //pega o nome dos estados como chave e como inicio do desenho
    for(int i  = 0; i < this->objArestaEstado.getListaDeEstado()->count();++i)
    {
        Estado<T> aux = objArestaEstado.getListaDeEstado()->at(i);
        mapDeAutomatos.insert(aux.getNome(),aux.getNome());
        erro = false;
    }

    if(erro)
        throw  QString("Não foi possivel gerar as chaves para o automato! 1 - AFD.desenharAutomato");
    erro = true;

    //pega os valores das arestas de acordo com o estado e monta tipo uma lista de adjcencia
    for(int i = 0; i < this->objArestaEstado.getListaDeAresta()->count(); ++i)
    {
        mapDeAutomatos[(this->objArestaEstado.getListaDeAresta()->at(i)).getQ0().getNome()]
                += "--"  +  (this->objArestaEstado.getListaDeAresta()->at(i)).getValor()
                +  "-> " + (this->objArestaEstado.getListaDeAresta()->at(i)).getQ1().getNome();
        erro = false;


    }

    if(erro)
        throw  QString("Não foi possivel pegar os valores das arestas para o automato! 2 - AFD.desenharAutomato");

    erro = true;

    //desenha
    QMapIterator<QString, QString> item(mapDeAutomatos);
    while(item.hasNext())
    {
        item.next();
        saida += item.key() + item.value() + "\n";
        erro = false;
    }

    if(erro)
        throw  QString("Não foi possivel desenhar o automato! 3 - AFD.desenharAutomato");

    return saida;

}

template <class T>
void AFD<T>::adicionarLetraDoAlfabeto(T letra)
{
    if( listaDeAlfabeto->contains(letra) )
        throw QString("Erro com a mensagem 'A Letra  " + letra + " já pertence ao alfabeto' AFD.adicionarLetraDoAlfabeto 1");
    if( letra == "")
        throw QString("Erro com a mensagem 'A letra do alfabeto não pode ser vazia!' AFD.adicionarLetraDoAlfabeto 2");
    listaDeAlfabeto->push_back(letra);
}




template <class T>
int AFD<T>::definirEstadoInicial()
{
    for(int i = 0; i < this->objArestaEstado.getListaDeEstado()->count();++i)
    {
        if(this->objArestaEstado.getListaDeEstado()->at(i).getEhEstadoInicial())
        {
            this->objEstadoInicial.setNome(this->objArestaEstado.getListaDeEstado()->at(i).getNome());
            i =  this->objArestaEstado.getListaDeEstado()->count() + 75;
            return 1 ;
        }
    }

    throw QString("Automato sem estado inicial AFD.definirEstadoInicial 1");
}

template <class T>
void AFD<T>::montarAutomato()
{
    //define o estado inicial
    //std::cout << "es" << this->definirEstadoInicial();
    //cria o mapa de estado
    for(int i  = 0; i < this->objArestaEstado.getListaDeEstado()->count();++i)
    {
        QList<Aresta<T>>list;
        this->mapObjAutomato[this->objArestaEstado.getListaDeEstado()->at(i).getNome()] = list;
    }

    //distribui as arestas
    for(int i = 0; i < this->listaDeAlfabeto->count(); ++i)
    {
        for(int j = 0; j < this->objArestaEstado.getListaDeAresta()->count(); ++j)
        {
            //se o valor da aresta for a do alfabeto
            if(this->objArestaEstado.getListaDeAresta()->at(j).getValor() == this->listaDeAlfabeto->at(i))
            {
                //std::cout << this->objArestaEstado.getListaDeAresta()->at(j).getValor().toStdString() << std::endl;
                mapObjAutomato[this->objArestaEstado.getListaDeAresta()->at(j).getQ0().getNome()].push_back(this->objArestaEstado.getListaDeAresta()->at(j));

            }
        }
    }


}

template <class T>
bool AFD<T>::submeterPalavra(QString palavra)
{
    QString nomeEstadoAtual = this->objEstadoInicial.getNome();
    for(int i = 0; i < palavra.size(); i++)
    {
        QString aux((QChar(palavra[i])));

        int j;
        bool flagAchouLetra = true;

        for(j = 0; flagAchouLetra && j < this->mapObjAutomato[nomeEstadoAtual].count(); j++)
        {
            //encontrou uma ligação com a palavra
            if(this->mapObjAutomato[nomeEstadoAtual].at(j).getValor() == aux)
            {
                nomeEstadoAtual = this->mapObjAutomato[nomeEstadoAtual].at(j).getQ1().getNome();
                flagAchouLetra = false;
            }
        }

        if(flagAchouLetra)
        {
            return false;
        }
    }
    //se for estado final
    return mapObjAutomato[nomeEstadoAtual].at(0).getQ0().getEhEstadoFinal();
}

template <class T>
bool AFD<T>::ehSensoEstrito()
{
   bool visitados[this->getObjArestaEstado().getListaDeEstado()->count()];
   return this->dsf(visitados,"");

}

template <class T>
bool AFD<T>::dsf(bool *visitados, QString q0)
{
    if(q0.isEmpty())
    {

    }
}


template <class T>
class MatrizAFD
{
private:
    QString **matriz;
    int linha;
    int coluna;
    QList<T> *listaDeAlfabeto;
    ArestaEstado<T> objArestaEstado;
    const QString valorMarcacao = "X";
    QMap<QString, QList<std::tuple<Estado<T>,Estado<T>>>> mapListPorEst;

    void troca(int &a,int &b)
    {
        int aux = a;
        a = b;
        b = aux;
    }

    bool ehDebug = true;


public:
    MatrizAFD(int linha,int coluna, QList<T> *listaDeAlfabeto,ArestaEstado<T> &objArestaEstado)
    {
        matriz = new QString * [coluna];
        for(int i = 0; i < coluna; i++)
            matriz[i] = new QString[linha];
        this->listaDeAlfabeto = listaDeAlfabeto;
        this->objArestaEstado = objArestaEstado;
        this->coluna = coluna;
        this->linha = linha;
    }

    void preencher(QString valor)
    {
        for(int i = 0; i < this->coluna; i++)
            for(int j = 0; j < linha;j++)
                this->matriz[i][j] = "V";
        for(int i = 1; i < coluna;i++)
        {
            for(int j = 0; j < i; j++)
            {
                this->matriz[i][j] = valor;
            }
        }
    }

    void imprimir()
    {
        for(int i = 1; i < coluna;i++)
        {
            for(int j = 0; j < i; j++)
            {
                std::cout << matriz[i][j].toStdString() << " ";
            }
            std::cout << std::endl;
        }

    }

    void marcarPorEstado(QString q0,QString q1, QString valor = "")
    {
        valor = valor.isEmpty() ? this->valorMarcacao : valor;
        const Estado<T> estado1 = this->objArestaEstado.consulteEstadoPorNome(q0);
        const Estado<T> estado2 = this->objArestaEstado.consulteEstadoPorNome(q1);

        int posEstado1 = this->objArestaEstado.consultePosicaoEstado(estado1);
        int posEstado2 = this->objArestaEstado.consultePosicaoEstado(estado2);

        //        std::cout << estado1.getNome().toStdString() << " pos = " << posEstado1 << std::endl;

        //        std::cout << estado2.getNome().toStdString() << " pos = " << posEstado2 << std::endl;
        //sejam os mesmos estados
        if(posEstado1 == posEstado2)
            return;

        if(posEstado1 >= this->coluna || posEstado2 >= this->coluna)
            return;

        //marca os dois lados da matriz
        this->matriz[posEstado1][posEstado2] = valor;
        this->matriz[posEstado2][posEstado1] = valor;

    }

    void preencherEstadosFinais()
    {
        foreach(const Aresta<T> aresta,*this->objArestaEstado.getListaDeAresta())
        {
            //se o inicio da aresta for um estado final
            if(aresta.getQ0().getEhEstadoFinal())
            {
                marcarPorEstado(aresta.getQ0().getNome(),aresta.getQ1().getNome(),"X");
            }
        }
    }
    void preencherEstadosNaoFinaisComFinais()
    {
        foreach(const Aresta<T> aresta_i,*this->objArestaEstado.getListaDeAresta())
        {
            //se o estado não for marcado, marcamos ele com todos os finais
            if(!aresta_i.getQ0().getEhEstadoFinal())
            {
                foreach(const Aresta<T> aresta_j,*this->objArestaEstado.getListaDeAresta())
                {
                    if(aresta_j.getQ0().getEhEstadoFinal())
                    {
                        marcarPorEstado(aresta_i.getQ0().getNome(),aresta_j.getQ0().getNome());
                    }
                }

            }
        }
    }



    void preencherEstadosNaoEquivalentes()
    {
        for(int i = 1; i < this->coluna; i++)
        {
            int k = i - 1;
            for(int j = i; j < this->coluna;j++)
            {
                if(ehDebug)
                    std::cout <<"i = " << j << " j = "<< k << " " <<this->matriz[j][k].toStdString() << std::endl;
                //se não estiver marcada caso 1 e 2
                if(this->matriz[j][k] != "V" && this->matriz[j][k] != "X" && this->matriz[j][k] != "O")
                {
                    this->marcaEstadosNaoEquivalentes(j,k);
                }
                else//caso 3
                {
                    if(this->matriz[j][k] == "X" || this->matriz[j][k] == "O")
                    {
                        if(ehDebug)
                            std::cout << "CASO 3\n";
                        Estado<T> estado_1 = this->objArestaEstado.getListaDeEstado()->at(k);
                        Estado<T> estado_2 = this->objArestaEstado.getListaDeEstado()->at(j);

                        //caso 1
                        if(estado_1.getNome() != estado_2.getNome())
                        {
                            foreach (const QString item, *this->listaDeAlfabeto)
                            {
                                Estado<T> est_1 = this->objArestaEstado.funcaoProgramaEstendida(estado_1,item);
                                Estado<T> est_2 = this->objArestaEstado.funcaoProgramaEstendida(estado_2,item);

                                //caso 1
                                if(est_1.getNome() != est_2.getNome())
                                {
                                    int index_i = this->objArestaEstado.consultePosicaoEstado(est_1);
                                    int index_j = this->objArestaEstado.consultePosicaoEstado(est_2);

                                    if(index_j > index_i)
                                        troca(index_i,index_j);

                                    if(this->matriz[index_i][index_j] != "X")
                                    {

                                        this->matriz[index_i][index_j] = "O";
                                        //this->matriz[index_j][index_i] = "O";
                                    }

                                    QString nomeEstado = obterNomeCabecaLista(est_1,est_2);
                                    this->marcarMap(nomeEstado);
                                }

                            }
                        }


                    }
                }
            }
        }
    }

    void marcarMap(QString nomeEstado)
    {
        // std::cout<< "Estado = " << nomeEstado.toStdString() << std::endl;
        if(this->mapListPorEst.contains(nomeEstado))
        {
            // std::cout<< "entrou  1 "  << std::endl;
            for(int i = 0; i < this->mapListPorEst[nomeEstado].count();i++)
            {
                //std::cout<< "entrou  2 "  << std::endl;
                auto tupla = this->mapListPorEst[nomeEstado].at(i);

                Estado<T>est_1 = std::get<0>(tupla);
                Estado<T>est_2 = std::get<1>(tupla);

                int index_i = this->objArestaEstado.consultePosicaoEstado(est_1);
                int index_j = this->objArestaEstado.consultePosicaoEstado(est_2);

                if(index_j > index_i)
                    troca(index_i,index_j);

                this->matriz[index_i][index_j] = "O";

                if(this->ehDebug)
                    std::cout<< "MARCA MAP = ligando " + est_1.getNome().toStdString() + " a " +  est_2.getNome().toStdString()<< std::endl;

                QString nomeProxEst = this->obterNomeCabecaLista(est_1,est_2);
                this->marcarMap(nomeProxEst);

            }
        }
    }

    QString obterNomeCabecaLista(Estado<T> e1,Estado<T>e2)
    {
        return e1.getNome() > e2.getNome()
                ?  e2.getNome() + ";" + e1.getNome()
                 :  e1.getNome() + ";" + e2.getNome();
    }

    void marcaEstadosNaoEquivalentes(int i,int j)
    {
        Estado<T> estado_1 = this->objArestaEstado.getListaDeEstado()->at(j);
        Estado<T> estado_2 = this->objArestaEstado.getListaDeEstado()->at(i);

        //caso 1
        if(estado_1.getNome() == estado_2.getNome())
            return;

        foreach (const QString item, *this->listaDeAlfabeto)
        {
            Estado<T> est_1 = this->objArestaEstado.funcaoProgramaEstendida(estado_1,item);
            Estado<T> est_2 = this->objArestaEstado.funcaoProgramaEstendida(estado_2,item);

            //caso 1
            if(est_1.getNome() != est_2.getNome())
            {
                QString nomeLista = obterNomeCabecaLista(est_1,est_2);

                if(!this->mapListPorEst.contains(nomeLista))
                {
                    if(ehDebug)
                        std::cout << "Lista  << " + nomeLista.toStdString() + " criada\n";
                    QList<std::tuple<Estado<T>,Estado<T>>> *list = new QList<std::tuple<Estado<T>,Estado<T>>>();
                    this->mapListPorEst[nomeLista] = *list;
                }

                if(ehDebug)
                    std::cout << "Lista  << " + nomeLista.toStdString() + " aponta para " + this->obterNomeCabecaLista(estado_1,estado_2).toStdString() + "\n";
                std::tuple<Estado<T>,Estado<T>>tuplaDeEstado;
                std::get<0>(tuplaDeEstado) = estado_1;
                std::get<1>(tuplaDeEstado) = estado_2;
                this->mapListPorEst[nomeLista].push_back(tuplaDeEstado);
            }
        }
    }

    AFD<T>*gerarNovoAutomato()
    {
        AFD<T>* automato = new AFD<T>();
        QStringList listaNomesAutomatos;
        QList<mumu::Estado<QString>>*listaDeEstado = new QList<mumu::Estado<QString>>();

        //copia todos automatos
        for(int i = 0; i < this->objArestaEstado.getListaDeEstado()->count(); i++)
        {
            listaNomesAutomatos.push_back(this->objArestaEstado.getListaDeEstado()->at(i).getNome());
        }

        //pega os automatos a serem minimizados
        for(int i = 1; i < this->coluna; i++)
        {
            int k = i - 1;
            for(int j = i; j < this->coluna;j++)
            {
                if(this->matriz[j][k] == "*")
                {
                    Estado<T> estado_1 = this->objArestaEstado.getListaDeEstado()->at(j);
                    Estado<T> estado_2 = this->objArestaEstado.getListaDeEstado()->at(k);

                    bool podeSetar  = true;

                    //verificação para não unir estados que ja foram unidos
                    for(int k = 0; k < listaNomesAutomatos.count(); k++)
                    {
                        QString aux = listaNomesAutomatos.at(k);
                        if(aux.contains(QChar(';')))
                        {
                            QStringList listStr = aux.split(QChar(';'));
                            for(int l =0; l < listStr.count(); l++)
                            {
                                if(listStr.at(l) == estado_1.getNome() || listStr.at(l) == estado_2.getNome())
                                {
                                    podeSetar = false;
                                    l =  listStr.count() + 2;
                                    k = listaNomesAutomatos.count() + 2;
                                }
                            }
                        }

                    }

                    if(podeSetar)
                    {
                        listaNomesAutomatos.removeOne(estado_1.getNome());
                        listaNomesAutomatos.removeOne(estado_2.getNome());
                        listaNomesAutomatos.push_back(this->obterNomeCabecaLista(  estado_1,estado_2) );
                    }
                }
            }
        }



        //copia o alfabeto
        for(int i  = 0; i < this->listaDeAlfabeto->count(); i++)
        {
            automato->adicionarLetraDoAlfabeto(this->listaDeAlfabeto->at(i));
        }

        //pega os estados e defini os iniciais e finais
        for(int i = 0; i < listaNomesAutomatos.count(); i++)
        {
            QString nomeEstado = listaNomesAutomatos.at(i);
            bool ehMinimizado = nomeEstado.contains(QChar(';'));
            for(int j = 0; j < this->objArestaEstado.getListaDeEstado()->count(); j++)
            {
                if(ehMinimizado)
                {
                    QStringList list = nomeEstado.split(';');
                    if(list.count() > 1)
                    {
                        bool ehFinal  = false;
                        bool ehInicial = false;
                        Estado<T>estado;
                        estado.setNome(nomeEstado);
                        for(int k = 0; k < list.count();k++)
                        {
                            QString nomeAtual = list[k];
                            Estado<T>est = this->objArestaEstado.consulteEstadoPorNome(nomeAtual);

                            if(est.getEhEstadoFinal())
                                ehFinal = true;

                            if(est.getEhEstadoInicial())
                                ehInicial = true;

                            if(ehFinal && ehInicial)
                                k = list.count() + 2;

                        }
                        estado.setEhEstadoFinal(ehFinal);
                        estado.setEhEstadoInicial(ehInicial);
                        listaDeEstado->push_back(estado);
                        j = this->objArestaEstado.getListaDeEstado()->count() + 2;

                    }
                }
                else
                {
                    if(nomeEstado ==  this->objArestaEstado.getListaDeEstado()->at(j).getNome())
                    {
                        listaDeEstado->push_back(this->objArestaEstado.getListaDeEstado()->at(j));
                        j = this->objArestaEstado.getListaDeEstado()->count() + 2;
                    }
                }
            }
        }

        //associação fisica
        for(int i = 0; i < listaDeEstado->count();i++)
        {
            mumu::Estado<QString> estado = listaDeEstado->at(i);
            automato->getObjArestaEstado().incluirEstado(estado);
            if(ehDebug)
                std::cout <<"Nome estado = " <<estado.getNome().toStdString() << "\n";
        }



        //ligação de aresta
        foreach(QString item,listaNomesAutomatos)
        {
            bool ehMinimizado = item.contains(QChar(';'));
            foreach(Aresta<T> aresta, *this->objArestaEstado.getListaDeAresta())
            {
                if(ehMinimizado)
                {
                    QString nomeEstado = item.split(';').at(0);
                    if(ehDebug)
                        std::cout << " Minimo entrou  com " << item.toStdString() << std::endl;
                    if(nomeEstado == aresta.getQ0().getNome())
                    {
                        if(ehDebug)
                            std::cout << " Minimo  buscou com " << nomeEstado.toStdString() << std::endl;
                        Estado<T>e1 = aresta.getQ0();
                        Estado<T>e2 = aresta.getQ1();

                        bool entrou[2] = {false,false};

                        for(int i = 0; i < listaNomesAutomatos.count(); i++)
                        {
                            if(listaNomesAutomatos[i].contains(e2.getNome()) && !entrou[0])
                            {
                                e2.setNome(listaNomesAutomatos.at(i));
                            }
                            if(listaNomesAutomatos[i].contains(e1.getNome()) && !entrou[1])
                            {
                                e1.setNome(listaNomesAutomatos.at(i));
                            }

                            if(entrou[0] && entrou[1])
                            {
                                i = listaNomesAutomatos.count() + 2;
                            }
                        }
                        if(ehDebug)
                            std::cout <<"MINIMO + " << "Estado 1 " << e1.getNome().toStdString() << " Estado 2 " << e2.getNome().toStdString() <<" COM " << aresta.getValor().toStdString() << "\n";
                        automato->getObjArestaEstado().ligarEstado(e1,e2,aresta.getValor());
                    }
                }
                else
                {
                    if(item == aresta.getQ0().getNome())
                    {
                        if(ehDebug)
                            std::cout << "NÂO Minimo entrou com " << item.toStdString() << std::endl;

                        Estado<T>e1 = aresta.getQ0();
                        Estado<T>e2 = aresta.getQ1();
                        bool entrou[2] = {false,false};

                        for(int i = 0; i < listaNomesAutomatos.count(); i++)
                        {
                            if(listaNomesAutomatos[i].contains(e2.getNome()) && !entrou[0])
                            {
                                e2.setNome(listaNomesAutomatos.at(i));
                            }
                            if(listaNomesAutomatos[i].contains(e1.getNome()) && !entrou[1])
                            {
                                e1.setNome(listaNomesAutomatos.at(i));

                            }

                            if(entrou[0] && entrou[1])
                            {
                                i = listaNomesAutomatos.count() + 2;
                            }
                        }
                        if(ehDebug)
                            std::cout <<"<NÂO  Minimizado " << "Estado 1 " << e1.getNome().toStdString() << " Estado 2 " << e2.getNome().toStdString() <<" COM " << aresta.getValor().toStdString() << "\n";

                        automato->getObjArestaEstado().ligarEstado(e1,e2,aresta.getValor());


                    }
                }
            }
        }
        automato->montarAutomato();
        return automato;
    }

    inline bool getDebug(){return this->ehDebug;}
};

template <class T>
AFD<T> *AFD<T>::mininmizar()
{
    if(!this->ehSensoEstrito())
        throw QString("O Automato não é Senso Estrito!");

    int linhaColuna = this->objArestaEstado.getListaDeEstado()->count();
    MatrizAFD<T> matriz(linhaColuna,linhaColuna,this->listaDeAlfabeto,this->objArestaEstado);
    matriz.preencher("*");
    bool debug = matriz.getDebug();

    if(debug)
    {
        std::cout << "Matriz antes de preencher estados finais\n";
        matriz.imprimir();
        std::cout << std::endl;
    };

    matriz.preencherEstadosFinais();


    if(debug)
    {
        std::cout << "Matriz apos preencher estados finais\n";
        matriz.imprimir();
        std::cout << std::endl;
    }
    matriz.preencherEstadosNaoFinaisComFinais();
    if(debug)
    {
        std::cout << "Matriz apos de preencher os estados não finais com finais\n";
        matriz.imprimir();
        std::cout << std::endl;
    }
    matriz.preencherEstadosNaoEquivalentes();
    if(debug)
    {
        std::cout << "Matriz apos de preencher os  não equivalentes\n";
        matriz.imprimir();
        std::cout << std::endl;
    }
    return matriz.gerarNovoAutomato();
}


}


#endif // AFD_H


