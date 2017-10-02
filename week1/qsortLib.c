#include<stdio.h>
#include<stdlib.h>

int values[] = {88, 56, 100, 2, 5};

int cmpFunc(const void *a, const void *b)
{
        printf("\n%d - %d\n",*(int*)a,*(int*)b);
        return (*(int*)a - *(int*)b);
}

int main()
{
        int n;
        printf("before sorting  the list is:\n");

        for(int i=0; i < 5; i++){
                printf("%5d", values[i]);
        }

        qsort(values, 5, sizeof(int), cmpFunc);

        printf("\nAfter sorting the list is: \n");
        for( n = 0 ; n < 5; n++ ) 
                {   
                        printf("%5d", values[n]);
                }
   
        printf("\n");
        return 0;
}
