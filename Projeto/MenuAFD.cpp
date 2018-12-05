
namespace mumu {


namespace menuAFD {


#include<iostream>


#include<AFD.h>
#include<Estado.h>
#include<Aresta.h>
#include<ArestaEstado.h>
#include<QString>

//VARIAVEIS GLOBAIS

static mumu::AFD<QString> automatoDeterministico;

static QList<mumu::Estado<QString>> *listaDeEstado = new QList<mumu::Estado<QString>>();


static mumu::Estado<QString> item; //usada para foreach


//SOBRECARGAS DE OPERADORES


std::ostream& operator << (std::ostream &entrada, QString &obj)
{
    return entrada << obj.toStdString();

}



//METODOS AUX(S)
void lerQtdEstado(int &qtdEstado)
{
    while(qtdEstado <= 0)
    {
        std::cout << "Quantidade de estados: ";
        std::cin >> qtdEstado;

        if(qtdEstado <= 0)
        {
            std::cerr << "A Quantidade deve ser maior ou igual a zero( >= 0 )\n";
        }

    }
}

std::string stringEmpty()
{

    return "";
}


void limparTela()
{

#ifdef  linux
    system("clear");
#elif defined WIN32 //windows
    system("cls");
#else//mac e outros
    int i = 0;
    while(++i < 100) std::cout << "\n";
#endif

}

void lerEstados(int qtdEstado)
{

    std::cout << "Informe Estados inicias\n";
    bool informouEstadoInicial = false;
    for(int i = 0; i < qtdEstado; i++)
    {
        std::string nomeEstado = "";
        while(nomeEstado == stringEmpty())
        {
            std::cout << "Estado " << i + 1 << " :";
            std::cin >> nomeEstado;

            mumu::Estado<QString>estado;
            estado.setNome(QString::fromStdString(nomeEstado));
            if(listaDeEstado->contains(estado))
            {
                std::cout << "O Estado de nome " + nomeEstado   << " ja esta em uso\n";
                nomeEstado = stringEmpty();
            }
            else
            {
                if(!informouEstadoInicial)
                {
                    char resposta[100];
                    std::cout << "Inicial ? ";
                    std::cin >> resposta;
                    if(resposta[0] == 's' || resposta[0] == 'S')
                    {
                        estado.setEhEstadoInicial(true);
                        informouEstadoInicial = true;
                    }

                }

                char respostaFinal[100];
                std::cout << "Final ? ";
                std::cin >> respostaFinal;
                estado.setEhEstadoFinal(respostaFinal[0] == 's' || respostaFinal[0] == 'S');

                if(!listaDeEstado)
                    throw QString("erro lista nao setada");
                listaDeEstado->push_back(estado);

            }
        }
    }
}



void criarAlfabeto()
{

        std::string alfabeto;
        std::cout << "Digite o alfabeto separado por ponto e virgula,\ncaso exista caracter repetido o sistema ira considerar apenas um :\n";
        std::cin >> alfabeto;

        QStringList list = QString::fromStdString(alfabeto).split(';');
        for(int i = 0; i < list.size(); i++)
        {
            automatoDeterministico.adicionarLetraDoAlfabeto(list[i]);
        }



}

mumu::Estado<QString>& retornaEstadoPorNome(QString nome)
{

        foreach(item,*listaDeEstado)
        {
            if(item.getNome() == nome)
            {
                return item;
            }
        }
    throw QString("Erro com a mensagem '" + nome + "não foi encontrado '\n - main.retornaEstadoPorNome");
}



void associarEstadosAutomatoDeterministico()
{
    bool ehFimDaAssociacao = false;
    std::string associacao1 = stringEmpty();
    std::string associacao2 = stringEmpty();
    std::string letra = stringEmpty();

    std::cout << "Digite as associacoes e a letra do seu alfabeto : ";
    while(!ehFimDaAssociacao)
    {
        try
        {
            std::cout << "\nAssociacao 1 : ";
            std::cin >> associacao1;

            std::cout << "\nAssociacao 2 : ";
            std::cin >> associacao2;

            std::cout << "\nLetra : ";
            std::cin >> letra;

            if(!automatoDeterministico.getListaDeAlfabeto()->contains(QString::fromStdString(letra)))
            {
                std::cerr << "Essa Letra nao pertence ao alfabeto!\n";
            }
            else
            {
                mumu::Estado<QString> q0 = retornaEstadoPorNome(QString::fromStdString(associacao1));
                mumu::Estado<QString> q1 = retornaEstadoPorNome(QString::fromStdString(associacao2));

                automatoDeterministico.getObjArestaEstado().ligarEstado(q0,q1,QString::fromStdString(letra));

                std::string aux;
                std::cout << "Deseja associar mais estados ? ";
                std::cin >> aux;

                if(aux == "N" || aux == "n")
                    ehFimDaAssociacao = true;
            }
        }
        catch(QString &erro)
        {
            std:: cerr << erro;
        }
    }
}


void mostrarAutomato(mumu::AFD<QString> *automato)
{
    QMapIterator<QString,QList<mumu::Aresta<QString>>> colecao(automato->getMapObjAutomato());
    while(colecao.hasNext())
    {
        colecao.next();

        std::cout << colecao.key().toStdString() << " -> ";
        for(int i = 0; i < colecao.value().count(); i++)
        {
            std::cout << colecao.value().at(i).getValor().toStdString() << " -> " << colecao.value().at(i).getQ1().getNome().toStdString() << " - >";
        }

        if(retornaEstadoPorNome(colecao.key()).getEhEstadoInicial())
        {
            std::cout << " = EI ";
        }

        if(retornaEstadoPorNome(colecao.key()).getEhEstadoFinal())
        {
            std::cout << " = EF";
        }

        std::cout << "\n";
    }
}

std::string mostrarOpcaoMenu()
{
    std::string menu = "";
    menu += "******************AFD**************************\n";
    menu += "1 - Minimizar\n";
    menu += "2 - Submeter palavra\n";
    menu += "3 - Ver automato\n";
    menu += "0 - Sair\n";

    menu += "\n";
    return menu;
}

//MAIN
void menu()
{

    try
    {
        //Declaração de variaveis
        int qtdEstado = 0;


        //Leitura de Dados
        lerQtdEstado(qtdEstado);

        limparTela();

        //criando alfabeto
        criarAlfabeto();

        limparTela();

        //cruando estados
        lerEstados(qtdEstado);
        for(int i = 0; i < listaDeEstado->count();i++)
        {
            mumu::Estado<QString> estado = listaDeEstado->at(i);
            automatoDeterministico.getObjArestaEstado().incluirEstado(estado);
        }

        limparTela();
        //associando estados
        associarEstadosAutomatoDeterministico();


        //cria o automato
        automatoDeterministico.montarAutomato();

        bool ehFimDePrograma = false;
        char opcao = '0';

        limparTela();
        while(!ehFimDePrograma)
        {
            std::cout<<mostrarOpcaoMenu();
            std::cin >> opcao;
            limparTela();
            switch (opcao) {
            case '0':
            {
                ehFimDePrograma = true;
                automatoDeterministico = mumu::AFD<QString>();
                listaDeEstado->clear();
            }
                break;
            case '1':
            {
                auto t = automatoDeterministico.mininmizar();
                std::cout << "e1 " << t->getObjArestaEstado().getListaDeEstado()->at(0).getNome().toStdString() << "\n";

                std::cout << "e2 " << t->getObjArestaEstado().getListaDeEstado()->at(1).getNome().toStdString() << "\n";

            }
                break;
            case '2':
            {
                std::string palavra;
                std::cout << "Palavra :";
                std::cin >> palavra;
                if(automatoDeterministico.submeterPalavra(QString::fromStdString(palavra)))
                {
                    std::cout << "Palavra aceita\n";
                }
                else
                {
                    std::cout << "Palavra não aceita\n";
                }
            }
                break;
            case '3':
                mostrarAutomato(&automatoDeterministico);
                std::cout << "";
                break;
            default:
                std::cerr << "\nOpção invalida\n - Atencao";
                break;
            }
        }



    }
    catch(QString &erro)
    {
        std::cerr << erro << " Atenção" << std::endl;
    }

}




void menuPrinc(mumu::AFD<QString> &automato,QList<mumu::Estado<QString>> *_listaDeEstado)
{

    listaDeEstado = _listaDeEstado;
    bool ehFimDePrograma = false;
    char opcao = '0';

    limparTela();
    while(!ehFimDePrograma)
    {
        std::cout<<mostrarOpcaoMenu();
        std::cin >> opcao;
        limparTela();
        switch (opcao) {
        case '0':
        {
            ehFimDePrograma = true;
            automato = mumu::AFD<QString>();
            listaDeEstado->clear();
        }
            break;
        case '1':
        {
            try
            {
                auto autoAux = automato.mininmizar();
                auto listAux = listaDeEstado;
                listaDeEstado = autoAux->getObjArestaEstado().getCopiaListaDeEstado();
                mostrarAutomato(autoAux);
                listaDeEstado = listAux;
            }
            catch(QString &erro){std::cerr << erro.toStdString();}
        }
            break;
        case '2':
        {
            std::string palavra;
            std::cout << "Palavra :";
            std::cin >> palavra;
            if(automato.submeterPalavra(QString::fromStdString(palavra)))
            {
                std::cout << "Palavra aceita\n";
            }
            else
            {
                std::cout << "Palavra não aceita\n";
            }
        }
            break;
        case '3':
            mostrarAutomato(&automato);
            std::cout << "";
            break;
        default:
            std::cerr << "\nOpção invalida\n - Atencao";
            break;
        }
    }



}
/*exemplo de impressão AFD

            QMapIterator<QString,QList<mumu::Aresta<QString>>> colecao(automatoDeterministico.getMapObjAutomato());
            while(colecao.hasNext())
            {
                colecao.next();
                std::cout << colecao.key().toStdString() << " -> ";
                for(int i = 0; i < colecao.value().count(); i++)
                {
                    std::cout << colecao.value().at(i).getValor().toStdString() << " -> " << colecao.value().at(i).getQ1().getNome().toStdString() << "-->";
                }
                std::cout << "\n";
            }
*/



}//fim afd

}

