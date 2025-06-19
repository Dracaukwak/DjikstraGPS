#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"


struct list_node_t *new_list_node(void *data) {
    struct list_node_t *newListNode = calloc(1, sizeof(struct list_node_t));
    assert(newListNode);
    newListNode->data = data;
    return newListNode;
}

void *get_list_node_data(const struct list_node_t *node) {
    assert(node);
    return node->data;
}

struct list_node_t *get_successor(const struct list_node_t *node) {
    assert(node);
    return node->successor;
}

struct list_node_t *get_predecessor(const struct list_node_t *node) {
    assert(node);
    return node->predecessor;
}

void set_list_node_data(struct list_node_t *node, void *newData) {
    assert(node);
    node->data = newData;
}

void set_successor(struct list_node_t *node, struct list_node_t *newSuccessor) {
    assert(node);
    node->successor = newSuccessor;
}

void set_predecessor(struct list_node_t *node, struct list_node_t *newPredecessor) {
    assert(node);
    node->predecessor = newPredecessor;
}

struct list_t *new_list() {
    struct list_t *newList = calloc(1, sizeof(struct list_t));
    assert(newList);
    return newList;
}

int list_is_empty(const struct list_t *L) {
    assert(L);
    return L->size == 0;
}

unsigned int get_list_size(const struct list_t *L) {
    assert(L);
    return L->size;
}


struct list_node_t *get_list_head(const struct list_t *L) {
    assert(L);
    return L->head;
}


struct list_node_t *get_list_tail(const struct list_t *L) {
    assert(L);
    return L->tail;
}


void increase_list_size(struct list_t *L) {
    assert(L);
    L->size++;
}


void decrease_list_size(struct list_t *L) {
    assert(L);
    L->size--;
}


void set_list_size(struct list_t *L, unsigned int newSize) {
    assert(L && newSize >= 0);
    L->size = newSize;
}


void set_list_head(struct list_t *L, struct list_node_t *newHead) {
    assert(L);
    L->head = newHead;
}


void set_list_tail(struct list_t *L, struct list_node_t *newTail) {
    assert(L);
    L->tail = newTail;
}

void delete_list(struct list_t *L, void (*freeData)(void *)) {
    assert(L);
    if (freeData) {
        for (struct list_node_t *it = get_list_head(L); it != NULL;) {
            freeData(get_list_node_data(it));
            struct list_node_t *aux = it;
            it = get_successor(it);
            free(aux);
        }
    } else {
        for (struct list_node_t *it = get_list_head(L); it != NULL;) {
            struct list_node_t *aux = it;
            it = get_successor(it);
            free(aux);
        }
    }
    free(L);
}

void view_list(const struct list_t *L, void (*viewData)(const void *)) {
    assert(L);
    printf("Nombre de noeud de la liste : %u\n", get_list_size(L));
    printf("(");
    for (struct list_node_t *it = get_list_head(L); it != NULL; it = get_successor(it)) {
        viewData(get_list_node_data(it));
        if (get_successor(it)) {
            printf(", ");
        }

    }
    printf(")\n");
}

void list_insert_first(struct list_t *L, void *data) {
    assert(L);
    struct list_node_t *newHead = new_list_node(data);
    if (list_is_empty(L)) {
        set_list_tail(L, newHead);
    } else {
        set_successor(newHead, get_list_head(L));
        set_predecessor(get_list_head(L), newHead);
    }
    set_list_head(L, newHead);
    increase_list_size(L);
}

void list_insert_last(struct list_t *L, void *data) {
    assert(L);
    struct list_node_t *newTail = new_list_node(data);
    if (list_is_empty(L)) {
        set_list_head(L, newTail);
    } else {
        set_predecessor(newTail, get_list_tail(L));
        set_successor(get_list_tail(L), newTail);
    }
    set_list_tail(L, newTail);
    increase_list_size(L);
}

void list_insert_after(struct list_t *L, void *data, struct list_node_t *node) {
    assert(L);

    if (list_is_empty(L)) {
        list_insert_first(L, data);
    } else if (get_list_tail(L) == node) {
        list_insert_last(L, data);

    } else {
        struct list_node_t *newNode = new_list_node(data);
        set_successor(newNode, get_successor(node));
        set_predecessor(get_successor(node), newNode);
        set_successor(node, newNode);
        set_predecessor(newNode, node);
        increase_list_size((L));
    }

}

void *list_remove_first(struct list_t *L) {
    assert(L);
    struct list_node_t *delNode = get_list_head(L);
    void *data = get_list_node_data(delNode);
    if (get_list_size(L) == 1) {
        set_list_head(L, NULL);
        set_list_tail(L, NULL);
    } else {
        set_list_head(L, get_successor(get_list_head(L)));
        set_predecessor(get_list_head(L), NULL);
    }
    decrease_list_size(L);
    free(delNode);
    return data;
}

void *list_remove_last(struct list_t *L) {
    assert(L);
    struct list_node_t *previousTail = get_list_tail(L);
    void *data = get_list_node_data(previousTail);
    if (get_list_size(L) == 1) {
        set_list_head(L, NULL);
        set_list_tail(L, NULL);
    } else {
        set_list_tail(L, get_predecessor(previousTail));
        set_successor(get_list_tail(L), NULL);
    }
    decrease_list_size(L);
    free(previousTail);
    return data;

}

void *list_remove_node(struct list_t *L, struct list_node_t *node) {
    assert(L);
    if (node == get_list_head(L)) {
        return list_remove_first(L);
    } else if (node == get_list_tail(L)) {
        return list_remove_last(L);
    } else {
        void *data = get_list_node_data(node);
        set_successor(get_predecessor(node), get_successor(node));
        set_predecessor(get_successor(node), get_predecessor(node));
        decrease_list_size(L);
        free(node);
        return data;
    }
}

void list_swap_nodes_data(struct list_node_t *node1, struct list_node_t *node2) {
    assert(node1 && node2);
    void *aux = get_list_node_data(node1);
    set_list_node_data(node1, get_list_node_data(node2));
    set_list_node_data(node2, aux);
}

int list_data_exist(struct list_t *L, void *data) {
    assert(L);
    for (struct list_node_t *it = get_list_head(L); it != NULL; it = get_successor(it)) {
        if (get_list_node_data(it) == data) {
            return 1;
        }
    }
    return 0;
}