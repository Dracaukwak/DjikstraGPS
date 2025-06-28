#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"
#include "../include/list.h"
#include "../include/dyntable.h"
#include "../include/tree.h"

void afficheEtoile()
{
    int n = 10;
    for (int i = 0; i < n; i++)
    {
        printf("*");
    }
    printf("\n");
}

void runTest(const char* name, void (*testFunc)())
{
    printf("Running test: %s ...\n", name);
    fflush(stdout);
    testFunc();
    printf("%s PASSED\n\n", name);
}

void testUtils()
{
    int* i1 = malloc(sizeof(int));
    int* i2 = malloc(sizeof(int));
    *i1 = 7;
    *i2 = 5;
    assert(intGreaterThan(i1, i2));
    assert(!intGreaterThan(i2, i1));
    assert(!intEqualTo(i2, i1));
    assert(intSmallerThan(i2, i1));
    free(i1);
    free(i2);
}

void testListNode()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    struct list_node_t* node1 = new_list_node(i1);
    int* i2 = malloc(sizeof(int));
    *i2 = 7;
    struct list_node_t* node2 = new_list_node(i2);
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

void testGetteurAndSetteurList()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    struct list_t* l = new_list();
    struct list_node_t* node1 = new_list_node(i1);
    struct list_node_t* node2 = new_list_node(i2);

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
    assert(!list_is_empty(l));


    freeInt(i1);
    freeInt(i2);
}

void testViewAndDeleteList()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    struct list_t* l = new_list();
    struct list_node_t* node1 = new_list_node(i1);
    struct list_node_t* node2 = new_list_node(i2);
    //view_list(l, viewInt);
    set_list_head(l, node1);
    set_successor(node1, node2);
    set_list_tail(l, node2);

    //view_list(l, viewInt);
    delete_list(l, freeInt);
}

void testInsertFirstList()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    struct list_t* l = new_list();
    list_insert_first(l, i1);
    assert(get_list_size(l) == 1);
    assert(get_list_node_data(get_list_head(l)) == i1);
    assert(get_list_node_data(get_list_tail(l)) == i1);
    list_insert_first(l, i2);
    assert(get_list_size(l) == 2);
    assert(get_list_node_data(get_list_head(l)) == i2);
    assert(get_list_node_data(get_list_tail(l)) == i1);
    assert(get_successor(get_list_head(l)) == get_list_tail(l));
    assert(get_predecessor(get_list_tail(l)) == get_list_head(l));
    delete_list(l, freeInt);
}

void testInsertLastList()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    struct list_t* l = new_list();
    list_insert_last(l, i1);
    assert(get_list_size(l) == 1);
    assert(get_list_node_data(get_list_head(l)) == i1);
    assert(get_list_node_data(get_list_tail(l)) == i1);
    list_insert_last(l, i2);
    assert(get_list_node_data(get_list_tail(l)) != i1);
    assert(get_list_node_data(get_list_head(l)) == i1);
    assert(get_list_node_data(get_list_tail(l)) == i2);
    assert(get_list_size(l) == 2);
    assert(get_predecessor(get_list_tail(l)) == get_list_head(l));
    assert(get_successor(get_list_head(l)) == get_list_tail(l));
    delete_list(l, freeInt);
}

void testListInsertAfter()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    int* i3 = malloc(sizeof(int));
    *i3 = 10;
    struct list_t* l = new_list();
    list_insert_first(l, i1);
    list_insert_after(l, i2, get_list_head(l));
    assert(get_list_size(l) == 2);
    assert(get_list_node_data(get_list_tail(l)) == i2);
    assert(get_successor(get_list_head(l)) == get_list_tail(l));
    assert(get_predecessor(get_list_tail(l)) == get_list_head(l));
    list_insert_after(l, i3, get_list_head(l));
    assert(get_list_size(l) == 3);
    assert(get_successor(get_list_head(l)) == get_predecessor(get_list_tail(l)));
    //view_list(l, viewInt);
}

