#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<ncurses.h>
#include "soundix.h"

#define MAX_LEN_MEAN 1800
#define MAX_LEN_WORD 40

#include "btree.h"

int x = 0, y = 0;

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

void print(BTA *root,int r,int c)
{
    BTint i;
    char a[1800];
    char v[1800];
    int rsize;
    
    btpos(root, ZSTART);

    while(bnxtky(root, a, &i) == 0) {
        btsel(root, a, v, 1800, &rsize);
        mvprintw(r++, c,"%s:\t%s\n", a, v);
    }
}

void filterWord(char *a) {
    int i = 0;
    int r = 2;

    while('a' <= a[i] && a[i] <= 'z') {
        i++;
    }

    a[i] = '\0';
}

int handleInput(char *a) {
	int i = 0; //index of input character in array a
	int r = 3, c = 0; //row and column position
	int ch;

	while(1) {
		ch = getch();
		if(ch == '\n') return 1;
		if(ch == '\t') return 2;
        
        a[i++] = ch;
		
    }
}

void searchByName(BTA *root) {
    char a[1800],v[1800];
    char word[15];
    int i, rsize, flag = 0;
    mvprintw(x++,y,"enter the word: ");
    
    handleInput(word);

    filterWord(word);
    mvprintw(10,10,"%d",strlen(word));
    
    btpos(root,ZSTART);
    int dem = 0;
    
    while(bnxtky(root,a,&i) == 0) {
        btsel(root, a, v, 1800, &rsize);
        // printf("%s\n",a);
        if(strcmp(a,word) == 0) {
            mvprintw(x++,y,"%s:\t%s\n", a, v);
            flag = 1;
            break;
        }
        // if(dem++ == 2) break;
    }

    // if(!flag) printf("no number match!\n");
}

int createSdic(BTA *root, BTA *sdic) {
    char word[MAX_LEN_WORD];
	char mean[MAX_LEN_MEAN];
	int rsize;
	int count = 0;
	char soundex[5];

	btsel(root,"", mean, MAX_LEN_MEAN *sizeof(char), &rsize);
	while(  btseln(root,word, mean, MAX_LEN_MEAN * sizeof(char), &rsize) == 0 ) {
		SoundEx(soundex, word,4,1);
		int x = btins(sdic, word, soundex, 5 * sizeof(char));
        count++;
    }

	return count;
}

int suggestion(BTA *soundExTree, char* word, char suggestion[][MAX_LEN_WORD]) {
	int rsize;
	char word_soundex[5];
	char soundex[5];
	int size = 0;
	char en[MAX_LEN_WORD];

	SoundEx(word_soundex, word, 4,1);

	btsel(soundExTree, "", soundex, 5 * sizeof(char), &rsize);
	while( btseln(soundExTree, en, soundex, 5 * sizeof(char), &rsize ) == 0 && size < 10) {
		if ( strcmp(word_soundex, soundex) == 0 ) {
			strcpy(suggestion[size], en);
			size++;
		}
	}
	return size;
}


void findSuggestion(BTA *soundExTree, char *word) {
	
	char suggestion_str[10][MAX_LEN_WORD];

	int size = suggestion(soundExTree, word, suggestion_str);

	if (size > 0)
	{
		// printf("Do you mean: \n");
		for (int i = 0; i < size; i++)
		{
            // printf("%s\n",suggestion_str[i] );
            mvprintw(2+i, 0,"%s\n", suggestion_str[i]);
		}
	}
	else printf("No suggetion found\n");
}


int main() {
    initscr();
    btinit();

    BTA *root = btopn("vdic.dat",0,0);
	BTA *sdic =  btcrt("soundExTree.txt",0,0);
    readFile(root);
    createSdic(root, sdic);
    findSuggestion(sdic,"com");
    // print(sdic,0,0);

    btcls(root);
    btcls(sdic);
    getch();
    endwin();
    return 0;
}