#include<stdio.h>
#include<string.h>
#include"fields.h"
#include"dllist.h"
#include"jrb.h"
#include<stdlib.h>

typedef struct {
    char name[10];
    Jval phone;
}phonebook;

void readFile(JRB tree) {
    phonebook a;
    char *name = (char*)malloc(sizeof(char)*10);
    FILE *f = fopen("phonebook.txt", "r");

    for(int i = 0; i< 3; i++) {
        long tem;
        fscanf(f, "%[^:]",name); fscanf(f,"%*c");

        fscanf(f, "%ld", &tem);
        a.phone = new_jval_l(tem);
        // printf("%s-%ld\n",name,tem);
        if(jrb_find_str(tree, name)) continue;
        
        jrb_insert_str(tree, strdup(name),a.phone);
    }
    free(name);
    fclose(f);
}

int main()
{
    JRB br = make_jrb();
    JRB node;
    readFile(br);
    jrb_traverse(node, br) {
        printf("%s-%ld\n",jval_s(node->key),jval_l(node->val));
    };

    jrb_free_tree(br);
}