#include <stdio.h>
#include <string.h>

#define ItemType int

typedef struct {
    int size;
    int length;
    ItemType *items;
} List;

List *createList();
void initializeList(List *l);
int addLastList(List *l, ItemType e);
int addList(List* l, ItemType e, int index);
int removeList(List* l, int index, ItemType *e);
int removeElementList(List* l, ItemType* e);
int getList(List* l, int index, ItemType* e);
int setList(List* l, int index, ItemType* e);
int indexOfList(List* l, ItemType* e);
int containsList(List* l, ItemType *e);
int sizeList(List* l);
int isEmptyList(List* l);
void printList(List* l);

int main() {
    return 0;
}

List *createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List *l) {
    l->length = 6;
    l->size = 0;
    l->items = (ItemType*) calloc(l->length, sizeof (ItemType));
}

int addLastList(List *l, ItemType e) {
    return addList(l, e, sizeList(l));
}

int addList(List* l, ItemType e, int index) {
    if (sizeList(l) == l->length) {
        //dobra
    }
    if (index > sizeList(l)) {
        index = sizeList(l);
    } else if (index < 0) {
        index = 0;
    }
    if (index < sizeList(l)) {
        memcpy(l->items[index + 1], l->items[index], sizeof (int) * sizeList(l) - index);
    }
    l->items[index] = e;
    l->size++;
    return 1;

}

int removeList(List* l, int index, ItemType *e) {

}

int removeElementList(List* l, ItemType* e) {

}

int getList(List* l, int index, ItemType* e) {

}

int setList(List* l, int index, ItemType* e) {

}

int indexOfList(List* l, ItemType* e) {

}

int containsList(List* l, ItemType *e) {

}

int sizeList(List* l) {
    return l->size;
}

int isEmptyList(List* l) {
    return l->length == 0;
}

void printList(List* l) {
    int i = 0;
    while (i < l->size) {
        printf("%d ", l->items[i]);
        i++;
    }
    printf("\n");
}