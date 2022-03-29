/*Autor: Rita Leite, IST nº: 92646
File: binarytrees.c
Descriçao:São implementadas as funcoes necessarias para manipular a arvore de ficheiros criada.*/


#include "functions.h"
#include "structures.h"
#include "hashtables.h"
#include "binarytrees.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Recebe um file <f> e devolve um file tal cuja diretoria é o maior subcaminho
da diretoria de <f>*/
file * find_parent(file * f, file_table * table){
    int len=0;
    int i;
    file * parent;
    char** path_break=path_breakdown(f->diretoria);
    while(path_break[len]!=NULL){
        len++;
    }
    if(len<=1){
        free(path_break[0]);
    free(path_break);
        return NULL;
    }
    else{
        parent=HTfind_dir(table, path_break[len-2]);
        for(i=0;i<len;i++){
            free(path_break[i]);
        }
        free(path_break);
        return parent;
    }

}


/*Encontra e devolve o ultimo file criado cuja diretoria tem como maior subcaminho
a diretoria de <f>*/
file * find_last_child(file * f){
    file * sibling;
    if(f!=NULL){
        if(f->first_child==NULL){
            return NULL;
        }
        else{
            sibling=f->first_child;
            while(sibling->next_sibling!=NULL){
                sibling=sibling->next_sibling;
            }
            return sibling;
        }
    }
    return NULL;
}

/*Recebe um file <f> e devolve o file cujo next_sibling é <f> se este existir
e NULL c.c.*/
file * find_prev_sibling(file * f, file * parent){
    file * sibling;
    if(parent!=NULL){
        if(parent->first_child==NULL || parent->first_child==f){
            return NULL;
        }
        else{
            sibling=parent->first_child;
            while(sibling->next_sibling!=f){
                if(sibling->next_sibling==NULL){
                    return NULL;
                }
                sibling=sibling->next_sibling;
            }
            return sibling;
        }
    }
    else{
        return NULL;
    }
}

/*Recebe um file <f> e apaga f e todos os files existentes na arvore à direita e para
baixo de <f>, libertando toda a memoria associada*/
void delete_underlings(file * f, file_table * table){
    file * child;
    file * sibling;
    if(f==NULL){
        return;
    }
    child = f->first_child;
    sibling = f->next_sibling;
    table=HTremove_file(table, f->diretoria);
    if(sibling!=NULL){
        delete_underlings(sibling, table);
    }
    if(child!=NULL){
        delete_underlings(child, table);
    }
}

/*Retira da arvore com inicio em <root> o file <f> assim como todos os que estão à sua direita e para baixo*/
void remove_from_tree(file * f, file * root, file_table * table){
    file * parent=find_parent(f,table);
    file * sibling;
    delete_underlings(f->first_child, table);
    if(parent==NULL){
        parent=root;
    }
    sibling=find_prev_sibling(f, parent);
    if(sibling==NULL){
        if(f->next_sibling!=NULL){
            parent->first_child=f->next_sibling;
        }
        else{
            parent->first_child=NULL;
        }
    }
    else{
        if(f->next_sibling!=NULL){
            sibling->next_sibling=f->next_sibling;
        }
        else{
            sibling->next_sibling=NULL;
        }
    }
    f->next_sibling=NULL;
    f->first_child=NULL;
    table=HTremove_file( table, f->diretoria);/*!!!*/
}

/*Recebe um caminho e devolve uma lista com todos os subcaminhos do mesmo*/
char** path_breakdown(char* path){
    int i;
    int j=0;
    int s;
    int counter=0;
    char** map;
    char reader2[65535]; /*pode se alterar no futuro*/
    for(s=0; path[s]!='\0';s++){
        if(path[s]=='/'){
                counter++;
        }
    }

    map=(char**)malloc(sizeof(char*)*(counter+1));
    for(i=0;i<counter+1;++i){
        if(path[j]=='\0'){
                break;}
        reader2[j]='/';
        j++;
        while(path[j]!='\0' && path[j]!='/'){
            reader2[j]=path[j];
            j++;
        }
        reader2[j]='\0';
        map[i]=(char*)malloc(sizeof(char)*(strlen(reader2)+1));
        strcpy(map[i], reader2);
        map[counter]=NULL;
    }

    return map;
}

/*Recebe um caminho, e altera-o com objetivo de obedecer às guidelines fornecidas
no enunciado*/
char * path_processing(char* path){
    int i=0;
    int j=0;
    char * reader3=(char*)malloc(strlen(path)+2);
    reader3[0]='/';
    while( path[j]!='\0'){
        while(path[j]=='/'){
            j++;
            reader3[i]='/';
        }
        i++;
        while(path[j]!='/' && path[j]!='\0'){
            reader3[i]=path[j];
            i++;
            j++;
        }
    }
    if(reader3[i-1]=='/'){
        reader3[i-1]='\0';
    }
    else{
        reader3[i]='\0';}
    return reader3;
}

/*Funcao recursiva utilizada para adicionar à arvore e à tabela todos os files com diretorias na lista <dir>, utlizada para auxiliar o
comando set*/
void recursive_set(file * child, char ** dir, file * root, file_table * table, int i, int key, char* content){
    file * f=new_file(content,dir[i],key);
    file * parent;
    table=HTinsert_file(table ,f);
    f->first_child=child;
    if(i!=0){
        parent=find_parent(f,table);
        if(parent!=NULL){
            if(find_last_child(parent)!=NULL){
                find_last_child(parent)->next_sibling=f;
            }
            else{
                parent->first_child=f;
            }
        }
        else{
            recursive_set(f, dir, root,table,i-1,0,NULL);
        }
    }
    else{
        if(find_last_child(root)!=NULL){
            find_last_child(root)->next_sibling=f;
        }
        else{
            root->first_child=f;
        }
    }
}

