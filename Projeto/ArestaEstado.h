#ifndef ARESTAESTADO_H
#define ARESTAESTADO_H

#include<Aresta.h>
#include<Estado.h>

#include<iostream>

namespace mumu
{
template<class T>
class ArestaEstado
{
private:
    ///<summary>
    ///  Lista de Estado
    /// <summary/>
    QList<Estado<T>> *listaDeEstado;
    ///<summary>
    ///   Lista de Aresta
    /// <summary/>
    QList<Aresta<T>> *listaDeAresta;
public:
    ArestaEstado<T>(){listaDeEstado = new QList<Estado<T>>();listaDeAresta = new QList<Aresta<T>>();}
    ~ArestaEstado<T>()
    {

    }


    bool ehEstadoRepetido(Estado<T> obj);
    bool ehEstadoRepetido(T nomeEstado){return ehEstadoRepetido(Estado<T>(nomeEstado) );}
    bool possuiLetra(T letra, Estado<T> &estado);


    void incluirEstado(Estado<T> &obj);
    void ligarEstado(Estado<T> &q0,Estado<T> &q1,T ligacao);
    void ligarEstado(T &q0,T &q1,T ligacao);
    QList<Aresta<T> >const  * getListaDeAresta()  const {return this->listaDeAresta;}
    QList<Estado<T> >const  * getListaDeEstado()  const {return this->listaDeEstado;}
    QList<Estado<T> >  * getCopiaListaDeEstado()  const;
    Estado<T> consulteEstadoPorNome(QString nome);
    QList<Estado<T>>consulteListaDeEstadoPorNome(QString nome);
    Estado<T> funcaoProgramaEstendida(Estado<T>estado,T letra);
    QList<Estado<T>>consulteListFuncaoProgramaEstendida(Estado<T>estado,T letra);

    //obtem todos os estados alcançados aparti de uma letra, usado para transições vazias
    void bfs_custumer(Estado<T> estado,T letra,QStringList *listaDeEstadoCustumer);

