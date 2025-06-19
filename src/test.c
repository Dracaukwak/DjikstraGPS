#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"
#include "../include/list.h"


void runTest(const char *name, void(*testFunc)()) {
    printf("Running test: %s ...\n", name);
    fflush(stdout);
    testFunc();
    printf("%s PASSED\n", name);
}

void testUtils() {
    int *i1 = malloc(sizeof(int));
    int *i2 = malloc(sizeof(int));
    *i1 = 7;
    *i2 = 5;
    assert(intGreaterThan(i1, i2));
    assert(!intGreaterThan(i2, i1));
    assert(!intEqualTo(i2, i1));
    assert(intSmallerThan(i2, i1));
    free(i1);
    free(i2);
}

void testListNode() {
    int *i1 = malloc(sizeof(int));
    *i1 = 4;
    struct list_node_t *node1 = new_list_node(i1);
    int *i2 = malloc(sizeof(int));
    *i2 = 7;
    struct list_node_t *node2 = new_list_node(i2);
    set_successor(node1, node2);
    set_predecessor(node2, node1);

    assert(*(int *) get_list_node_data(node1) == 4);
    set_list_node_data(node2, i1);
    assert(get_list_node_data(node2) == i1);
    assert(*(int *) get_list_node_data(node1) != 7);
    assert(get_successor(node1) == node2);
    assert(get_predecessor(node2) == node1);
    assert(get_predecessor(node1) != node2);
}

void testGetteurAndSetteurList() {
    int *i1 = malloc(sizeof(int));
    *i1 = 4;
    int *i2 = malloc(sizeof(int));
    *i2 = -9;
    struct list_t *l = new_list();
    struct list_node_t *node1 = new_list_node(i1);
    struct list_node_t *node2 = new_list_node(i2);

    assert(list_is_empty(l));
    assert(get_list_size(l) == 0);
    set_list_head(l, node1);
    set_list_tail(l, node2);
    increase_list_size(l);
    increase_list_size(l);
    assert(get_list_size(l) == 2);
    assert(get_list_head(l) == node1);
    assert(get_list_tail(l) != node1);
    assert(get_list_head(l) != node2);
    assert(get_list_tail(l) == node2);


    freeInt(i1);
    freeInt(i2);
}

int main() {
    runTest("utils.c", testUtils);
    runTest("listNode", testListNode);
    runTest("liste getteurAndsetteur",testGetteurAndSetteurList);
}