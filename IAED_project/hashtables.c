/*Autor: Rita Leite, IST nº: 92646
File: hashtables.h
Descriçao:São implementadas as funcoes necessarias para manipulacao de tabelas de dispersao*/

#include "hashtables.h"
#include "structures.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*Função de dispersão para strings*/
int Hash(char *s, int M){
    int h = 0, a = 127;
    for (; *s != '\0'; s++){
        h = (a*h + *s) % M;
    }
    return h;
}

/*Cria e aloca memoria para uma tabela de dispersao por encadeamento externo de tamanho <size>*/
file_table * init_table(int size){
    int i;
    file_table * table =(file_table*) malloc(sizeof(file_table));
    table->heads = (file_node*)malloc(size*sizeof(file_node));
    for (i = 0; i < size; i++){
        table->heads[i] = NULL;
    }
    table->size = size;
    table->full = 0;
    return table;
}

/*Insere um novo file na tabela*/
file_table  * HTinsert_file(file_table * table, file * f){
    int i = Hash(f->diretoria, table->size);
    table->heads[i] = insert_node(table->heads[i], f);
    table->full++;
    return table;
}

/*Remove o file com diretoria <dir> da tabela*/
file_table  * HTremove_file(file_table * table, char * dir){
    int i = Hash(dir, table->size);
    table->heads[i] = remove_node(table->heads[i], dir);
    table->full--;
    return table;
}


/*Encontra o file com diretoria <dir> na tabela, devolvendo o mesmo no caso de ele existir
e NULL c.c.*/
file * HTfind_dir(file_table * table, char * dir){
    int i = Hash(dir, table->size);
    file_node aux = find_dir(table->heads[i], dir);
    if(aux == NULL){
        return NULL;
    }
    return aux->item;
}

/*Encontra o primeiro file criado com content <val> na tabela, devolvendo o mesmo no caso de ele existir
e NULL c.c..*/
file * HTfind_content(file_table * table, char * val, int key){
    int i;
    file_node aux;
    file_node res=NULL;
    for(i=0; i<table->size;i++){
        aux = find_content(table->heads[i], val);
        if(aux!=NULL){
            if(aux->item->chave<=key){
                res=aux;
                key=aux->item->chave;
            }
        }
    }
    if(res == NULL){
        return NULL;
    }
    return res->item;
}

/*Apaga a tabela <table> e liberta a memoria associada*/
void delete_Hashtable(file_table * table){
    int i;
    for (i = 0; i < table->size; i++){
        if (table->heads[i] != NULL){
            remove_all(table->heads[i]);
        }
    }
    free(table->heads);
    free(table);
}


