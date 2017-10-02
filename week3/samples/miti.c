#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void readFile() {
    char a[10];
    scanf("%[^ ]",a);
    printf("%d\n", (int)strlen(a));
}

int main() {
    
    readFile();
    return 0;
}