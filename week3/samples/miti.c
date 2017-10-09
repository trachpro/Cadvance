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

    while('a' <= a[i] && a[i] <= 'z' || a[i] == ' ') {
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
    mvprintw(1,y,"enter the word: ");
    
    int type = handleInput(word);

    filterWord(word);

    btpos(root,ZSTART);
    int dem = 0;
    
    while(bnxtky(root,a,&i) == 0) {
        btsel(root, a, v, 1800, &rsize);

        if(type == 1 && strcmp(a,word) == 0) {
            mvprintw(2,y,"%s:\t%s\n", a, v);
            flag = 1;
            break;
        }
        if(type == 2 && strcmp(a,word) >= 0) {
            mvprintw(2,y,"%s:\t%s\n", a, v);
            flag = 1;
            break;
        }
    }

    if(!flag) mvprintw(1,0,"no number match!\n");
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
            mvprintw(2+i, 10,"%s\n", suggestion_str[i]);
		}
	}
	else printf("No suggetion found\n");
}

void addNewWord(BTA *root, BTA *sdic) {
    mvprintw(0,0,"input english word: ");

    char word[15], mean[40];
    char en[MAX_LEN_WORD];

    handleInput(word);
    filterWord(word);
    mvprintw(2,0,"input meaning: ");

    handleInput(mean);
    filterWord(mean);
    int x = btins(root, mean, word, 1800);
    // btins(root, mean, word, 1800);

    SoundEx(en, word, 4,1);
    btins(sdic, word, en, 5 * sizeof(char));

    if(x) {
        mvprintw(4,0,"add fail: %s-%s",word, mean);
    }
}

void menu() {
    mvprintw(0,30,"my dictionary");
    mvprintw(1,50,"menu");
    mvprintw(2,50,"1.add new word");
    mvprintw(3,50,"2.update word");
    mvprintw(4,50,"3.delete word");   
}


int main() {
    initscr();
    btinit();

    BTA *root = btopn("vdic.dat",0,0);
	BTA *sdic =  btopn("soundExTree.dat",0,0);
    readFile(root);
    createSdic(root, sdic);

    char word[15];

    char ls;
    do {
        mvprintw(0,30,"MY DICTIONARY");
        mvprintw(1,40,"1.search");
        mvprintw(2,40,"2.suggestion");
        mvprintw(3,40,"0.exit");
        ls = getch();
        clear();

        switch(ls) {
            case '1': {
                mvprintw(0,30,"SEARCH");
                searchByName(root);
                break;
            }
            case '2': {
                mvprintw(0,30,"SUGGESTION");
                move(1,0);

                handleInput(word);
                filterWord(word);
                findSuggestion(sdic,word);
                break;
            }
            case '0': break;
            default: mvprintw(0,24,"WRONG OPTION! TRY AGAIN!"); break;
        }

        if(ls != '0') {
            mvprintw(18,20,"press any key to return the menu!");
            getch();
            clear();
        }

    }while(ls!='0');

    btcls(root);
    btcls(sdic);
    mvprintw(15,30,"BYE  BYE");
    getch();
    endwin();
    return 0;
}