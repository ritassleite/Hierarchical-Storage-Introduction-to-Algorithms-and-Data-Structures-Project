/*Autor: Rita Leite, IST nº: 92646
File: main.c
Descriçao:Ficheiro principal para o sistema de armazenaçao de ficheiros.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "functions.h"
#include "hashtables.h"
#include "binarytrees.h"


int main()
{
    file_table * HASHTABLE = init_table(1327);
    int key=0;
    char* var=str_alloc("\0");
    file * root = new_file(str_alloc("\0"),var,0);
    char scanner[7];
    char c;
    HASHTABLE=HTinsert_file(HASHTABLE,root);
    scanf("%s", scanner);
    while(strcmp(scanner, "quit")!=0){
        if(strcmp(scanner,"set")==0){
                Set(HASHTABLE,root, key+1);
                key++;
        }
        else if(strcmp(scanner ,"help")==0){
            help();
        }
        else if(strcmp(scanner, "print")==0){
            print(HASHTABLE, root, root);
        }
        else if(strcmp(scanner, "find")==0){
            Find(HASHTABLE);
        }
        else if(strcmp(scanner, "list")==0){
            c=getchar();
            if(c=='\n'){
                list_without_input(root);
            }
            else{
                list_with_input(HASHTABLE);
            }
        }
        else if(strcmp(scanner, "search")==0){
            Search(HASHTABLE, key);
        }
        else if(strcmp(scanner, "delete")==0){
            c=getchar();
            if(c=='\n'){
                HASHTABLE=delete_all(HASHTABLE);
                root = new_file(str_alloc("\0"),var,0);
                HASHTABLE=HTinsert_file(HASHTABLE,root);

            }
            else{
                delete_paths(HASHTABLE, root);
            }
        }
        scanf("%s", scanner);
    }
    quit(HASHTABLE);
    free(var);
    return 0;
}
