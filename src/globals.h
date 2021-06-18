#ifndef GLOBAL
#define GLOBAL
typedef struct holy{
    int l;
    int c;
    int playtype;
    //char opt[7];
    struct holy *prox;
}data, *pdata;
/* //Same as
typedef struct holy data, *pdata;   
struct holy{
    int l;
    int c;
    int playtype;
    char opt[7];
    pdata prox; 
}; */
typedef struct max{
    int addlcA,addlcB;
    int RockA,RockB;
}maxplays, *pmaxplays;

typedef struct tabarr{
    char ** table;
    int ncol,nlin;
}Table, *pTable;

#endif
