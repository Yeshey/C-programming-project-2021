#include <stdio.h>
#include "header.h"

void tableprint(pTable ptable){
    /*Table 4*4:
    S - Stone
     ---------------
    | G : Y :   : R |    
    |---:---:---:---|
    | S : G :   : Y |
    |---:---:---:---| 
    |   :   :   :   |
    |---:---:---:---|
    | S : S : Y : R |
     ---------------*/
    int i=0,j=0;
    //-----Print the table-----
    printf("  ");
    for(i=0;i<ptable->ncol;i++)
        printf(" C%d ",i);
    putchar('\n');

    printf("   ");
    for(i=0;i<ptable->ncol;i++)
        if(i!=ptable->ncol-1)
            printf("----");
        else 
            printf("---");
    putchar('\n');

        for(i=0;i<ptable->nlin;i++){
            printf("L%d|",i);
            for(j=0;j<ptable->ncol-1;j++){
                printf(" %c :",ptable->table[i][j]);
            }
            printf(" %c |\n",ptable->table[i][j]);

            if(i!=ptable->nlin-1){
                printf("  |");
                for(j=0;j<ptable->ncol-1;j++)
                    printf("---:");
                printf("---|\n");
            }
        }
    printf("   ");
    for(i=0;i<ptable->ncol;i++)
        if(i!=ptable->ncol-1)
            printf("----");
        else 
            printf("---");
    putchar('\n');
    //-----Print the table-----
}

void show(pdata p){
    //Shows contents of connected list
    int count=1;
    printf("printing\n");
    while (p!=NULL){
        printf("struct%d: \nl=%d, c=%d, playtype=%d\n",count++,(*p).l,(*p).c,(*p).playtype);
        p = p -> prox;
    }
}

void welcome(){
    printf("\n     ::::::::::: ::::::::   ::::::::   ::::::::  \n");
    printf  ("        :+:    :+:    :+: :+:    :+: :+:    :+:  \n");
    printf  ("       +:+    +:+    +:+ +:+        +:+    +:+   \n");
    printf  ("      +#+    +#+    +:+ :#:        +#+    +:+    \n");
    printf  ("     +#+    +#+    +#+ +#+   +#+# +#+    +#+     \n");
    printf  ("#+# #+#    #+#    #+# #+#    #+# #+#    #+#      \n");
    printf  ("#####      ########   ########   ########        \n\n");
    printf( "      :::::::::   :::::::: \n");
    printf( "     :+:    :+: :+:    :+: \n");
    printf( "    +:+    +:+ +:+    +:+  \n");
    printf( "   +#+    +:+ +#+    +:+   \n");
    printf( "  +#+    +#+ +#+    +#+    \n");
    printf( " #+#    #+# #+#    #+#     \n");
    printf( "#########   ########       \n\n");
    printf( "      ::::::::  ::::::::::   :::   :::       :::     :::::::::: ::::::::  :::::::::   :::::::: \n");
    printf( "    :+:    :+: :+:         :+:+: :+:+:    :+: :+:   :+:       :+:    :+: :+:    :+: :+:    :+: \n");
    printf( "   +:+        +:+        +:+ +:+:+ +:+  +:+   +:+  +:+       +:+    +:+ +:+    +:+ +:+    +:+  \n");
    printf( "  +#++:++#++ +#++:++#   +#+  +:+  +#+ +#++:++#++: :#::+::#  +#+    +:+ +#++:++#:  +#+    +:+   \n");
    printf( "        +#+ +#+        +#+       +#+ +#+     +#+ +#+       +#+    +#+ +#+    +#+ +#+    +#+    \n");
    printf( "#+#    #+# #+#        #+#       #+# #+#     #+# #+#       #+#    #+# #+#    #+# #+#    #+#     \n");
    printf( "########  ########## ###       ### ###     ### ###        ########  ###    ###  ########       \n\n");
    //Used site for font generation: https://patorjk.com/software/taag/#p=display&f=Small&t=Jogo%20do%20sem%C3%A1fro
    //Font: Alligator
}

