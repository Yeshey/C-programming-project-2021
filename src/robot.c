#include <stdio.h>
#include <string.h>
#include "header.h"
#include "utils.h"

void robot(char * saveinput,pTable ptable,pmaxplays pmaxplays){
    int i=0,j=0;
    int l = intUniformRnd(0, ptable->nlin);
    int c = intUniformRnd(0, ptable->ncol);
    int numoccupied=0;
    int numwithredorS=0;
    for (i = 0; i < ptable->nlin; i++){
        for (j = 0; j < ptable->ncol; j++){
            if (ptable->table[i][j]!=' ')
                numoccupied++; } }
    for (i = 0; i < ptable->nlin; i++){
        for (j = 0; j < ptable->ncol; j++){
            if (ptable->table[i][j]=='R' || ptable->table[i][j]=='S')
                numwithredorS++; } }
    float squares = ptable->nlin*ptable->ncol;
    float possibleplays = (squares-numoccupied)+(squares-numwithredorS)+pmaxplays->addlcB;
    if (probEvento((float)(possibleplays-numwithredorS)/possibleplays) || (pmaxplays->addlcB==0 && pmaxplays->RockB==0) ){
        //places Piece
        saveinput[1]=',';
        saveinput[0]=l+'0';
        saveinput[2]=c+'0';
    } else {
        if (probEvento((float)(possibleplays-numoccupied)/possibleplays)==1 || pmaxplays->addlcB==0){
            //places Stone
            saveinput[1]=',';
            saveinput[0]=l+'0';
            saveinput[2]=c+'0';
            saveinput[3]=c+'0';
        } else {
            if (probEvento(0.5)==1){
                saveinput[0]='L';
                saveinput[1]='\n';
                saveinput[2]='\0';
            } else{
                saveinput[0]='C';
                saveinput[1]='\n';
                saveinput[2]='\0';
            }
        }
    }
    return;
}

int isrobotplayin(int turn,int robot1){
    int false = 0;
    int true = 1;
    int answer=false;
    if (turn%2==0 && robot1==1)
        answer=true;
    return answer;
}