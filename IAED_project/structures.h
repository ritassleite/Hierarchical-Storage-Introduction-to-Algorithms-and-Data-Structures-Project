/*Autor: Rita Leite, IST nº: 92646
File: structures.h
Descriçao:Ficheiro Header para <structures.c>, onde são implementadas as estruturas para ficheiros e listas ligadas que os contêm*/


#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

/*Define file como a estrutura que contém a <diretoria> (caminho associado a este), o seu valor associado <content>,
 a sua <chave> (correspondente ao momento de adição de um valor ao mesmo), <first_child> (o primeiro file cujo caminho
associado tem como maior subcaminho a <diretoria>), e <next_sibling> (correspondente ao seguinte ficheiro com os mesmos subcaminhos que o file atual)*/
typedef struct ficheiro{
    int chave;
    char* content;
    char* diretoria;
    struct ficheiro * first_child;
    struct ficheiro * next_sibling;
} file;


/* Implementa a estrutura de um node para a criação das listas ligadas */
typedef struct node{
    file * item;
    struct node * prox;
} *file_node;

/*Aloca memória para o string <str>*/
char * str_alloc(char * str);

/*Cria um novo file, alocando memória para o mesmo*/
file * new_file(char* value, char* pos, int chave);

/*Apaga um file do sistema, e limpa a memória associada ao mesmo*/
void delete_file(file * f);

/*Cria um novo node para guardar um file*/
file_node new_node(file *f);

/*Insere um node ao início de uma lista ligada que começa no node <head>*/
file_node insert_node(file_node head, file * f);

/*Encontra o file que guarda o conteudo <content> na lista ligada
com inicio em <head>*/
file_node find_content(file_node head, char* content);

/*Encontra o file com a diretoria associada igual a <dir> na lista ligada
com inicio em <head>*/
file_node find_dir(file_node head, char* dir);

/*Retira o file com diretoria <dir> da lista ligada com inicio em <head>,
libertando a memória associada ao mesmo*/
file_node remove_node(file_node head, char* dir);

/*Apaga todos os files na lista ligada com inicio em <head>*/
void remove_all(file_node head);




#endif
