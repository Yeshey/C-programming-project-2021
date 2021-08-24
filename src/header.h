#ifndef HEADER
#define HEADER
#include "globals.h"
void tableprint(pTable ptable);
void welcome();
pdata playoptions(pTable ptable, pdata list,pmaxplays pmaxplays,int turn,int robot1,int initdim);
void show(pdata p);
void initializer();
void gameturn(pTable ptable, pdata list,pmaxplays pmaxplays,int robot1,int initdim,int turn);
int winner(pTable ptable);
int interpretplay(char * str,int * inlin, int * incol,pmaxplays pmaxplays,int turn, pTable ptable,int robot1);
void updatetablearray(pTable ptable, pdata news);
char whosplaying(int turn);
void addline(pTable ptable,pdata news);
void addcolumn(pTable ptable,pdata news);
void robot(char * saveinput,pTable ptable,pmaxplays pmaxplays);
int isrobotplayin(int turn,int robot1);
void totext(pdata p,int robot1);
void freelist(pdata list);
void freearray(pTable ptable);
void freememory(pTable ptable,pdata list);
pTable summon2Darray(pTable ptable,pdata list);
pTable rebuild2Darray(pTable ptable,pdata list,int initdim,int * turn);
void end_game(pTable ptable,pdata list);
void rewindx(pTable ptable,pdata list,int option2,int initdim,int turn);
void pause(pTable ptable,pdata list,int robot1,int initdim,pmaxplays pmaxplays);
void deactivatefichbin();
#endif 