    int consultePosicaoEstado(Estado<T>estado);
};



template<class T>
void  ArestaEstado<T>:: bfs_custumer(Estado<T> estado,T letra,QStringList *listaDeEstadoCustumer)
{
    if(!listaDeEstadoCustumer->contains(estado.getNome()))
    {
        listaDeEstadoCustumer->push_back(estado.getNome());
        foreach(Aresta<T> item, *this->listaDeAresta)
        {
            if(item.getQ0().getNome() == estado.getNome() && item.getValor() == letra)
            {
                bfs_custumer(item.getQ1(),letra,listaDeEstadoCustumer);
            }
        }
    }
}


template<class T>
QList<Estado<T> >* ArestaEstado<T>::getCopiaListaDeEstado() const
{
    QList<Estado<T> >* list = new QList<Estado<T> > ();
    foreach (Estado<T> item, *this->listaDeEstado)
    {
       Estado<T>estado(item);
       list->push_back(estado);
    }
    return list;
}

template<class T>
bool ArestaEstado<T>::ehEstadoRepetido(Estado<T> obj)
{
    for(auto i = listaDeEstado->begin(); i != listaDeEstado->end(); i++)
    {
        if(((Estado<T>)*i).getNome() == obj.getNome())
        {
            return true;
        }
    }
    return false;
}

template<class T>
bool ArestaEstado<T>::possuiLetra(T letra, Estado<T> &estado)
{
    if(!this->listaDeEstado->contains(estado))
        return false;
    for(int i = 0; i < this->listaDeAresta->count(); i++)
    {
        if(this->listaDeAresta->at(i).getQ0() == estado && this->listaDeAresta->at(i).getValor() == letra)
        {
            return true;
        }
    }
    return false;
}



template<class T>
void ArestaEstado<T>::incluirEstado(Estado<T> &obj)
{
    if(this->ehEstadoRepetido(obj))
        throw QString("Erro com a mensagem 'O Nome do estado " + obj.getNome() + " já esta em uso!'" + "\n ArestaEstado.incluirEstado - 1");

    this->listaDeEstado->push_back(obj);
}

template<class T>
void ArestaEstado<T>::ligarEstado(Estado<T> &q0, Estado<T> &q1, T ligacao)
{
    if(!ehEstadoRepetido(q0))
        throw QString("Erro com a mensagem 'O Nome do estado " + q0.getNome() + " não existe!'" + "\n ArestaEstado.ligarEstado - 1");

    if(!ehEstadoRepetido(q1))
        throw QString("Erro com a mensagem 'O Nome do estado " + q1.getNome() + " não existe!'" + "\n ArestaEstado.ligarEstado - 2");

    if(ligacao == "")
        throw QString("Erro com a mensagem 'A ligação não pode ser vazia!' \n ArestaEstado.ligarEstado - 3");

    Aresta<T> objAresta;
    objAresta.setValor(ligacao);
    objAresta.ligarEstado(q0,q1);
    this->listaDeAresta->push_back(objAresta);
}

template<class T>
void ArestaEstado<T>::ligarEstado(T &q0,T &q1,T ligacao)
{
    int indexQ0  = -1;
    int indexQ1 = -1;
    for(int i  = 0; i < listaDeEstado->count(); i++)
    {
        if(this->listaDeEstado->at(i).getNome() == q0)
            indexQ0 = i;
        if(this->listaDeEstado->at(i).getNome() == q1)
            indexQ1 = i;
    }

    //this->ligarEstado(this->listaDeEstado->at(indexQ0),this->listaDeEstado->at(indexQ1),ligacao);

    Aresta<T> objAresta;
    objAresta.setQ1(this->listaDeEstado->at(indexQ1));
    objAresta.setQ0(this->listaDeEstado->at(indexQ0));
    objAresta.setValor(ligacao);
    this->listaDeAresta->push_front(objAresta);
}

template<class T>
Estado<T> ArestaEstado<T>::consulteEstadoPorNome(QString nome)
{
    for(int i  = 0; i < listaDeEstado->count(); i++)
    {
        if(this->listaDeEstado->at(i).getNome().trimmed() ==  nome.trimmed())
        {
            Estado<T> estado;
            estado.setEhEstadoFinal(this->listaDeEstado->at(i).getEhEstadoFinal());
            estado.setEhEstadoInicial(this->listaDeEstado->at(i).getEhEstadoInicial());
            estado.setNome(this->listaDeEstado->at(i).getNome());
            return estado;
        }
    }

    throw QString("O Estado " + nome + " nao existe na lista de estado - ArestaEstado.consulteEstadoPorNome 1");
}


template<class T>
QList<Estado<T>> ArestaEstado<T>::consulteListaDeEstadoPorNome(QString nome)
{
    QList<Estado<T>>list;
    for(int i  = 0; i < listaDeEstado->count(); i++)
    {
        if(this->listaDeEstado->at(i).getNome() == nome)
        {
            Estado<T> estado;
            estado.setEhEstadoFinal(this->listaDeEstado->at(i).getEhEstadoFinal());
            estado.setEhEstadoInicial(this->listaDeEstado->at(i).getEhEstadoInicial());
            estado.setNome(this->listaDeEstado->at(i).getNome());
            list.push_back(estado);
        }
    }
    return list;
}
template<class T>
Estado<T> ArestaEstado<T>:: funcaoProgramaEstendida(Estado<T>estado,T letra)
{
    foreach(const Aresta<T>aresta_i,*this->listaDeAresta)
    {
        if(aresta_i.getQ0().getNome() == estado.getNome() && letra == aresta_i.getValor())
        {
            Estado<T> estado;
            estado.setEhEstadoFinal(aresta_i.getQ1().getEhEstadoFinal());
            estado.setEhEstadoInicial(aresta_i.getQ1().getEhEstadoInicial());
            estado.setNome(aresta_i.getQ1().getNome());
            return estado;
        }
    }

    throw QString("A palavra " + letra + " ou o estado " + estado.getNome() + " nao foi encontrado - ArestaEstado.funcaoProgramaEstendida");
}
template<class T>
QList<Estado<T>> ArestaEstado<T>:: consulteListFuncaoProgramaEstendida(Estado<T>estado,T letra)
{
    auto ordenacao = []( Estado<T> &v1,  Estado<T> &v2){return v1.getNome() > v2.getNome(); };
    QList<Estado<T>> list;
    foreach(const Aresta<T>aresta_i,*this->listaDeAresta)
    {
        if(aresta_i.getQ0().getNome() == estado.getNome() && letra == aresta_i.getValor())
        {
            Estado<T> estado;
            estado.setEhEstadoFinal(aresta_i.getQ1().getEhEstadoFinal());
            estado.setEhEstadoInicial(aresta_i.getQ1().getEhEstadoInicial());
            estado.setNome(aresta_i.getQ1().getNome());
            list.push_back(estado);
        }
    }
    qSort(list.begin(),list.end(),ordenacao);
    return list;
}


template<class T>
int ArestaEstado<T>::consultePosicaoEstado(Estado<T> estado)
{
    for(int i  = 0; i < listaDeEstado->count(); i++)
    {
        if(this->listaDeEstado->at(i).getNome() == estado.getNome())
        {
            return i;
        }
    }

    throw QString("O Estado " + estado.getNome() + " nao existe na lista de estado - ArestaEstado.consultePosicaoEstado 1");
}


}

#endif // ARESTAESTADO_H
