/*Autor: Rita Leite, IST nº: 92646
File: structures.c
Descriçao:São aqui implementadas as funcoes necessárias para manipulação da estrutura file e listas ligadas*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "structures.h"

/*Aloca memória para o string <str>*/
char * str_alloc(char * str){

    char *res= (char*) malloc(sizeof(char)*(strlen(str)+1));
    strcpy(res, str);
    return res;
}

/*Cria um novo file, alocando memória para o mesmo*/
file* new_file(char* value, char* dir, int chave)
{
    file * x = malloc(sizeof(file));
    x->content= value;
    x->diretoria= str_alloc(dir);
    x->first_child = NULL;
    x->next_sibling = NULL;
    x->chave=chave;
    return x;
}

/*Apaga um file do sistema, e limpa a memória associada ao mesmo*/
void delete_file(file * f){

    free(f->diretoria);

    free(f->content);

    free(f);

}

/*Cria um novo node para guardar um file*/
file_node new_node(file *f){
    struct node *n=(file_node)malloc(sizeof(struct node));
    n->item = f;
    return n;
}

/*Insere um node ao início de uma lista ligada que começa no node <head>*/
file_node insert_node(file_node head, file * f){
    file_node newhead = new_node( f);
    newhead->prox = head;
    return newhead;
}


/*Encontra o file que guarda o conteudo <content> na lista ligada
com inicio em <head>*/
file_node find_content(file_node head, char* content){
    file_node aux = head;
    while(aux!= NULL){
        if(aux->item->content==NULL){
            aux=aux->prox;
        }
        else if (strcmp(aux->item->content, content) == 0){
            break;
        }
        else{
            aux = aux->prox;
        }
    }
    return aux;
}

/*Encontra o file com a diretoria associada igual a <dir> na lista ligada
com inicio em <head>*/
file_node find_dir(file_node head, char* dir){
    file_node aux = head;
    while(aux!= NULL){
        if (strcmp(aux->item->diretoria, dir) == 0){
            break;
        } else{
            aux = aux->prox;
        }
    }
    return aux;
}

/*Retira o file com diretoria <dir> da lista ligada com inicio em <head>,
libertando a memória associada ao mesmo*/
file_node remove_node(file_node head, char* dir){
    file_node aux, prev;
    for (aux = head, prev = NULL; aux != NULL; prev = aux, aux = aux->prox){
        if (strcmp(aux->item->diretoria, dir) == 0){
            if (aux == head){
                head = aux->prox;
            }
            else{
                prev->prox = aux->prox;
            }
            delete_file(aux->item);
            free(aux);
            break;
        }
    }
    return head;
}

/*Apaga todos os files na lista ligada com inicio em <head>*/
void remove_all(file_node head){
    file_node aux;
    while (head != NULL){
        aux = head->prox;
        delete_file(head->item);
        free(head);
        head = aux;
    }
}




