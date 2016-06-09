#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef LIST_H
#define LIST_H


typedef struct  node {
  struct node * next;
  char * type;
  char * name;
  char * data;
} item;

typedef struct {
  item * head;
} list;

item * search(list * l, char * s);
void   update(list * l, char * s, char * v);
item * create(char * s, char * t, char * v);
item * insert(list * l, char * t, char * s, char * v);

#endif
