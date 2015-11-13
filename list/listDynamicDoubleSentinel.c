#include <stdio.h>
#include <stdlib.h>

#define ItemType int

typedef struct node {
    ItemType data;
    struct node *prev;
    struct node *next;
} Node;

typedef struct {
    Node *sentinel;
    int size;
} List;

typedef enum {
    false, true
} Boolean;

List *createList();
void initializeList(List *l);
Boolean addListLast(List *l, ItemType e);
Boolean addList(List* l, ItemType e, int index);
Boolean removeList(List* l, int index, ItemType *e);
Boolean removeListLast(List* l, ItemType* e);
Boolean getList(List* l, int index, ItemType* e);
Boolean setList(List* l, int index, ItemType e);
int indexOfList(List* l, ItemType* e);
Boolean containsList(List* l, ItemType *e);
int sizeList(List* l);
Boolean isEmptyList(List* l);
void printList(List* l);
void printBoolean(Boolean *b);

int main() {
    List *l = createList();
    initializeList(l);
    ItemType e = 123;
    Boolean b;
    addList(l, 123, 0);
    addList(l, 456, 1);
    addList(l, 789, 2);
    addListLast(l, 10);
    addListLast(l, 20);
    addListLast(l, 30);
    addListLast(l, 40);
    printf("Size: %d\n", sizeList(l));
    printList(l);

    removeList(l, 5, &e);
    removeList(l, 5, &e);
    removeList(l, 1, &e);
    addList(l, 123, 0);
    addList(l, 456, 1);
    addList(l, 789, 2);
    addListLast(l, 10);
    addListLast(l, 20);
    addListLast(l, 30);
    addListLast(l, 40);
    removeList(l, 2, &e);
    removeList(l, 1, &e);
    b = containsList(l, &e);
    printBoolean(&b);

    printList(l);
    removeListLast(l, &e);
    removeListLast(l, &e);
    removeListLast(l, &e);
    removeListLast(l, &e);
    addList(l, 123, 0);
    addList(l, 456, 1);
    addList(l, 789, 2);
    addListLast(l, 10);
    addListLast(l, 20);
    addListLast(l, 30);
    addListLast(l, 40);
    getList(l, 4, &e);
    printf("GET: %d\n", e);
    setList(l, 4, 854);
    getList(l, 1, &e);
    printf("GET: %d\n", e);
    printList(l);
}

List *createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List *l) {
    l->size = 0;
    l->sentinel = malloc(sizeof (Node));
    l->sentinel->next = NULL;
    l->sentinel->prev = NULL;
}

Boolean addListLast(List *l, ItemType e) {
    addList(l, e, l->size - 1);
}

Boolean addList(List* l, ItemType e, int index) {
    if (index < 0 || index >= l->size) {
        return false;
    }
    Node *node = (Node*) malloc(sizeof (Node));
    Node *aux;
    node->data = e;
    if (!l->sentinel->next) {//primeiro elemento
        node->next = NULL;
        node->prev = NULL;
        l->sentinel->next = node;
        l->sentinel->prev = node;
    } else if (index == 0) {//no começo
        aux = l->sentinel->next;
        node->next = aux;
        node->prev = NULL;
        aux->prev = node;
        l->sentinel->next = node;
    } else if (index == l->size - 1) {//no fim
        aux = l->sentinel->prev;
        aux->next = node;
        node->prev = aux;
        node->next = NULL;
        l->sentinel->prev = node;
    } else {//no meio
        aux = l->sentinel->next;
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
    return true;
}

Boolean removeListLast(List *l, ItemType *e) {
    return removeList(l, l->size - 1, e);
}

Boolean removeList(List *l, int index, ItemType *e) {
    if (isEmptyList(l)) {
        return false;
    }
    if (index < 0 || index >= l->size) {
        return false;
    }
    Node *removed, *aux;
    if (index == 0) {
        removed = l->sentinel->next;
        if (l->size == 1) {
            l->sentinel->next = NULL;
            l->sentinel->prev = NULL;
        } else {
            aux = removed->next;
            l->sentinel->next = aux;
            aux->prev = NULL;
        }
    } else if (index == l->size - 1) {
        removed = l->sentinel->prev;
        aux = removed->prev;
        aux->next = NULL;
        l->sentinel->prev = aux;
    } else {
        if (index < l->size / 2) {
            removed = l->sentinel->next;
            int i = 0;
            while (i < index) {
                removed = removed->next;
                i++;
            }
        } else {
            removed = l->sentinel->prev;
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
    return true;
}

Boolean getList(List* l, int index, ItemType* e) {
    if (l->size == 0) {
        return true;
    }
    int i;
    Node *get = l->sentinel->next;
    if (index < (l->size / 2)) {
        for (i = 0; i < index; i++) {
            get = get->next;
        }
        *e = get->data;
    } else {
        get = l->sentinel->prev;
        for (i = l->size; i > index; i--) {
            get = get->prev;
        }
        *e = get->next->data;
    }
    return false;
}

Boolean setList(List* l, int index, ItemType e) {
    if (l->size == 0) {
        return false;
    }
    int i;
    Node *set = l->sentinel->next;
    printf("\nindex: %d \n", index);
    if (index < (l->size / 2)) {
        for (i = 0; i < index; i++) {
            set = set->next;
        }
        set->data = e;
        printf("\ndata set: %d\n", set->next->data = e);
    } else {
        set = l->sentinel->prev;
        for (i = l->size; i > index; i--) {
            set = set->prev;
        }
        set->next->data = e;
        //        printf("\ndata set: %d\n", set->next->data = e);
    }
    return true;
};

int indexOfList(List* l, ItemType* e) {
    if (isEmptyList(l)) {
        return -1;
    }
    int i;
    Node *aux = l->sentinel->next;
    for (i = 0; i < l->size; i++) {
        if (aux->data == *e) {
            return i;
        }
        aux = aux->next;
    }
    return -1;
}

Boolean containsList(List* l, ItemType *e) {
    if (isEmptyList(l)) {
        return false;
    }
    return indexOfList(l, e) != -1;
}

Boolean isEmptyList(List* l) {
    return l->sentinel->next == NULL;
}

int sizeList(List* l) {
    return l->size;
}

void printList(List* l) {
    Node *i = l->sentinel->next;
    printf("- - - - print - - - - \n");
    while (i) {
        printf("%d\n", i->data);
        i = i->next;
    }
    printf("\n- - - - end print - - - - \n");
}

void printBoolean(Boolean *b) {
    if (*b == 1) {
        printf("true;\n");
    } else {
        printf("false;\n");
    }
}