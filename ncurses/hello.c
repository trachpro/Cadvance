
#include <ncurses.h>
WINDOW * win1;
WINDOW * win2;

int handleInput(char *a) {
	int i = 0; //index of input character in array a
	int r = 0, c = 0; //row and column position
	char ch;

	
	
	while(ch) {
		ch = getch();
		if(ch == '1') {
			mvwin(win1, 30, 30);
			mvprintw(20, 20, "win1");
		}
		else {
			mvwin(win2, 40, 40);
			mvprintw(20, 10, "win2");			
		}
	}
}

int main()
{	
	initscr();
	// raw();
	char a[20];
	handleInput(a);

	mvprintw(2,0,a);
	getch();
	endwin();
	return 0;
}