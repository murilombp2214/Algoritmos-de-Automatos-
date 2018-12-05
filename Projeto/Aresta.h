#ifndef ARESTA_H
#define ARESTA_H

#include<Estado.h>

#include<QString>

namespace mumu
{
template<class T>
class Aresta
{
    private:

        ///<summary>
        ///   VALUE = Valor da aresta
        /// <summary/>
        T valor;


        ///<summary>
        ///   Estado de inicio da aresta
        /// <summary/>
        Estado<T> q0;

        ///<summary>
        ///   Estado de fim da aresta
        /// <summary/>
        Estado<T> q1;

    public:
        Aresta<T>(){}
        ~Aresta(){}

        inline T getValor() const {return this->valor;}

        inline void setValor(T &valor) {this->valor = valor;}


        inline void ligarEstado(Estado<T> q0,Estado<T> q1) {this->q0 = q0;this->q1 = q1;}
        inline void ligarEstado(Estado<T> &q0,Estado<T> &q1,T &valor) {this->q0 = q0;this->q1 = q1;this->valor = valor;}
        inline void ligarEstado(T &valor) {this->valor = valor;}

        Estado<T> getQ0() const{return this->q0;}
        Estado<T> getQ1() const {return this->q1;}

        void setQ1(const Estado<T> &value) {this->q1 = value;}
        void setQ0(const Estado<T> &value) {this->q0 = value;}

        inline bool operator == (Aresta<T> obj){return obj.getQ0() == q0 && this->valor == obj.valor &&  obj.getQ1() == q1;}
        inline bool operator != (Aresta<T> obj){return !operator !=(obj);}
};







}
#endif // ARESTA_H
