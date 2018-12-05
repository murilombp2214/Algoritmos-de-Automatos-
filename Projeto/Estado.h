#ifndef ESTADO_H
#define ESTADO_H


#include<QString>
#include<QList>

namespace mumu
{
template <class T>
class Estado
{
private:
    ///<summary>
    /// Nome do estado
    /// <summary/>
    QString nome;

    ///<summary>
    ///   Verifica se é estado inicial
    /// <summary/>
    ///
    bool ehEstadoInicial;

    ///<summary>
    ///   Verifica se é estado final
    /// <summary/>
    bool ehEstadoFinal;

    ///<summary>
    ///  Lista de estados que esse estado com transição vazia leva
    /// <summary/>
    QList<Estado<T>> *listaDeEstadoEpson;
public:
    Estado<T>(){ehEstadoInicial = ehEstadoFinal = false;}
    Estado<T>(QString nome):nome(nome){ehEstadoInicial = ehEstadoFinal = false;}
    ~Estado()
    {

    }

    inline QString getNome()const{return this->nome;}
    inline bool getEhEstadoInicial() const {return this->ehEstadoInicial;}
    inline bool getEhEstadoFinal() const{return this->ehEstadoFinal;}

    inline void setNome(QString nome){this->nome = nome;}                             
    inline void setEhEstadoInicial(bool ehEstadoInicial) {this->ehEstadoInicial = ehEstadoInicial;}
    inline void setEhEstadoFinal(bool ehEstadoFinal){this->ehEstadoFinal = ehEstadoFinal;}

    inline bool operator == (Estado<T> obj){return obj.getNome() == this->nome;}
    inline bool operator != (Estado<T> obj){return obj.getNome() != this->nome;}
    inline bool operator > (Estado<T> obj){return obj.getNome() > this->nome;}
    inline bool operator < (Estado<T> obj){return obj.getNome() < this->nome;}
    inline bool operator >= (Estado<T> obj){return obj.getNome() >= this->nome;}
    inline bool operator <= (Estado<T> obj){return obj.getNome() <= this->nome;}
};






}

#endif // ESTADO_H
