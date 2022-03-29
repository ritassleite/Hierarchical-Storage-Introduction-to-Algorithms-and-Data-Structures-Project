/*Autor: Rita Leite, IST nº: 92646
File: hashtables.h
Descriçao:Ficheiro Header para <hashtables.c>, onde é implementada a tabela de dispersão por encadeamento externo*/

#ifndef HASHTABLES_H_INCLUDED
#define HASHTABLES_H_INCLUDED
#include "structures.h"

/*Estrutura de uma tabela de dispersao por encadeamento externo com tamanho <size> e ocupação <full>*/
typedef struct hashtable{
    file_node * heads;
    int size;
    int full;
} file_table;

/*Função de dispersão para strings*/
int Hash(char *s, int M);

/*Cria e aloca memoria para uma tabela de dispersao por encadeamento externo*/
file_table * init_table(int M);

/*Insere um novo file na tabela*/
file_table  * HTinsert_file(file_table * table, file * f);

/*Remove o file com diretoria <dir> da tabela*/
file_table  * HTremove_file(file_table * table, char * dir);

/*Encontra o file com diretoria <dir> na tabela, devolvendo o mesmo no caso de ele existir
e NULL c.c.*/
file * HTfind_dir(file_table * table, char * dir);

/*Encontra o primeiro file criado com content <val> na tabela, devolvendo o mesmo no caso de ele existir
e NULL c.c..*/
file * HTfind_content(file_table * table, char * val, int key);

/*Apaga a tabela <table> e liberta a memoria associada*/
void delete_Hashtable(file_table * table);


#endif
