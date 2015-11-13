#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef int ItemType;

struct node {
    ItemType data;
    Node *next;
};

typedef struct {
    Node *first;
    Node *last;
    int size;
} List;

List *createList();
void initializeList(List *l);
int addListLast(List *l, ItemType e);
int addList(List* l, ItemType e, int index);
int removeList(List* l, int index, ItemType *e);
int removeListLast(List* l, ItemType* e);
int getList(List* l, int index, ItemType* e);
int setList(List* l, int index, ItemType* e);
int indexOfList(List* l, ItemType* e);
int containsList(List* l, ItemType *e);
int sizeList(List* l);
int isEmptyList(List* l);
void printList(List* l);

Node* createNode();

int main() {
    List *list = createList();
    ItemType e = 15;
    initializeList(list);
    //    addListLast(list, 10);
    addListLast(list, 15);
    addList(list, 7, 0);
    addList(list, 17, 0);
//    addListLast(list, 5);
    //    addList(list, 71, 1);
    //    addList(list, -2, 1);
    //    addList(list, 0, 1);
    //    addList(list, 2, 1);
    //    addList(list, 88, 3);
    printf("size: %d\n", sizeList(list));
    //    int x;
    //    x = indexOfList(list, &e);
    //    printf("index de %d: %d\n", e, x);
    //    removeElementList(list, &e);
    printList(list);
}

Node* createNode() {
    return (Node*) malloc(sizeof (Node));
}

List* createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List *l) {
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

int addListLast(List *l, ItemType e) {
    return addList(l, e, l->size);
}

int addList(List* l, ItemType e, int index) {
    if (index > sizeList(l) || index < 0) {
        printf("aqui\n");
        return 0;
    }
    Node *node = createNode();
    node->data = e;
    node->next = NULL;
    if (isEmptyList(l)) {
        l->first = node;
        l->last = node;
    } else {
        Node *iterador = createNode();
        iterador = l->first;
        int i = 0;
        while (i < index) {
            i++;
            iterador = iterador->next;
        }
        if (index == 0) {
            node->next = iterador;
            l->first = node;
        } else if (index == sizeList(l)) {
            iterador->next = node;
            l->last = node;
        } else {
            node->next = iterador->next;
            iterador->next = node;
        }
        free(iterador);
    }
    l->size++;
    return 1;
}

int removeList(List* l, int index, ItemType * e) {
    if (index > l->size || index < 0) {
        return 0;
    }
    Node *node, *removed;
    node = createNode();
    removed = createNode();
    node = l->first;
    int i = 0;
    while (i < index) {
        i++;
        node = node->next;
    }
    if (index == 0) {
        removed = l->first;
        l->first = removed->next;
    } else if (index == sizeList(l)) {
        removed = node->next;
        node->next = NULL;
        l->last = node;
    } else {
        removed = node->next;
        node->next = removed->next;
    }
    if (isEmptyList(l)) {
        l->first = NULL;
        l->last = NULL;
    }
    *e = removed->data;
    free(node);
    free(removed);
    l->size--;
    return 1;
}

int removeElementList(List* l, ItemType * e) {
    return removeList(l, indexOfList(l, e), e);
}

int getList(List* l, int index, ItemType * e) {
    if (index > l->size || index < 0) {
        return 0;
    }
    Node *node = createNode();
    node = l->first;
    int i = 0;
    while (i <= index) {
        i++;
        node = node->next;
    }
    *e = node->data;
    free(node);
    return 1;
}

int setList(List* l, int index, ItemType * e) {
    if (index > l->size || index < 0) {
        return 0;
    }
    Node *node = createNode();
    node = l->first;
    int i = 0;
    while (i <= index) {
        i++;
        node = node->next;
    }
    node->data = *e;
    free(node);
    return 1;
}

int indexOfList(List* l, ItemType * e) {
    Node *node = createNode();
    node = l->first;
    int i = 0;
    while (node) {
        if (node->data == *e) {
            free(node);
            return i;
        }
        i++;
        node = node->next;
    }
    free(node);
    return -1;
}

int containsList(List* l, ItemType * e) {
    Node *node = createNode();
    node = l->first;
    int i = 0;
    while (node) {
        if (node->data == *e) {
            free(node);
            return i;
        }
        i++;
        node = node->next;
    }
    free(node);
    return -1;
}

int sizeList(List * l) {
    return l->size;
}

int isEmptyList(List * l) {
    return l->first == NULL;
}

void printList(List * l) {
    Node *node = createNode();
    node = l->first;
    while (node) {
        printf("%d, ", node->data);
        node = node->next;
    }
    printf("\n");
    free(node);
}