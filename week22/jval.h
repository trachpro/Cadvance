#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef union {
    int i;
    long l;
    float f;
    double d;
    void *v;
    char c;
    char *s;
}jval;

jval new_jval_int(int i) {
    jval in;
    in.i = i;
    return in;
}

jval new_jval_long(long l) {
    jval in;
    in.l = l;
    return in;
}

jval new_jval_float(float f) {
    jval in;
    in.f = f;
    return in;
}

jval new_jval_double(double d) {
    jval in;
    in.d = d;
    return in;
}

jval new_jval_void(void *v) {
    jval in;
    in.v = v;
    return in;
}

jval new_jval_char(char c) {
    jval in;
    in.c = c;
    return in;
}

jval new_jval_string(char *s) {
    jval in;
    strcpy(in.s,s);
    return in;
}

void exch(jval *x, jval *y) {
    jval tem = *x;
    *x = *y;
     *y = tem;
}

void sort_gen(jval *arr, int l, int r, int(*compare)(jval*, jval*)) {
	if(l >= r) return;
	int i, p, j, q, k;
	i = p = l - 1;
	j = q = r;
	while(1) {
		while(compare(&arr[r], &arr[++i]) > 0);
		while(compare(&arr[r], &arr[--j]) < 0)
			if(j == i)
				break;
		if(i >= j)
			break;
		exch(&arr[i], &arr[j]);
		if(compare(&arr[r], &arr[i]) == 0)
			exch(&arr[i], &arr[++p]);
		if(compare(&arr[r], &arr[j]) == 0)
			exch(&arr[j], &arr[--q]);
	}
	exch(&arr[i], &arr[r]);
	j = i - 1;
	i = i + 1;
	for(k = l; k <= p; k++)
		exch(&arr[k], &arr[j--]);
	for(k = r - 1; k >= q; k--)
		exch(&arr[k], &arr[i++]);
	sort_gen(arr, l, j, compare);
	sort_gen(arr, i, r, compare);
}

int search_gen(jval *arr, int l, int r, jval val,int (*compare)(jval *, jval *)){
    if(l > r) return -1;
    int m = (l + r)/2;
    if(compare(&arr[m], &val) == 0) return m;
    else if (compare(&arr[m], &val) < 0) return search_gen(arr, m + 1, r, val, compare);
    else return search_gen(arr, l, m - 1, val, compare);
}

int compare_int(jval *a, jval *b) {
	return (*a).i - (*b).i;
}

void sort_gen_int(jval *arr, int l, int r){
	sort_gen(arr, l, r, compare_int);
}

int search_gen_int(jval *arr, int l, int r, jval val) {
	return search_gen(arr, l, r, val, compare_int);
}