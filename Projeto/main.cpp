#include<iostream>
#include<fstream>
#include<AFD.h>
#include<Estado.h>
#include<Aresta.h>
#include<ArestaEstado.h>


#include<MenuAFD.cpp>
#include<MenuAFND.h>
#include<MenuAF_Epson.h>

#include<QFile>
#include<QTextStream>

#include<QString>

#include <unistd.h>








void aberturaFormatoStarWars()
{

    std::string mario =
    "___________________▄▄▄▀▀▀▀▀▀▀▄                                                             \n"
    " _______________▄▀▀____▀▀▀▀▄____█                                                         \n"
    " ___________▄▀▀__▀▀▀▀▀▀▄___▀▄___█                                                         \n"
    " __________█▄▄▄▄▄▄_______▀▄__▀▄__█                                                        \n"
    " _________█_________▀▄______█____█_█                                                      \n"
    " ______▄█_____________▀▄_____▐___▐_▌                                                      \n"
    " ______██_______________▀▄___▐_▄▀▀▀▄                                                      \n"
    " ______█________██_______▌__▐▄▀______█                                                    \n"
    " ______█_________█_______▌__▐▐________▐                                                   \n"
    " _____▐__________▌_____▄▀▀▀__▌_______▐_____________▄▄▄▄▄▄                                 \n"
    " ______▌__________▀▀▀▀________▀▀▄▄▄▀______▄▄████▓▓▓▓▓▓▓███▄                               \n"
    " ______▌____________________________▄▀__▄▄█▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄                             \n"
    " ______▐__________________________▄▀_▄█▓▓▓▓▓▓▓▓▓▓_____▓▓____▓▓█▄                          \n"
    " _______▌______________________▄▀_▄█▓▓▓▓▓▓▓▓▓▓▓____▓▓_▓▓_▓▓__▓▓█                          \n"
    " _____▄▀▄_________________▄▀▀▌██▓▓▓▓▓▓▓▓▓▓▓▓▓__▓▓▓___▓▓_▓▓__▓▓█                           \n"
    " ____▌____▀▀▀▄▄▄▄▄▄▄▄▀▀___▌█▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓__▓________▓▓___▓▓▓█                           \n"
    " _____▀▄_________________▄▀▀▓▓▓▓▓▓▓▓█████████████▄▄_____▓▓__▓▓▓█                          \n"
    " _______█▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█▓▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▄▄___▓▓▓▓▓█                              \n"
    " _______█▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█▓▓███▓▓▓▓████▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓▓█                              \n"
    " ________█▓▓▓▓▓▓▓▓▓▓▓▓▓▓█▓█▓▓██░░███████░██▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓█                             \n"
    " ________█▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓░░░░░█░░░░░██░░░░██▓▓▓▓▓▓▓▓▓██▓▓▓▓▌                            \n"
    " ________█▓▓▓▓▓▓▓▓▓▓▓▓▓▓███░░░░░░░░____░██░░░░░░░██▓▓▓▓▓▓▓██▓▓▌                           \n"
    " ________▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓██░░░░░░░________░░░░░░░░░██████▓▓▓▓▓█▓▌                          \n"
    " ________▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓██░░░░░░___▓▓▓▓▓░░░░░░░███░░███▓▓▓▓▓█▓▌                           \n"
    " _________█▓▓▓▓▓▓▓▓▓▓▓▓▓██░░░░░___▓▓█▄▄▓░░░░░░░░___░░░░█▓▓▓▓▓█▓▌                          \n"
    " _________█▓▓▓▓▓▓▓▓▓▓▓▓▓█░░█░░░___▓▓██░░░░░░░░▓▓▓▓__░░░░█▓▓▓▓██                           \n"
    " _________█▓▓▓▓▓▓▓▓▓▓▓▓▓█░███░░____▓░░░░░░░░░░░█▄█▓__░░░░█▓▓█▓█                           \n"
    " _________▐▓▓▓▓▓▓▓▓▓▓▓▓▓█░█████░░░░░░░░░░░░░░░░░█▓__░░░░███▓█                             \n"
    " __________█▓▓▓▓▓▓▓▓▓▓▓▓█░░███████░░░░░░░░░░░░░░░▓_░░░░░██▓█                              \n"
    " __________█▓▓▓▓▓▓▓▓▓▓▓▓█░░░███████░░░░░░░░░░░░░░_░░░░░██▓█                               \n"
    " __________█▓▓▓▓▓▓▓▓▓▓▓▓█░░░███████░░░░░░░░░░░░░░░░░░░██▓█                                \n"
    " ___________█▓▓▓▓▓▓▓▓▓▓▓▓█░░░░███████░░░░░░░░░░░█████░██░░▓                               \n"
    " ___________█▓▓▓▓▓▓▓▓▓▓▓▓█░░░░░░__███████░░░░░███████░░█░░░▓                              \n"
    " ___________█▓▓▓▓▓▓▓▓▓▓▓▓▓█░░░░░░█▄▄▄▀▀▀▀████████████░░█░░░▓                              \n"
    " ___________▐▓▓▓▓▓▓▓▓▓▓▓▓█░░░░░░██████▄__▀▀░░░███░░░░░█░░▓▓▓                              \n"
    " ___________▐▓▓▓▓▓▓▓▓▓▓▓█▒█░░░░░░▓▓▓▓▓███▄░░░░░░░░░░░░▓▓▓▓_____▄▄▄                        \n"
    " ___________█▓▓▓▓▓▓▓▓▓█▒▒▒▒█░░░░░░▓▓▓▓▓█░░░░░░░░░░▓▓      ▓▄▄▄_▄▀▀____▀▄                  \n"
    " __________█▓▓▓▓▓▓▓▓▓█▒▒▒▒█▓▓░░░░░░░░░░░░░░░░░░   ▓▓____▄▀____▀▄_________▀▄               \n"
    " _________█▓▓▓▓▓▓▓▓▓█▒▒▒▒█▓▓▓▓░░░░░░░░░░░░▓▓▓▓▓______▐▄________█▄▄▀▀▀▄__█                 \n"
    " ________█▓▓▓▓▓▓▓▓█▒▒▒▒▒▒█▓▓▓▓▓▓▓░░░░░░░░▓____________█_█______▐_________▀▄▌              \n"
    " _______█▓▓▓▓▓▓▓▓█▒▒▒▒▒▒███▓▓▓▓▓▓▓▓▓▓▓█▒▒▄___________█__▀▄____█____▄▄▄____▐               \n"
    " ______█▓▓▓▓▓▓▓█_______▒▒█▒▒██▓▓▓▓▓▓▓▓▓▓█▒▒▒▄_________█____▀▀█▀▄▀▀▀___▀▀▄▄▐               \n"
    " _____█▓▓▓▓▓██▒_________▒█▒▒▒▒▒███▓▓▓▓▓▓█▒▒▒██________▐_______▀█_____________█            \n"
    " ____█▓▓████▒█▒_________▒█▒▒▒▒▒▒▒▒███████▒▒▒▒██_______█_______▐______▄▄▄_____█            \n"
    " __█▒██▒▒▒▒▒▒█▒▒____▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒____▒█▓█__▄█__█______▀▄▄▀▀____▀▀▄▄█               \n"
    " __█▒▒▒▒▒▒▒▒▒▒█▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█_______█▓▓█▓▓▌_▐________▐____________▐              \n"
    " __█▒▒▒▒▒▒▒▒▒▒▒███▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒_______█▓▓▓█▓▌__▌_______▐_____▄▄____▐               \n"
    " _█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒_____█▓▓▓█▓▓▌__▌_______▀▄▄▀______▐                 \n"
    " _█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████▓▓█▓▓▓▌__▀▄_______________▄▀                  \n"
    " _█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███▒▒▒▒▒▒▒██▓▓▓▓▓▌___▀▄_________▄▀▀                     \n"
    " █▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒▒█▓▓▓▓▓▀▄__▀▄▄█▀▀▀                           \n"
    " █▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▓▓▓▓██▄▄▄▀                               \n"
    " █▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████                                     \n"
    " █▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█                                       \n"
    " _█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▄▄▄▄▄                                 \n"
    " _█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███▒▒▒▒▒▒██▄▄                             \n"
    " __█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒███▒▒▒▒▒▒▒▒▒▒▒▒▒█▄                           \n"
    " __█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█                          \n"
    " __█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█                         \n"
    " ___█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▌                        \n"
    " ____█▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░▒▒▌                        \n"
    " ____█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████▒▒▒▒▒█▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒░▒▌                        \n"
    " _____█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█_______▐▒▒▒▒█▒▒▒▒▒▒▒░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▌                      \n"
    " ______█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█________█▒▒█▒▒▒▒▒▒░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌                      \n"
    " _______█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█________█▒█▒▒▒▒▒▒░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌                      \n"
    " ________█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█________█▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█                       \n"
    " _________█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█________█▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█                        \n"
    " _________█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█________█▒▒▒░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀                         \n"
    " __________█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█_______█▒░░░▒▒▒▒▒░░░░░░░░▒▒▒█▀▀▀                           \n"
    " ___________█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█_______█░▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░█▀                              \n"
    " ____________█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█_______█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀                                \n"
    " _____________█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█_______█▒▒▒▒▒▒▒▒▒           ▀                           \n";

    std::string aed[5] =
    {
       " /$$             /$$$$$$$$        /$$$$$$  \n"
       "| $$            | $$_____/       //$$__ $$ \n"
       "| $$            | $$            | $$  \\ $$ \n"
       "| $$            | $$$$$         | $$$$$$$$  \n"
       "| $$            | $$__/         | $$__  $$ \n"
       "| $$            | $$            | $$  | $$  \n"
       "| $$$$$$$$      | $$            | $$  | $$  \n"
       "|________/      |__/            |__/  |_$$  \n",


        " /$$             /$$$$$$$$        /$$$$$$  \n"
        "| $$            | $$_____/       //$$__ $$ \n"
        "| $$            | $$            | $$  \\ $$ \n"
        "| $$            | $$$$$         | $$$$$$$$  \n"
        "| $$            | $$__/         | $$__  $$ \n"
        "| $$$$$$$$      | $$            | $$  | $$  \n"
        "|________/      |__/            |__/  |_$$  \n",

        " /$$             /$$$$$$$$        /$$$$$$  \n"
        "| $$            | $$_____/       //$$__ $$ \n"
        "| $$            | $$$$$         | $$$$$$$$  \n"
        "| $$            | $$__/         | $$__  $$ \n"
        "| $$$$$$$$      | $$            | $$  | $$  \n"
        "|________/      |__/            |__/  |_$$  \n",

        " /$$             /$$$$$$$$        /$$$$$$  \n"
        "| $$            | $$_____/       //$$__ $$ \n"
        "| $$            | $$$$$         | $$$$$$$$  \n"
        "| $$$$$$$       | $$__/         | $$__  $$ \n"
        "|________/      |__/            |__/  |_$$  \n",


        " /$            |$$$$$$$$       /$$$$$$  \n"
        "| $            |$$_____|      //$$__ $$ \n"
        "| $            |$$$$$         |$$$$$$$$  \n"
        "| $$$$$$       |$$__/         |$$__  $$ \n"
        "|_______/      |__/           |__/  |_$$  \n"

    };

    int i = 0;

    sleep(3);
    i = 0;
    std::string espaco = "";
    while(i++ < 5)
    {

        std::cout << espaco + "...HA MUITO TEMPO ATRAS EM UMA DISCIPLINA MUITO DISTANTE DO PRIMEIRO PERIODO...\n";
        sleep(1);
        espaco += "    ";
        system("cls");

    }

    i = 0;
    int j = 20;
    int k = 0;
    while(i++ < 20)
    {

        while(k++ < j) std::cout << "\n";
        if(i < 4)
        {
            std::cout << aed[i-1];
            sleep(1);
        }
        else
        {
            std::cout << aed[4];
            if(i%2)sleep(1);
        }
        system("cls");
        k = 0;
        j--;

    }



    std::string algoritmo =
            "|   _   ||   |    |       ||       ||    _ |  |   | |       ||  |_|  ||       ||       |  \n"
            "|  |_|  ||   |    |    ___||   _   ||   | ||  |   | |_     _||       ||   _   ||  _____|  \n"
            "|       ||   |    |   | __ |  | |  ||   |_||_ |   |   |   |  |       ||  | |  || |_____   \n"
            "|       ||   |___ |   ||  ||  |_|  ||    __  ||   |   |   |  |       ||  |_|  ||_____  |  \n"
            "|   _   ||       ||   |_| ||       ||   |  | ||   |   |   |  | ||_|| ||       | _____| |  \n"
            "|__| |__||_______||_______||_______||___|  |_||___|   |___|  |_|   |_||_______||_______|  \n";
    std::string de =
            "                  \n"
            "|      | |       |\n"
            "|  _    ||    ___|\n"
            "| | |   ||   |___ \n"
            "| |_|   ||    ___|\n"
            "|       ||   |___ \n"
            "|______| |_______|\n";

     std::string autu =
             "|   _   ||  | |  ||       ||       ||  |_|  ||   _   ||       ||       ||       |\n"
             "|  |_|  ||  | |  ||_     _||   _   ||       ||  |_|  ||_     _||   _   ||  _____|\n"
             "|       ||  |_|  |  |   |  |  | |  ||       ||       |  |   |  |  | |  || |_____ \n"
             "|       ||       |  |   |  |  |_|  ||       ||       |  |   |  |  |_|  ||_____  |\n"
             "|   _   ||       |  |   |  |       || ||_|| ||   _   |  |   |  |       | _____| |\n"
             "|__| |__||_______|  |___|  |_______||_|   |_||__| |__|  |___|  |_______||_______|\n";


   std::string fini =
           "|       ||   | |  |  | ||   | |       ||       ||       |  \n"
           "|    ___||   | |   |_| ||   | |_     _||   _   ||  _____|  \n"
           "|   |___ |   | |       ||   |   |   |  |  | |  || |_____   \n"
           "|    ___||   | |  _    ||   |   |   |  |  |_|  ||_____  |  \n"
           "|   |    |   | | | |   ||   |   |   |  |       | _____| |  \n"
           "|___|    |___| |_|  |__||___|   |___|  |_______||_______|  \n";

   i=-1;
   j = 20;
   while(i++ < 4)
   {
       switch (i)
       {
           case 0:
           {
             std::cout << algoritmo << std::endl;
             break;
           }
           case 1:
           {
                std::cout << algoritmo << std::endl;
                std::cout << de << std::endl;
                break;
           }
           case 2:
           {
               std::cout << algoritmo << std::endl;
               std::cout << de << std::endl;
               std::cout << autu << std::endl;
               break;
           }
           case 3:
           {
               std::cout << algoritmo << std::endl;
               std::cout << de << std::endl;
               std::cout << autu << std::endl;
               std::cout << fini << std::endl;
               break;
           }
       }
      sleep(1);
      k = 0;
      system("cls");
   }
}