void testlistRemove()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    int* i3 = malloc(sizeof(int));
    *i3 = 10;
    struct list_t* l = new_list();

    /* == Test remove first == */
    list_insert_first(l, i1);
    assert(list_remove_first(l) == i1);
    assert(list_is_empty(l));
    assert(get_list_head(l) == NULL);
    list_insert_first(l, i1);
    list_insert_first(l, i2);
    assert(list_remove_first(l) == i2);
    assert(get_list_size(l) == 1);
    assert(get_list_node_data(get_list_tail(l)) == i1);
    assert(get_list_node_data(get_list_tail(l)) == i1);

    /* == Test remove last == */
    list_insert_last(l, i2);
    list_insert_last(l, i3);
    assert(list_remove_last(l) == i3);
    assert(get_list_size(l) == 2);
    assert(get_list_node_data(get_list_tail(l)) == i2);
    assert(list_remove_last(l) == i2);
    assert(get_list_size(l) == 1);
    assert(get_list_node_data(get_list_tail(l)) == i1);
    assert(list_remove_last(l) == i1);
    assert(list_is_empty(l));
    assert(get_list_tail(l) == NULL);
    assert(get_list_head(l) == NULL);

    /* == Test remove node == */
    list_insert_last(l, i1);
    list_insert_last(l, i2);
    list_insert_last(l, i3);
    //view_list(l, viewInt);
    assert(list_remove_node(l, get_successor(get_list_head(l))) == i2);
    assert(get_list_size(l) == 2);
    assert(get_successor(get_list_head(l)) == get_list_tail(l));
    assert(get_predecessor(get_list_tail(l)) == get_list_head(l));
    //view_list(l, viewInt);
    assert(list_remove_node(l, get_list_tail(l)) == i3);
    assert(get_list_size(l) == 1);
    assert(get_successor(get_list_head(l)) == NULL);
    //view_list(l,viewInt);
    assert(list_remove_node(l, get_list_head(l)) == i1);
    assert(list_is_empty(l));
    //view_list(l,viewInt);
}

void testSwapAndExist()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    int* i3 = malloc(sizeof(int));
    *i3 = 10;
    struct list_t* l = new_list();
    list_insert_first(l, i1);
    list_insert_last(l, i2);
    list_insert_after(l, i3, get_list_tail(l));
    list_swap_nodes_data(get_list_tail(l), get_list_head(l));
    assert(get_list_node_data(get_list_tail(l)) == i1);
    assert(get_list_node_data(get_list_head(l)) == i3);
    assert(list_data_exist(l, i1));
    //view_list(l,viewInt);
    list_remove_last(l);
    assert(!list_data_exist(l, i1));
}

void testDyntableCreation()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 7;
    struct dyn_table_t* table = new_dyn_table();
    assert(table->size == 1 && table->used == 0);
    table->T[0] = i1;
    table->used = 1;
    assert(get_dyn_table_data(table, 0) == i1);
    freeInt(i1);
}

void testDyntableGetteurAndSetteur()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 7;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    struct dyn_table_t* table = new_dyn_table();
    set_dyn_table_data(table, 0, i1);
    increase_dyn_table_used(table);
    assert(get_dyn_table_used(table) == 1 && get_dyn_table_size(table) == 1);
    assert(get_dyn_table_data(table, 0) == i1);
    assert(dyn_table_is_full(table));

    set_dyn_table_size(table, 2);
    increase_dyn_table_used(table);
    set_dyn_table_data(table, 1, i2);
    assert(get_dyn_table_used(table) == 2 && get_dyn_table_size(table) == 2);
    //view_dyn_table(table, viewInt);
    assert(get_dyn_table_data(table, 1) == i2);
    assert(dyn_table_is_full(table));
    set_dyn_table_size(table, 8);
    assert(!dyn_table_is_quasi_empty(table));
    set_dyn_table_size(table, 12);
    assert(dyn_table_is_quasi_empty(table));
    decrease_dyn_table_used(table);
    assert(get_dyn_table_used(table) == 1);
    //view_dyn_table(table, viewInt);
    delete_dyn_table(table, freeInt);
}

