/*Autor: Rita Leite, IST nº: 92646
File: binarytrees.h
Descriçao:Ficheiro header para <binarytrees.c>*/


#ifndef BINARYTREES_H_INCLUDED
#define BINARYTREES_H_INCLUDED

/*Recebe um file <f> e devolve um file tal cuja diretoria é o maior subcaminho
da diretoria de <f>*/
file * find_parent(file * f, file_table * table);

/*Encontra e devolve o ultimo file criado cuja diretoria tem como maior subcaminho
a diretoria de <f>*/
file * find_last_child(file * f);

/*Recebe um file <f> e devolve o file cujo next_sibling é <f> se este existir
e NULL c.c.*/
file * find_prev_sibling(file * f, file * parent);

/*Recebe um file <f> e apaga f e todos os files existentes na arvore à direita e para
baixo de <f>, libertando toda a memoria associada*/
void delete_underlings(file * f, file_table * table);

/*Retira da arvore com inicio em <root> o file <f> assim como todos os que estão à sua direita e para baixo*/
void remove_from_tree(file * f, file * root, file_table * table);
char** path_breakdown(char* path);
char * path_processing(char* path);
void recursive_set(file * child, char ** dir, file * root, file_table * table, int i, int key, char* content);
#endif
