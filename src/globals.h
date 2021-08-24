#ifndef GLOBAL
#define GLOBAL
typedef struct holy{
    int l;
    int c;
    int playtype;
    struct holy *prox;
}data, *pdata;

typedef struct max{
    int addlcA,addlcB;
    int RockA,RockB;
}maxplays, *pmaxplays;

typedef struct tabarr{
    char ** table;
    int ncol,nlin;
}Table, *pTable;

#endif