void testInsertEtRemoveDyntable()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 7;
    int* i2 = malloc(sizeof(int));
    *i2 = -9;
    int* i3 = malloc(sizeof(int));
    *i3 = 10;
    struct dyn_table_t* table = new_dyn_table();
    dyn_table_insert(table, i1);
    assert(get_dyn_table_used(table) == 1);
    assert(get_dyn_table_data(table, 0) == i1);
    assert(get_dyn_table_size(table) == 1);
    dyn_table_insert(table, i2);
    assert(get_dyn_table_used(table) == 2);
    assert(get_dyn_table_data(table, 1) == i2);
    assert(get_dyn_table_size(table) == 2);
    dyn_table_insert(table, i3);
    assert(get_dyn_table_used(table) == 3);
    assert(get_dyn_table_data(table, 2) == i3);
    assert(get_dyn_table_size(table) == 4);
    dyn_table_swap_nodes_data(table, 1, 2);
    assert(get_dyn_table_data(table, 1) == i3);
    assert(get_dyn_table_data(table, 2) == i2);
    //view_dyn_table(table,viewInt);
    dyn_table_swap_nodes_data(table, 1, 2);
    assert(get_dyn_table_data(table, 1) == i2);
    assert(get_dyn_table_data(table, 2) == i3);
    set_dyn_table_size(table, 16);
    assert(get_dyn_table_size(table) == 16);
    assert(dyn_table_remove(table) == i3);
    assert(get_dyn_table_used(table) == 2);
    assert(get_dyn_table_size(table) == 8);
    assert(dyn_table_remove(table) == i2);
    //view_dyn_table(table, viewInt);
    assert(get_dyn_table_used(table) == 1);
    assert(get_dyn_table_size(table) == 4);
    assert(dyn_table_remove(table) == i1);
    assert(get_dyn_table_used(table) == 0);
    assert(get_dyn_table_size(table) == 2);
    //view_dyn_table(table, viewInt);
}

void testGetteurEtSetteurNodeTree()
{
    int* i1 = calloc(1, sizeof(int));
    *i1 = 13;
    int* i2 = calloc(1, sizeof(int));
    *i2 = 4;
    int* i3 = calloc(1, sizeof(int));
    *i3 = 8;
    struct tree_node_t* node1 = new_tree_node(i1);
    struct tree_node_t* node2 = new_tree_node(i2);
    struct tree_node_t* node3 = new_tree_node(i3);
    set_right(node1, node2);
    set_left(node1, node3);
    set_tree_node_data(node2, i1);
    assert(get_tree_node_data(node1) == i1);
    assert(get_left(node1)== node3);
    assert(get_right(node1) ==node2);
    assert(get_tree_node_data(get_left(node1)) == i3);
    assert(get_tree_node_data(node2) ==i1);
    freeInt(i1);
    freeInt(i2);
    freeInt(i3);
}

void testGetteurAndSetteurTree()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 4;
    struct tree_node_t* node1 = new_tree_node(i1);
    struct tree_t* t = new_tree();
    set_tree_root(t, node1);
    increase_tree_size(t);
    assert(get_tree_size(t) == 1);
    assert(get_tree_root(t)== node1);
    delete_tree(t, freeInt);
}

void testViewsTree()
{
    int* i1 = calloc(1, sizeof(int));
    *i1 = 1;
    int* i2 = calloc(1, sizeof(int));
    *i2 = 2;
    int* i3 = calloc(1, sizeof(int));
    *i3 = 3;
    int* i4 = calloc(1, sizeof(int));
    *i4 = 4;
    struct tree_node_t* node1 = new_tree_node(i1);
    struct tree_node_t* node2 = new_tree_node(i2);
    struct tree_node_t* node3 = new_tree_node(i3);
    struct tree_node_t* node4 = new_tree_node(i4);
    struct tree_t* t = new_tree();

    set_tree_root(t, node1);
    set_left(get_tree_root(t), node2);
    set_right(get_tree_root(t), node3);
    set_left(node2, node4);
    view_preorder(get_tree_root(t), viewInt);
    view_inorder(get_tree_root(t),viewInt);
    view_postorder(get_tree_root(t),viewInt);
    printf("\n");
    view_tree(t,viewInt,0);
    view_tree(t,viewInt,1);
    view_tree(t,viewInt,2);
    view_tree(t,viewInt,3);
    delete_tree(t, freeInt);
}

int main()
{
    runTest("utils.c", testUtils);
    runTest("listNode", testListNode);
    runTest("liste getteurAndsetteur", testGetteurAndSetteurList);
    runTest("test deleteList", testViewAndDeleteList);
    runTest("Test insertFirstList", testInsertFirstList);
    runTest("Test listInsertLast", testInsertLastList);
    runTest("Test listInsertAfter", testListInsertAfter);
    runTest("Test listRemove", testlistRemove);
    runTest("Test swap et exist", testSwapAndExist);
    runTest("Test dyntableCreation", testDyntableCreation);
    runTest("Test dyntable getteur et setteur", testDyntableGetteurAndSetteur);
    runTest("testInsertEtRemoveDyntable", testInsertEtRemoveDyntable);
    runTest("testGetteurEtSetteurNodeTree", testGetteurEtSetteurNodeTree);
    runTest("testGetteurAndSetteurTree", testGetteurAndSetteurTree);
    runTest("Test views tree", testViewsTree);
    return 0;
}
