#include <stdio.h>
#include <stdlib.h>

typedef int ItemType;

typedef struct node {
    ItemType data;
    struct node *prev;
    struct node *next;
} Node;

typedef struct {
    Node *first;
    Node *last;
    int size;
} List;

List *createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List *l) {
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

int addListLast(List *l, ItemType e) {
    addList(l, e, l->size);
}

int addList(List* l, ItemType e, int index) {
    if (index < 0 || index > l->size) {
        return 0;
    }
    Node *node = (Node*) malloc(sizeof (Node));
    Node *aux;
    node->data = e;
    if (!l->first) {//primeiro elemento
        printf("1o Elemento\n");
        node->next = NULL;
        node->prev = NULL;
        l->first = node;
        l->last = node;
    } else if (index == 0) {//no começo
        printf("Begining\n");
        aux = l->first;
        node->next = aux;
        node->prev = NULL;
        aux->prev = node;
        l->first = node;
    } else if (index == l->size) {//no fim
        printf("End\n");
        aux = l->last;
        aux->next = node;
        node->prev = aux;
        node->next = NULL;
        l->last = node;
    } else {//no meio
        printf("Middle\n");
        aux = l->first;
        int i = 1;
        while (i < index) {
            aux = aux->next;
            i++;
        }
        node->next = aux->next;
        node->prev = aux;
        aux->next = aux;
        aux = node->next;
        aux->prev = node;
    }
    l->size++;
    return 1;
}

int removeList(List* l, int index, ItemType *e) {
    if (isEmptyList(l)) {
        return 0;
    }
    if (index < 0 || index >= l->size) {
        return 0;
    }
    Node *removed, *aux;
    if (index == 0) {
        removed = l->first;
        if (l->size == 1) {
            l->first = NULL;
            l->last = NULL;
        } else {
            aux = removed->next;
            l->first = aux;
            aux->prev = NULL;
        }
    } else if (index == l->size - 1) {
        removed = l->last;
        aux = removed->prev;
        aux->next = NULL;
        l->last = aux;
    } else {
        if (index < l->size / 2) {
            removed = l->first;
            int i = 0;
            while (i < index) {
                removed = removed->next;
                i++;
            }
        } else {
            removed = l->last;
            int i = l->size - 1;
            while (i > index) {
                removed = removed->prev;
                i--;
            }
        }
        aux = removed->prev;
        aux->next = removed->next;
        aux = removed->next;
        aux->prev = removed->prev;
    }
    *e = removed->data;
    free(removed);
    l->size--;
    return 1;
}

int removeElementList(List* l, ItemType* e) {
    removeList(l, indexOfList(l, e), e);
}

int getList(List* l, int index, ItemType* e) {
    if (isEmptyList(l)) {
        return 0;
    }
    Node *node;
    int i;
    if (index <= l->size / 2) {
        node = l->first;
        i = 0;
        while (i <= index) {
            i++;
            node = node->next;
        }
    } else {
        node = l->last;
        i = l->size - 1;
        while (index <= i) {
            i--;
            node = node->prev;
        }
    }
    *e = node->data;
    return 1;
}

int setList(List* l, int index, ItemType* e) {
    if (isEmptyList(l)) {
        return 0;
    }
    Node *node;
    int i;
    if (index <= l->size / 2) {
        node = l->first;
        i = 0;
        while (i <= index) {
            i++;
            node = node->next;
        }
    } else {
        node = l->last;
        i = l->size - 1;
        while (index <= i) {
            i--;
            node = node->prev;
        }
    }
    node->data = *e;
    return 1;
}

int indexOfList(List* l, ItemType* e) {
    if (isEmptyList(l)) {
        return 0;
    }
    Node *node = l->first;
    int i = 0;
    while (node) {
        if (node->data == *e) {
            return i;
        }
        i++;
        node = node->next;
    }
    return -1;
}

int containsList(List* l, ItemType *e) {
    if (isEmptyList(l)) {
        return 0;
    }
    Node *node = l->first;
    while (node) {
        if (node->data == *e) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

int sizeList(List* l) {
    return l->size;
}

int isEmptyList(List* l) {
    return l->first == NULL;
}

void printList(List* l) {
    Node *node = l->first;
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    List *l = createList();
    initializeList(l);
    ItemType *e = (ItemType*) malloc(sizeof (ItemType));

    addList(l, 123, 0);
    addList(l, 456, 1);
    addList(l, 79, 0);
    addList(l, 789, 10);
    addList(l, 45, 2);
    addList(l, 56, 1);
    addListLast(l, 10);
    addListLast(l, 20);
    addListLast(l, 30);
    addListLast(l, 40);
//    printList(l);
    printf("Size: %d\n", sizeList(l));

//    removeList(l, 5, e);
//    removeList(l, 5, e);
//    removeList(l, 1, e);
//    
//    addList(l, 123, 0);
//    addList(l, 456, 1);
//    addList(l, 789, 2);
//    
//    addListLast(l, 10);
//    addListLast(l, 20);
//    addListLast(l, 30);
//    addListLast(l, 40);
//    
//    removeList(l, 2, e);
//    removeList(l, 1, e);
//    containsList(l, e);
//    printList(l);
//    
//    getList(l, 4, e);
//    removeElementList(l, e);
//    removeElementList(l, e);
//    removeElementList(l, e);
//    removeElementList(l, e);
//    
//    addList(l, 123, 0);
//    addList(l, 456, 1);
//    addList(l, 789, 2);
//    
//    addListLast(l, 10);
//    addListLast(l, 20);
//    addListLast(l, 30);
//    addListLast(l, 40);
//    
//    getList(l, 4, e);
//    printf("GET: %d\n", *e);
//    
//    setList(l, 4, e);
//    getList(l, 1, e);
//    printf("GET: %d\n", *e);
//    printList(l);
    return 0;
}