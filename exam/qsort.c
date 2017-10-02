#include <stdio.h>
#include<stdlib.h>
// #include<time.h>
// #include<string.h>

typedef struct
{
    int key;
    char value[10];
} type;

void *mmemcpy(void *region1, const void *region2, size_t size)
{
    const char *first = (const char *)region2;
    const char *last = (const char *)region2 + size;
    char *result = (char *)region1;
    while (first != last)
        *result++ = *first++;
    // return result;
}

void swap(void *p1, void *p2, size_t pSize)
{
    void *tmp = (void*)malloc(pSize);
    mmemcpy(tmp, p1, pSize);
    mmemcpy(p1, p2, pSize);
    mmemcpy(p2, tmp, pSize);

    free(tmp);
}

int compare(const void *x,const void *y) {
    int a = *((int *)x), b = *((int *)y);
    printf("%d---%d\n",a,b);
    return a - b;
}

int search(void *buff, int size, int l, int r, void *item, int (compare)(const void*,const void*)) {
    if(r < l) return -1;
    int i = (l + r) / 2;
    int res = -compare(item, (char *)buff + i*size);
    printf("--%d\n",res);
    if(res == 0) return i;
    
    else if(res < 0 ) return search(buff, size, i + 1, r, item, compare);

    else return search(buff, size, l, i - 1, item, compare);
}

void sort(void *arr, int size, int len, int l, int r, int compare(const void*, const void*)) {
    if(r <= l) return;

    int s = l - 1, ss = l - 1;
    int e = r, ee = r; 
    void * p = (void *)arr + r*size;

    while(1) {
        while(compare(p,(void *)arr + (++s)*size) >= 0 && s < r);
        // break;
        while(compare(p,(void *)arr + (--e)*size)<=0 && s<= e);
        // break;
        if(s >= e) break;
        swap((void *)arr + (s)*size,(void *)arr + (e)*size, size);

        if(compare((void *)arr + (s)*size, p) == 0) swap()
    }

    swap(p, (void *)arr + s * size, size);

    sort(arr, size, len, l, s - 1, compare);
    sort(arr, size, len, s + 1, r, compare);
}

void print(int *a, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
}


int main()
{
    int a[] = {1,8,3,4,5,6};
    int x = 2;
    // printf("%d\n", search(a,sizeof(int), 0,5, &x, compare));
    sort(a, sizeof(int),6, 0,5,compare);
    print(a,6);
    // qsort(a,5,sizeof(int),compare);
}