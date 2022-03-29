/*Autor: Rita Leite, IST nº: 92646
File: functions.c
Descriçao: São implementadas as funcoes necessarias para executar os comandos estabelecidos
no enunciado
Teste Pratico: Perguntas 1 e 3*/


#include "functions.h"
#include "structures.h"
#include "hashtables.h"
#include "binarytrees.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Recebe um string <str> e devolve o string correspondente aos carateres a seguir ao ultimo '/' existente em <str>*/
char* last_string(char * str){
    int i=strlen(str);
    int j=i-1;
    char reader[65535];
    char * res;
    while(str[j]!='/'){
        j--;
    }
    j++;
    i=0;
    while(str[j]!='\0'){
        reader[i]=str[j];
        i++;
        j++;
    }
    reader[i]='\0';
    res=malloc(strlen(reader)+1);
    strcpy(res, reader);
    return res;
}

/*Funcao auxiliar para o algoritmo de ordenacao de strings merge sort*/
void mergeNum(char** list, int left, int m, int right){
    int i, j, k, var=right-left+1;
    char** aux=(char**)malloc(sizeof(char*)*var); /*ALTERAR*/
    for (i = m + 1; i > left; i--){
        aux[i-1-left]=str_alloc(list[i-1]);
    }

    for (j = m; j < right; j++){
        aux[right + m - j-left]=str_alloc(list[j+1]);
    }

    for (k = left; k <= right; k++){
        if (strcmp(aux[j-left],aux[i-left])<0){
            list[k]=(char*)realloc(list[k],(strlen(aux[j-left])+1)*sizeof(char));
            strcpy(list[k], aux[j-left]);
            j--;
        }
        else{
            list[k]=(char*)realloc(list[k],(strlen(aux[i-left])+1)*sizeof(char));
            strcpy(list[k], aux[i-left]);
            i++;
        }
    }
    for(i=0;i<var;i++){
        free(aux[i]);
        aux[i]=NULL;
    }
    free(aux);
}

/*Funcao que ordena alfabeticamente as strings em <list> entre as posicoes <l> e <r>,
recorrendo ao algoritmo merge_sort*/
void mergesortNum(char** list, int left, int right){
    int m = (right + left)/2;
    if (right <= left){
        return;
    }
    mergesortNum(list, left , m);
    mergesortNum(list, m + 1, right);
    mergeNum(list, left, m, right);
}


/*Recebe a tabela <table>, o file <root>, e a chave <key>, lê a informacao necessaria
e adiciona ao sistema o file associado à mesma*/
void Set(file_table * table, file * root, int key){
    file * f;
    int counter=0,i;
    char** aux;
    char val[65535], dir[65535];
    char *diretoria, *content;
    scanf("%s %[^\n]s", dir,val);
    diretoria=path_processing(dir);
    content = str_alloc(val);
    f=HTfind_dir(table, diretoria);
    if(f!=NULL){
        if(f->content!=NULL){free(f->content);}
        f->content=content;
        f->chave=key;
    }
    else{
        aux=path_breakdown(diretoria);
        while(aux[counter]!=NULL){
            counter++;
        }
        recursive_set(f,aux,root,table,counter-1,key,content);
        for(i=0;i<=counter;i++){
            free(aux[i]);
        }
    free(aux);
    }
    free(diretoria);

}

/*Imprime os comandos e a sua descricao*/
void help(){
    printf("help: Imprime os comandos disponíveis.\n");
    printf("quit: Termina o programa.\n");
    printf("set: adiciona ou modifica o valor a armazenar.\n");
    printf("print: Imprime todos os caminhos e valore.\n");
    printf("find: Imprime o valor armazenado.\n");
    printf("list: Lista todos os componentes de um caminho.\n");
    printf("search: Procura o caminho dado.\n");
    printf("delete: Apaga um caminho e todos os subcaminhos.\n");
}

/*Lê o caminho introduzido e encontra o ficheiro com essa diretoria*/
void Find(file_table * table){

    file * aux;
    char dir[65535];
    char* diretoria;

    scanf(" %s", dir);

    diretoria=path_processing(dir);
    aux=HTfind_dir(table, diretoria);
    if(aux==NULL){
        printf("not found\n");
    }
    else if(aux->chave==0){
        printf("no data\n");
    }
    else{
        printf("%s\n", aux->content);
    }
    free(diretoria);
}