static mumu::Estado<QString> item; //usada para foreach global
mumu::Estado<QString>& retornaEstadoPorNome(QString nome,QList<mumu::Estado<QString>>*listaDeEstado )
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

void comArquivoAFD()
{

    QT_TRY
    {
        mumu::AFD<QString> automatoDeterministico;
        std::ifstream arquivo;
        std::string a  = "../arquivos/afd.txt";
        arquivo.open(a.c_str());
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
                if(cont == 0)
                {
                    listaNomesAutomatos = QString::fromStdString(linha).split(';');
                }
                else
                {
                    if(cont == 1)
                    {
                        listaAlfabeto = QString::fromStdString(linha).split(';');
                    }
                    else
                    {
                        if(cont == 2)
                        {
                            listaAssociacoes = QString::fromStdString(linha).split(';');
                        }
                        else
                        {
                            if(cont == 3)
                            {
                                listaDeEstadosFinIni  = QString::fromStdString(linha).split(';');
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
            automatoDeterministico.adicionarLetraDoAlfabeto(item);

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
                        if(listaDeEstadosFinIni.at(k + 1) == "EF")
                        {
                            estado.setEhEstadoFinal(true);
                        }
                        else
                        {
                            if(listaDeEstadosFinIni.at(k + 1) == "EI")
                            {
                                estado.setEhEstadoInicial(true);
                            }
                        }

                    }
                }

            }

            //automatoDeterministico.getObjArestaEstado().incluirEstado(estado);
            listaDeEstado->push_back(estado);
        }


        //associação fisica
        for(int i = 0; i < listaDeEstado->count();i++)
        {
            mumu::Estado<QString> estado = listaDeEstado->at(i);
            automatoDeterministico.getObjArestaEstado().incluirEstado(estado);
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

                std::cout << e1.getNome().toStdString()  <<std::endl;
                std::cout << e2.getNome().toStdString()  <<std::endl;
                std::cout << letra.toStdString() <<std::endl;

                automatoDeterministico.getObjArestaEstado().ligarEstado(e1,e2,letra);
            }
            else
            {
                i = i + 1;
            }
        }


        automatoDeterministico.montarAutomato();
        mumu::menuAFD::menuPrinc(automatoDeterministico,listaDeEstado);
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


void mostrarOpcaoMenu()
{
    std::string menu = "";
    menu += "1 - AFD\n";
    menu += "2 - AFD - com arquivo\n";
    menu += "3 - AFND com arquivo\n";
    menu += "4 - AF-Epson com arquivo\n";
    menu += "0 - Sair\n";
    menu += "\n";
    std::cout << menu;
}


template<class T>
void chamaMenu(QString file)
{
    T obj(file);
    obj.obtenhaAutomatoComArquivo();
    obj.menu();
}


int main()
{
    //aberturaFormatoStarWars();

    bool ehFimDePrograma = false;
    char opcao = '0';
    while(!ehFimDePrograma)
    {
        mostrarOpcaoMenu();
        std::cin >> opcao;
        switch (opcao)
        {
            case '0' : ehFimDePrograma = true; break;
            case '1' : mumu::menuAFD::menu();break;
            case '2' : comArquivoAFD();break;
            case '3' : chamaMenu<MenuAFND>("../arquivos/afnd.txt"); break;
            case '4' : chamaMenu<MenuAF_Epson>("../arquivos/afEpson.txt"); break;
        }
    }
}


