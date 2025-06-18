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

void set_predecessor(struct list_node_t * node, struct list_node_t * newPredecessor){
    assert(node);
    node->predecessor = newPredecessor;
}

struct list_t * new_list(){
    struct list_t * newList = calloc(1, sizeof(struct list_t*));
    assert(newList);
    return newList;
}

int list_is_empty(const struct list_t * L){
    assert(L);
    return (unsigned int)L->size;
}