/*Lê o subcaminho introduzido e imprime por ordem alfabética todas as componentes imediatas deste*/
void list_with_input(file_table * table){
    char dir[65535];
    char ** reader=(char**)malloc(sizeof(char*));
    char** tmp;
    char* aux2;
    int k,j=0;
    file * aux;
    file * sibling;
    scanf("%s", dir);
    aux2=path_processing(dir);
    aux = HTfind_dir(table, aux2);
    if(aux!=NULL){
        sibling=aux->first_child;
        while(sibling!=NULL){
            tmp=(char**)realloc(reader, sizeof(char*)*(j+1));
            k=0;
            while(tmp==NULL){
                tmp=(char**)realloc(reader, sizeof(char*)*(j+k+1));
                k++;
            }
            reader=tmp;
            reader[j]=last_string(sibling->diretoria);
            j++;
            sibling=sibling->next_sibling;
        }
        mergesortNum(reader, k, j-1);
        for(k=j-1;k>=0;k--){
            printf("%s\n", reader[k]);
            free(reader[k]);
        }
    }
    else{
        printf("not found\n");
    }
    free(reader);
    free(aux2);

}

/*Imprime alfabeticamente todos os caminhos imediatos do sistema*/
void list_without_input(file * root){
    int k;
    file * sibling=root->first_child;
    char helper[65535];
    char** reader =(char**)malloc(sizeof(char*));
    char** tmp;
    int i=0, j=0;
    while(sibling!=NULL){
        tmp=(char**)realloc(reader, sizeof(char*)*(j+1));
        k=1;
        while(tmp==NULL){
            tmp=(char**)realloc(reader, sizeof(char*)*(j+k+1));
            k++;
        }
        reader=tmp;
        reader[j]=str_alloc(sibling->diretoria);
        j++;
        sibling=sibling->next_sibling;
    }
    mergesortNum(reader, 0, j-1);
    for(i=j-1;i>=0;i--){
        for(k=1;reader[i][k]!='\0';k++){
            helper[k-1]=reader[i][k];
        }
        helper[k-1]='\0';
        printf("%s\n", helper);
        free(reader[i]);
    }
    free(reader);

}

/*Lê um valor e imprime o primeiro caminho criado com o valor indicado*/
void Search(file_table * table, int key){
    char val[65535];
    char * value;
    file * f;
    scanf(" %[^\n]s", val);
    value=str_alloc(val);
    f=HTfind_content(table, value, key);
    if(f==NULL){
        printf("not found\n");
    }
    else{
        printf("%s\n", f->diretoria);
    }
    free(value);
}

/*Lê um subcaminho e apaga do sistema todos os files com caminhos que contêm este subcaminho, libertando a memoria associada*/
void delete_paths(file_table * table, file * root){
    char dir[65535];
    char* diretoria;
    file * current;
    scanf("%s", dir);
    diretoria=path_processing(dir);
    current=HTfind_dir(table,diretoria);
    if(current==NULL){
        printf("not found\n");
    }
    else{
        remove_from_tree(current, root, table);
    }
    free(diretoria);
}

/*Apaga todos os files do sistema*/
file_table * delete_all(file_table * table){
    file_table * empty_table;
    int size = table->size;
    delete_Hashtable(table);
    empty_table=init_table(size);

    return empty_table;
}

/*Imprime a diretoria e content de todos os files no sistema por ordem de criacao em profundidade*/
void print(file_table * table, file * f, file * root){
    if(f->chave!=0){
        printf("%s %s\n",f->diretoria ,f->content);
    }
    if(f==root){
        print(table,find_last_child(root), root);
    }
    else{
        if(find_last_child(f)!=NULL){
            print(table, find_last_child(f),root);
        }
        if(find_prev_sibling(f,find_parent(f, table))!=NULL){
            print(table, find_prev_sibling(f, find_parent(f,table)),root);
        }
    }
}

/*Liberta toda a memoria ocupada e termina o programa*/
void quit(file_table * table){
    delete_Hashtable(table);
}
