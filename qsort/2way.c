#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int a[],int x,int y)
{
    int tem = a[x];
    a[x] = a[y];
    a[y] = tem;
}

void quickSort(int a[],int l,int r)
{
    if(r <= l) return;

    int s = l - 1, e = r, pi = a[r];

    while(1) {
        while(a[++s] <= pi);
        while(a[--e] >= pi) if(e == r) break;
        
        if(s >= e) break;
        printf("\n %d-%d ------- %d-%d-----%d\n",s,e,a[s], a[e],pi);
        swap(a, e, s);
    }

    swap(a,e, r);
    printf("\n-------------\n");
    quickSort(a,l, s - 1);
    quickSort(a,e + 1, r);
    
}

void generate(int a[],int n)
{
    srand(time(NULL));
    for(int i = 0; i< n; i++)
    {
        a[i] = rand() % 9;
    }
}

void print(int a[], int n)
{
    for(int i = 0; i< n; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n-----------\n");
}

int main()
{
    int max = 10;
    int *a = (int *)malloc(sizeof(int)*max);

    generate(a,max);
    quickSort(a,0,max - 1);
    print(a,max);
    return 0;
}