#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "header.h"

void freememory(pTable ptable,pdata list){
    freelist(list);
    freearray(ptable);
}

void freelist(pdata list){
    pdata aux;
    while(list != NULL){
        aux = list;
        list = list->prox;
        free(aux);
    }
}

void freearray(pTable ptable){
    int i;
    for (i = 0; i < ptable->nlin; i++){
        free(ptable->table[i]);
    }
    free(ptable->table);
}

pTable summon2Darray(pTable ptable,pdata list){
    //declare bidimensional array ----------
    int i=0,j=0;
    ptable->table = malloc(ptable->nlin*sizeof(char*));
    if(ptable->table==NULL){
        printf("error in malloc1\n");
        end_game(ptable, list);
        //skips everything and returns 0
    }
    for (i = 0; i < ptable->nlin; i++){
        ptable->table[i] = malloc(ptable->nlin*sizeof(char));
        if (ptable->table[i] == NULL){
            printf("error in malloc2\n");
            end_game(ptable, list);
        }
    }
    for (i = 0; i < ptable->nlin; i++){
        for (j = 0; j < ptable->ncol; j++){
            ptable->table[i][j]=' ';
        }
    }
    return ptable;
    //declare bidimensional array ----------
}

void addline(pTable ptable,pdata new){
    int i=0,j=0;
    char ** aux;
    ptable->nlin++;
    aux = realloc(ptable->table,sizeof(char*)*ptable->nlin);
    if(aux==NULL){
        printf("error in realloc\n");
        end_game(ptable,new);
    } else {
        aux[ptable->nlin-1] = malloc(sizeof(char)*ptable->ncol);
        if(aux[ptable->nlin-1]==NULL){
            printf("error\n");
            end_game(ptable,new);
        }
        for (i = 0; i < ptable->ncol; i++){
            aux[ptable->nlin-1][i]=' ';
        }
        ptable->table=aux;
    }
}

void addcolumn(pTable ptable,pdata new){
    int i=0,j=0;
    char * aux;
    ptable->ncol++;
    for (i = 0; i < ptable->nlin; i++){
        aux = realloc(ptable->table[i],sizeof(char)*ptable->ncol);
        if(aux==NULL){
            printf("error\n");
            end_game(ptable,new);
        } else {
            ptable->table[i][ptable->ncol-1]=' ';
            ptable->table[i]=aux;
        }
    }
}

pTable rebuild2Darray(pTable ptable,pdata list,int initdim,int * turn){
    ptable->nlin = ptable->ncol = initdim;
    printf(" initdim = %d\n", initdim);
    ptable = summon2Darray(ptable,list);
    while (list!=NULL){
        if(list->playtype!=0){
            (*turn)++;
            updatetablearray(ptable,list);
        }
        list = list -> prox; // o ponteiro da esquerda fica a apontar para o ponteiro da direita
    }
    printf("Previous game successfuly loaded\n");
    return ptable;
}

void rewindx(pTable ptable,pdata list,int x,int initdim,int turn){
    int count = 0;
    Table auxmeattable;
    pTable auxptable = &auxmeattable;
    auxptable->table=NULL;
    auxptable->ncol=initdim;
    auxptable->nlin=initdim;
    auxptable = summon2Darray(auxptable,list);
    printf("----------------------------Previous Tabel States----------------------------\n");
    if (x>=turn-1)
        printf("printing all previous table states\n");
    else 
        printf("printing %d previous table states\n",x);
    while (list!=NULL){
        if(list->playtype!=0){
            updatetablearray(auxptable,list);
            if (count >= (turn-1)-x){
                tableprint(auxptable);
            }
            count++;
        }
        list = list -> prox;
    }
   freearray(auxptable);
    printf("----------------------------Previous Tabel States----------------------------\n");
    return;
}