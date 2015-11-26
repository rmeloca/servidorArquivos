#pragma once

#include "request.h"

typedef struct node Node;
typedef Request ItemType;

struct node {
    ItemType* data;
    Node* next;
};

typedef struct {
    Node* first;
    Node* last;
    int size;
} List;

List *createList();
void initializeList(List *l);
int addListLast(List *l, ItemType* e);
int addList(List* l, ItemType* e, int index);
int removeList(List* l, int index, ItemType* e);
int removeListLast(List* l, ItemType* e);
int getList(List* l, int index, ItemType* e);
int setList(List* l, int index, ItemType* e);
int equals(ItemType *e1, ItemType *e2);
int indexOfList(List* l, ItemType* e);
int containsList(List* l, ItemType* e);
int sizeList(List* l);
int isEmptyList(List* l);
void printList(List* l);
Node* createNode();