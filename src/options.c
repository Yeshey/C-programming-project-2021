#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

pdata playoptions(pTable ptable, pdata list,pmaxplays pmaxplays,int turn,int robot1,int initdim){
    int option1=1;
    int x=0;
    int tmp=0,goback;
    char saveinput[7];
    int inlin=0,incol=0;
    pdata new,aux;
    int i;
    int c;
    do{
    goback=0;
    tmp=0;
    if (!(turn%2==0 && robot1==1)){
    printf("Choose: Play(1), See previous Table states:(2), Pause(3), Help(4)\n 1/2/3/4 -> ");
        do{
            if (tmp!=0)
                printf(" 1/2/3/4 -> ");
            scanf("%d",&option1);
            while((c = getchar()) != '\n' && c != EOF)
            /* discard */ ;
            tmp=1;
        } while (option1!=1 && option1!=2 && option1!=3 && option1!=4);
    }
    switch (option1){
        case 1: 
            if (isrobotplayin(turn,robot1)==0)
                printf("Play:\n");

            new = malloc(sizeof(data));
            if(new==NULL){
                printf("error in malloc");
                end_game(ptable,list);
            }
            //input
            do{
                (*new).playtype = 0;
                if (!(turn%2==0 && robot1==1)){
                    fgets(saveinput,7,stdin);
                } else
                    robot(saveinput,ptable,pmaxplays);
                (*new).playtype = interpretplay(saveinput, &(*new).l, &(*new).c, pmaxplays, turn, ptable,robot1);
                if((*new).playtype==0 && isrobotplayin(turn,robot1)==0){
                    printf("\terror in input, try again\n");
                    //while((c = getchar()) != '\n' && c != EOF);
                }
            } while ((*new).playtype==0 );
            (*new).prox=NULL;
            //incert in end: (better to save just play)
            if(list==NULL){
                list=new;
            } else {
                aux=list;
                while(aux->prox != NULL)
                    aux=aux->prox;
                aux->prox=new;
            }         
            updatetablearray(ptable, new);  
            int j=0;
        break;

        case 2: 
            printf("See previous Table states:\nHow many previous Table states do you wish to see? ");
            tmp = 0;
            do{
                if(tmp!=0)
                    printf("error\n");
                scanf("%d", &x);
                while((c = getchar()) != '\n' && c != EOF);
                tmp=1;
            } while (x < 0);
            rewindx(ptable,list,x,initdim,turn);
            goback=1;
        break;

        case 3: 
            printf("Pause\n");
            pause(ptable,list,robot1,initdim,pmaxplays);
        break;

        case 4:
            printf("\tHow to play:\nValid inputs:\n\nline,column - Places the apropriate piece in the square with the given coordinates if possible\nExample: 1,2\tplaces piece in the first line second column\n\n");
            printf("line,columnS - Places a stone in the square with the given coordinates if possible (max one per player)\nExample: 1,2S\tplaces rock in the first line second column\n\n");
            printf("C - Adds a column,\nL - Adds a line\n\t each player can play one of these two options twice per game\n\n");
            printf("Objective: compleate a line, column or diagonal of the same color (diagonal are only possible on square tables)\n");
            goback=1;
        break;
        default:
            printf("error code 910");
    }
    } while (goback!=0);

    return list;
}

void updatetablearray(pTable ptable, pdata new){
    char ** aux = NULL;
    int i = 0;
    int j=0;
    switch (new->playtype)
    {
    case 0:
        break;
    case 1: // play type 1,2
        switch (ptable->table[new->l][new->c])
        {
        case ' ':
            ptable->table[new->l][new->c]='G';
            break;
        case 'G':
            ptable->table[new->l][new->c]='Y';
            break;
        case 'Y':
            ptable->table[new->l][new->c]='R';
            break;
        default:
        printf("error code 209\n");
            break;
        }
        break;
    case 2: // play type 1,2P
        ptable->table[new->l][new->c]='S';
        break;
    case 3: // play type C
        addcolumn(ptable,new);
        break;
    case 4: // play type L
        addline(ptable,new);
        break;
    default:
    printf("error code 143\n");
        break;
    }
}

