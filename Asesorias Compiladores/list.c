#include "list.h"

item * create(char * s, char * t, char * v) {
  item * n = (item*) malloc(sizeof(item));
  n->name  = (char*) malloc(sizeof(s)); 
  n->data  = (char*) malloc(sizeof(v)); 
  n->type  = (char*) malloc(sizeof(t)); 
  strcpy(n->name, s);
  strcpy(n->data, v);
  strcpy(n->type, t);
  n->next = 0;
  return    n;
}

item * insert(list * l, char * t, char * s, char * v) {
  item  * n = create(s, t, v);
  if (!l->head) 
    return l->head  = n;  
  item  ** x = &l->head;
  while ((*x)->next)
    x = &(*x)->next;
  return (*x)->next = n;
} 

item * search(list * l, char * s) {
  if (!l->head) return 0;  
  item  ** x =  &l->head;
  while ((*x)) {
    if (strcmp((*x)->name, s) == 0)
      return *x;
    x = &(*x)->next;
  }
  return 0;
}

void update(list * l, char * s, char * v) {
  if (!l->head)   return;  
  item  ** x =  &l->head;
  while ((*x)) {
    if (strcmp((*x)->name, s) == 0) {
      (*x)->data = (char*) malloc(sizeof(v));
      strcpy((*x)->data, v);
      return;
    }
    x = &(*x)->next;
  } 	
}


