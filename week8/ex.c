#include<stdio.h>
#include<stdlib.h>
#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"

JRB createList() {
  return make_jrb();
}

Dllist createNode() {
  return new_dllist();
}

void addOneDrect(JRB x, int key, int ad) {
  JRB node = jrb_find_int(x, key);
  Dllist list = NULL;
  
  if(list == NULL) {
    list = new_dllist();
  } else {
    list = (Dllist)list->val;
  }
  
  dll_append(list, new_jval_i(ad));

  jrb_insert_int(x, int key, new_jval_v(list));
}

void addElement(JRB x, int a, int b) {
  addOneDrect(x, a, b);
  addOneDrect(x, b, a);
}