int interpretplay(char * str,int * inlin, int * incol,pmaxplays pmaxplays,int turn, pTable ptable,int robot1){
    char player = whosplaying(turn);
    int tmp=0;
    *inlin = -1;  //to convert number in char form to int
    *incol = -1;
    if (strlen(str)<=2){
        if (str[0]=='C' || str[0]=='c'){  //C
            if (player=='A'){
                if (pmaxplays->addlcA>0){
                    (pmaxplays->addlcA)--;
                    tmp=3;
                } else 
                    if (isrobotplayin(turn,robot1)==0)
                        printf("You've exhausted your capacity to alter the table\n");
            } else {
                if (pmaxplays->addlcB>0){
                    (pmaxplays->addlcB)--;
                    tmp=3;
                } else
                    if (isrobotplayin(turn,robot1)==0)
                        printf("You've exhausted your capacity to alter the table\n");
            }
        }
        if (str[0]=='L' || str[0]=='l'){ //L
            if (player=='A'){
                if (pmaxplays->addlcA>0){
                    (pmaxplays->addlcA)--;
                    tmp=4;
                } else 
                    if (isrobotplayin(turn,robot1)==0)
                        printf("You've exhausted your capacity to alter the table\n");
            } else {
                if (pmaxplays->addlcB>0){
                    (pmaxplays->addlcB)--;
                    tmp=4;
                } else
                    if (isrobotplayin(turn,robot1)==0)
                        printf("You've exhausted your capacity to alter the table\n");
            }
        }
    } else if (             //1,2
        isdigit(str[0])!=0 &&
        (
            str[1]==',' ||
            str[1]==' '
        ) &&
        isdigit(str[2])!=0 && 
        strlen(str)<=4 &&
        (str[0] - '0')<ptable->nlin &&
        (str[2] - '0')<ptable->ncol
    ){
        if (ptable->table[(str[0] - '0')][(str[2] - '0')] != 'R' && ptable->table[(str[0] - '0')][(str[2] - '0')] != 'S'){
            *inlin = str[0] - '0';  //to convert number in char form to int
            *incol = str[2] - '0';
            tmp=1;
        } else {
            if (isrobotplayin(turn,robot1)==0)
                printf("invalid cell - ");
        }
    } else if (             //1,2P
        isdigit(str[0])!=0 &&
        (
            str[1]==',' ||
            str[1]==' '
        ) &&
        isdigit(str[2])!=0 &&
        (
            str[3]=='S' ||
            str[3]=='s'
        ) && 
        strlen(str)<=5 &&
        (str[0] - '0')<ptable->nlin &&
        (str[2] - '0')<ptable->ncol
    ){
        if (ptable->table[(str[0] - '0')][(str[2] - '0')] == ' '){ //test if cell's free
            if (player=='A'){
                if (pmaxplays->RockA >0){   //test if maximum number of stones' been reached
                    *inlin = str[0] - '0';  //to convert number in char form to int
                    *incol = str[2] - '0';
                    (pmaxplays->RockA)--;
                    tmp=2;
                } else 
                    if (isrobotplayin(turn,robot1)==0)
                        printf("Maximum Number of thrown Stones reached!\n");
            } else {
                if (pmaxplays->RockB >0){   //test if maximum number of stones' been reached
                    *inlin = str[0] - '0';  //to convert number in char form to int
                    *incol = str[2] - '0';
                    (pmaxplays->RockB)--;
                    tmp=2;
                } else
                    if (isrobotplayin(turn,robot1)==0)
                        printf("Maximum Number of thrown Stones reached!\n");
            }
        } else {
            if (isrobotplayin(turn,robot1)==0)
                printf("invalid cell - ");
        }
    }
    /*
    return 0 if invalid
    return 1 if is type 1,2
    return 2 if is type 1,2S
    return 3 if is type C
    return 4 if is type L
    // return 5 if is type B (back)
    */
   return tmp;
}

char whosplaying(int turn){
    return (turn%2 ? 'A' : 'B');
}