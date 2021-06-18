#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "header.h"

void initializer(){
    int option1;
    int tmp=0,c,initdim,turn=1;
    char loadopt='N';
    maxplays maxplays;
    pmaxplays pmaxplays = &maxplays;
    pmaxplays->addlcA=2,pmaxplays->addlcB=2;
    pmaxplays->RockA=1,pmaxplays->RockB=1;
    Table table;
    pTable ptable = &table;
    ptable->table=NULL;
    pdata list = NULL,listaux = NULL,listaux2 = NULL, pnew=NULL; // declare the connected list and friends

    // Verify if we have to load the fich.bin
    FILE * fp = fopen("fich.bin","rb");
    if (fp == NULL){ fclose(fp); printf("error opening file, exiting\n"); exit(0); };
    fread(&tmp,sizeof(int),1,fp);
    if (tmp == 1){
        printf("A fich.bin file with valid data has bin found, do you wish to load the previous game?(Y/N)");
        tmp=0;
        do{
            if (tmp!=0)
                printf("error in input\n");
            scanf("%c",&loadopt);
            while((c = getchar()) != '\n' && c != EOF) ;
            tmp=1;
        } while (loadopt!='Y' && loadopt!='N');
    }
    if(loadopt=='Y'){   // Load fich.bin:
        fread(&option1, sizeof(int), 1, fp);
        fread(&initdim,sizeof(initdim),1,fp);
        fread(pmaxplays,sizeof(maxplays),1,fp);
        tmp=0;
        do{
            pnew = malloc(sizeof(data));
            if(pnew==NULL){ end_game(ptable,list); }
            pnew->playtype=0;
            if(tmp==0)
                list = pnew;
            else
                listaux->prox=pnew;
            listaux2 = listaux;
            listaux = pnew; 
            tmp=1;
        } while ( (fread(pnew, sizeof(data), 1, fp)) == 1);
        free(listaux);
        listaux2->prox = NULL;  // eliminate last garbadge struct
        rebuild2Darray(ptable, list, initdim,&turn);
        printf("Resuming match against %s\n",option1==1 ? "random agent" : "another player");
    } else {
        initdim = ptable->nlin = ptable->ncol = intUniformRnd(3, 5);
        ptable = summon2Darray(ptable, list);
        tmp=0;
        printf("Play against a random agent(1) or another player(2)?\n 1/2 -> ");
        do{
            if (tmp!=0)
                printf(" 1/2 -> ");
            scanf("%d",&option1);
            while((c = getchar()) != '\n' && c != EOF)
            /* discard */ ;
            tmp=1;
        } while (option1!=1 && option1!=2);
    }
    fclose(fp);
    gameturn(ptable,list,pmaxplays,option1,initdim,turn);
}

void totext(pdata p,int robot1){
    int count=1;
    char fichtxt[50]="a";
    FILE *fp;
    printf("Choose file name to save the succession of all plays: ");
    fgets(fichtxt,sizeof(fichtxt),stdin);
    fp = fopen(fichtxt,"wt");
    if (fp == NULL) {
        printf("failed to save plays to file\n");
    } else {
        fprintf(fp,"--------------------------\nPlaytype examples:\nplaytype 1: 1,2\nplaytype 2: 1,2S\nnplaytype 3: C\nnplaytype 4: L\n\nplayer B is a bot: %s\n--------------------------\n\n",robot1==1 ? "TRUE" : "FALSE");
        while (p!=NULL){
            fprintf(fp,"round %d, player %c: \nl=%d, c=%d, playtype=%d\n",count++,whosplaying(count),(*p).l,(*p).c,(*p).playtype);
            p = p -> prox; // left pointer beggins pointing to right pointer
        }
    }
    fclose(fp);
}

void pause(pTable ptable,pdata list,int robot1,int initdim,pmaxplays pmaxplays){
    FILE * fp;
    int i;
    printf("writing game state to fich.bin...");
    fp = fopen("fich.bin","wb");
    if (fp == NULL) {
        fclose(fp);
        end_game(ptable,list);
    };
    if (list==NULL){
        i=0;
        fwrite(&i,sizeof(int),1,fp); // To indicate that there is no data to read
        printf("no game data to save, aborting\n");
    } else {
        i=1;
        fwrite(&i,sizeof(int),1,fp); // To indicate that there is data to read
        fwrite(&robot1,sizeof(robot1),1,fp);
        fwrite(&initdim,sizeof(initdim),1,fp);
        fwrite(pmaxplays,sizeof(maxplays),1,fp);
        //show(list);
        while (list!=NULL && list->playtype!=0){
            fwrite(list,sizeof(data),1,fp);
            list = list -> prox;
        }
    }
    // Binary save:
    // [Int flag wether there's valid data, 0 or 1][robot1][initdim][pmaxplays)][linked list]
    fclose(fp);
    end_game(ptable,list);
}

void deactivatefichbin(){
    FILE * fp;
    fp = fopen("fich.bin","wb");
    printf("deactivating fich.bin file if present...\n");
    if (fp == NULL) {
        printf("failed to deactivate fich.bin, the file should be deleted manually\n");
    } else {
        int i=0;
        fwrite(&i,sizeof(int),1,fp); // To indicate that there is no data to read
    }
    fclose(fp);
    return;
}