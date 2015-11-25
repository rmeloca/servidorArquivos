#include <stdio.h>
#include <stdlib.h>
#include "header/listDynamic.h"

Node* createNode() {
    Node* node = (Node*) malloc(sizeof (Node));
    node->data = (ItemType*) malloc(sizeof (ItemType));
    return node;
}

List* createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List* l) {
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

int addListLast(List* l, ItemType* e) {
    return addList(l, e, l->size);
}

int addList(List* l, ItemType* e, int index) {
    if (index > sizeList(l) || index < 0) {
        return 0;
    }
    Node* node = createNode();
    node->data = (ItemType*) malloc(sizeof (ItemType));
    memcpy(node->data, e, sizeof (ItemType));

    node->next = NULL;
    if (isEmptyList(l)) {
        l->first = node;
        l->last = node;
    } else {
        Node* iterador = createNode();
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

int removeList(List* l, int index, ItemType* e) {
    if (index > l->size || index < 0) {
        return 0;
    }
    Node *node, *removed;
    printf("DEBUGrm ===\n");
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
    e = removed->data;
    free(node);
    free(removed);
    l->size--;
    return 1;
}

int removeElementList(List* l, ItemType* e) {
    return removeList(l, indexOfList(l, e), e);
}

int getList(List* l, int index, ItemType* e) {
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
    e = node->data;
    free(node);
    return 1;
}

int setList(List* l, int index, ItemType* e) {
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
    node->data = e;
    free(node);
    return 1;
}

int indexOfList(List* l, ItemType* e) {
    Node *node = createNode();
    node = l->first;
    int i = 0;
    while (node) {
        if (equals(node->data, e)) {
            free(node);
            return i;
        }
        i++;
        node = node->next;
    }
    free(node);
    return -1;
}

int equals(ItemType *e1, ItemType *e2) {
    return e1->tipo == e2->tipo;
}

int containsList(List* l, ItemType* e) {
    Node *node = createNode();
    node = l->first;
    int i = 0;
    while (node) {
        if (equals(node->data, e)) {
            free(node);
            return i;
        }
        i++;
        node = node->next;
    }
    free(node);
    return -1;
}

int sizeList(List* l) {
    return l->size;
}

int isEmptyList(List* l) {
    return l->first == NULL;
}

void printList(List* l) {
    Node *node = createNode();
    node = l->first;
    while (node) {
        printf("%p, ", node->data);
        node = node->next;
    }
    printf("\n");
    free(node);
}