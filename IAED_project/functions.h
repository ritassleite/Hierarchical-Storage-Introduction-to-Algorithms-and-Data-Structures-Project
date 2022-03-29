/*Autor: Rita Leite, IST nº: 92646
File: functions.h
Descriçao:Ficheiro Header para <functions.c>*/

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "structures.h"
#include "hashtables.h"

/*Recebe um string <str> e devolve o string correspondente aos carateres a seguir ao ultimo '/' existente em <str>*/
char* last_string(char * str);

/*Funcao auxiliar para o algoritmo de ordenacao de strings merge sort*/
void mergeNum(char** list, int r, int l, int mid);

/*Funcao que ordena alfabeticamente as strings em <list> entre as posicoes <l> e <r>,
recorrendo ao algoritmo merge_sort*/
void mergesortNum(char** list, int l, int r);

/*Recebe a tabela <table>, o file <root>, e a chave <key>, lê a informacao necessaria
e adiciona ao sistema o file associado à mesma*/
void Set(file_table * table, file * root, int key);

/*Imprime os comandos e a sua descricao*/
void help();

/*Lê o caminho introduzido e encontra o ficheiro com essa diretoria*/
void Find( file_table * table);

/*Lê o subcaminho introduzido e imprime por ordem alfabética todas as componentes imediatas deste*/
void list_with_input(file_table * table);

/*Imprime alfabeticamente todos os caminhos imediatos do sistema*/
void list_without_input( file * root);

/*Lê um valor e imprime o primeiro caminho criado com o valor indicado*/
void Search(file_table * table, int key);

/*Lê um subcaminho e apaga do sistema todos os files com caminhos que contêm este subcaminho, libertando a memoria associada*/
void delete_paths(file_table * table, file * root);

/*Apaga todos os files do sistema*/
file_table * delete_all(file_table * table);

/*Imprime a diretoria e content de todos os files no sistema por ordem de criacao em profundidade*/
void print(file_table * table, file * f, file * root);

/*Liberta toda a memoria ocupada e termina o programa*/
void quit(file_table * table);


#endif
