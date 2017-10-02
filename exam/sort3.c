#include<stdio.h>
#include<stdlib.h>

void my_memcpy(void *des, const void *sour, size_t size)
{
	char *x = (char *)des;
	char *y = (char *)sour;
	
	for(int i = 0; i< size; i++) {
		x[i] = y[i];
	}
}

void swap(void *x, void *y, size_t size)
{
	char * tem = (char*)malloc(size);
	my_memcpy(tem, x, size);
	my_memcpy(x, y, size);
	my_memcpy(y,tem,size);
	
	free(tem);
}

int compare(const void* x, const void* y)
{
	int a =  *((int*)x) - *((int*)y);
	printf("%d - %d = %d\n",*(int*)x, *(int*)y,a);
	return a;
}

void print(int arr[], int size)
{
	for(int i = 0; i<= size; i++) {
		printf("%d ",arr[i]);
	}
	printf("\n----------\n");
}

void sort(void *arr, int l, int r, size_t size, int (*compare)(const void *x, const void *y))
{
	printf("----%d --- %d\n", l,r);
	print((int*)arr,13);
	if(r <= l) return;
	int s = l - 1, e = r;
    int ss = l - 1, ee = e;
	void * p = (void*)arr + size*r;
	
	while(1) {
		while(compare(p, (void*)arr + (++s)*size) >0) ;
        while(compare(p, (void*)arr + (--e)*size) < 0 )
        {
            // printf("\n %d - %d\n", e, l);
            if (e == l)
                break;
        }
        // printf("\n----%d-%d\n",s,e);
        // return;
		
        if(s >= e) break;
		swap((void*)arr + (s)*size,(void*)arr + (e)*size, size);
		
		if(compare((void*)arr +s*size, p ) == 0) swap((void*)arr + s*size, (void*)arr + (ss++)*size, size);
		if(compare((void*)arr +e*size, p ) == 0) swap((void*)arr + e*size, (void*)arr + (ee--)*size, size);
	}
	// printf("%d--%d\n", *(int*)((void*)arr + s*size),*(int*)((void*)arr + r*size));
	swap((void*)arr + s*size, (void*)arr + r*size,size);
	// printf("--%d--%d\n", *(int*)((void*)arr + s*size),*(int*)((void*)arr + r*size));
	// print((int*)arr,7);
	// return;
    s = s - 1;
    e = s + 1;
	
	for(int i = l; i< ss; i++) swap(((void*)arr + i*size), (void*)arr + (s--)*size, size);
	for(int i = r - 1; i > ee; i--) {
		swap(((void*)arr + i*size), (void*)arr + (e++)*size, size);
		printf("swap: %d %d", i,e);
	}

	print((int*)arr,13);
	sort(arr, l,s,size, compare );
	
	sort(arr, e,r,size, compare );
}

int main()
{
	int a[] = {1,5,3,10,44,10,8,9,6,8,6,11,10,0};
	print(a,13);
	sort(a,0,13,sizeof(int), compare);
	print(a,13);
	return 0;
}
