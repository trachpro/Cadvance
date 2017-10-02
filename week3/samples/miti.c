#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<ncurses.h>

#include "btree.h"

void readFile(BTA *root) {
    char a[1800];
    char v[1800];

    FILE *f = fopen("anhviet109K.txt","r");

    if(f ==  NULL) return;

    while(1) {
        while(fgetc(f) != '@' && !feof(f));

        if(!feof) break;
        fscanf(f,"%49[a-zA-Z]",a);

        if(!strcmp(a,"zone")) break; 

        while(fgetc(f) != '-' && !feof(f));
        if(!feof) break;
        fscanf(f,"%[^\n]",v);
        btins(root, a, v, 1800);
    }

    fclose(f);
}

void print(BTA *root)
{
    BTint i;
    char a[1800];
    char v[1800];
    int rsize;
    btpos(root, ZSTART);
    while(bnxtky(root, a, &i) == 0) {
        btsel(root, a, v, 1800, &rsize);
        printf("%s:\t%s\n", v, a);
    }
}

void searchByName(BTA *root) {
    char a[1800],v[1800];
    char word[15];
    int i, rsize, flag = 0;
    printf("enter the word: ");
    int c;
    do {
        c = getchar();
    }while(c != '\n' && c!= '\t');
    // scanf("%[^\t]",word); scanf("%*c");
    
    btpos(root,ZSTART);
    int dem = 0;
    
    while(bnxtky(root,a,&i) == 0) {
        btsel(root, a, v, 1800, &rsize);
        // printf("%s\n",a);
        if(strcmp(a,word) >= 0) {
            printf("%s:\t%s\n", a, v);
            flag = 1;
            break;
        }
        // if(dem++ == 2) break;
    }

    if(!flag) printf("no number match!\n");
}

int main() {
    BTA *root;
    // getch();
    // return 0;
    btinit();

    root = btcrt("vdic",0, FALSE);
    readFile(root);
    searchByName(root);
    // print(root);
    btcls(root);
    return 0;
}