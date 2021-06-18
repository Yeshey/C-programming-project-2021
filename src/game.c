#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "header.h"

void gameturn(pTable ptable, pdata list,pmaxplays pmaxplays,int robot1,int initdim,int turn){
    do{
        printf("Turn %d, player: %c\n",turn,whosplaying(turn));
        tableprint(ptable);
        list = playoptions(ptable,list,pmaxplays,turn,robot1,initdim);
        turn++;
    } while (winner(ptable)!=0);

    tableprint(ptable);
    printf("player %c won!\n",whosplaying(turn));
    totext(list,robot1);
    deactivatefichbin();

    freememory(ptable, list);
}

int winner(pTable ptable){
    int i=0,j=0;
    int line = 1;
    //Test Lines:
    for (i = 0; i < ptable->nlin; i++){
        for (j = 1; j < ptable->ncol; j++){
            if(ptable->table[i][j] == ptable->table[i][j-1] && ptable->table[i][j]!=' '){
                line++;
            }
        }
        if (line==ptable->ncol)
            return 0;
        line=1;
    }
    //Test Columns:
    for (i = 0; i < ptable->ncol; i++){
        for (j = 1; j < ptable->nlin; j++){
            if(ptable->table[j][i] == ptable->table[j-1][i] && ptable->table[j][i]!=' '){
                line++;
            }
        }
        if (line==ptable->nlin)
            return 0;
        line=1;
    }
    //Diagonals
    j = 1;  
    if (ptable->ncol == ptable->nlin){
        for (i = 1; i < ptable->nlin; i++){
            if(ptable->table[i][i] == ptable->table[i-1][i-1] && ptable->table[i][i]!=' '){
                line++;     //Left to Right Diagonals
            }
            if(ptable->table[i][ptable->ncol-1-i] == ptable->table[i-1][ptable->ncol-i] && ptable->table[i][ptable->ncol-1-i]!=' '){
                j++;        //Right to Left Diagonals
            }
        }
        if (line==ptable->nlin || j==ptable->nlin)
            return 0;
    }
}

void end_game(pTable ptable,pdata list){
    freememory(ptable,list);
    exit(0); //skips everything and returns 0
}