#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"
#include "../include/list.h"
#include "../include/dyntable.h"
#include "../include/tree.h"
#include "../include/heap.h"

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
    // free(i1);
    // free(i2);
}


/**********************************************************************************
 * list_t test
 **********************************************************************************/

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


    // freeInt(i1);
    // freeInt(i2);
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
    // delete_list(l, freeInt);
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
    // delete_list(l, freeInt);
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
    // delete_list(l, freeInt);
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

/**********************************************************************************
 * dyntable_t test
 **********************************************************************************/

void testDyntableCreation()
{
    int* i1 = malloc(sizeof(int));
    *i1 = 7;
    struct dyn_table_t* table = new_dyn_table();
    assert(table->size == 1 && table->used == 0);
    table->T[0] = i1;
    table->used = 1;
    assert(get_dyn_table_data(table, 0) == i1);
    // freeInt(i1);
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
    // delete_dyn_table(table, freeInt);
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

/**********************************************************************************
 * tree_t test
 **********************************************************************************/

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
    // freeInt(i1);
    // freeInt(i2);
    // freeInt(i3);
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
    // delete_tree(t, freeInt);
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
    // view_preorder(get_tree_root(t), viewInt);
    // view_inorder(get_tree_root(t), viewInt);
    // view_postorder(get_tree_root(t), viewInt);
    // printf("\n");
    // view_tree(t, viewInt, 0);
    // view_tree(t, viewInt, 1);
    // view_tree(t, viewInt, 2);
    // view_tree(t, viewInt, 3);
    // delete_tree(t, freeInt);
}

void testInsertAndgetNodeDataAndRemoveTree()
{
    int* i0 = calloc(1, sizeof(int));
    *i0 = 0;
    int* i1 = calloc(1, sizeof(int));
    *i1 = 1;
    int* i2 = calloc(1, sizeof(int));
    *i2 = 2;
    int* i3 = calloc(1, sizeof(int));
    *i3 = 3;
    int* i4 = calloc(1, sizeof(int));
    *i4 = 4;
    int* i5 = calloc(1, sizeof(int));
    *i5 = 5;
    int* i6 = calloc(1, sizeof(int));
    *i6 = 6;
    int* i7 = calloc(1, sizeof(int));
    *i7 = 7;
    // int* i8 = calloc(1, sizeof(int));
    // *i8 = 8;
    // int* i9 = calloc(1, sizeof(int));
    // *i9 = 9;

    struct tree_t* t = new_tree();
    tree_insert(t, i0);


    assert(get_tree_size(t)==1);
    assert(get_tree_node_data(get_tree_root(t))==i0);
    // view_tree(t, viewInt, 0);

    tree_insert(t, i1);
    assert(get_tree_size(t) == 2);
    assert(get_tree_node_data(get_left(get_tree_root(t)))==i1);

    tree_insert(t, i2);
    assert(get_tree_size(t)==3);
    assert(get_tree_node_data(get_right(get_tree_root(t)))==i2);

    tree_insert(t, i3);
    assert(get_tree_size(t)==4);
    assert(get_tree_node_data(get_left(get_left(get_tree_root(t))))==i3);

    tree_insert(t, i4);
    assert(get_tree_size(t)==5);
    assert(get_tree_node_data(get_right(get_left(get_tree_root(t))))==i4);

    tree_insert(t, i5);
    assert(get_tree_size(t)==6);
    assert(get_tree_node_data(get_left(get_right(get_tree_root(t))))==i5);

    tree_insert(t, i6);
    assert(get_tree_size(t)==7);
    assert(get_tree_node_data(get_right(get_right(get_tree_root(t))))==i6);

    tree_insert(t, i7);
    assert(get_tree_size(t)==8);
    assert(get_tree_node_data(get_left(get_left(get_left(get_tree_root(t)))))==i7);

    assert(get_tree_node_data(tree_find_node(t,0)) == i0);
    assert(get_tree_node_data(tree_find_node(t,1)) == i1);
    assert(get_tree_node_data(tree_find_node(t,2)) == i2);
    assert(get_tree_node_data(tree_find_node(t,3)) == i3);
    assert(get_tree_node_data(tree_find_node(t,4)) == i4);
    assert(get_tree_node_data(tree_find_node(t,5)) == i5);
    assert(get_tree_node_data(tree_find_node(t,6)) == i6);
    assert(get_tree_node_data(tree_find_node(t,7)) == i7);
    assert(get_tree_node_data(tree_find_node(t,0)) != i4);

    assert(tree_remove(t)==i7);
    assert(get_tree_size(t)==7);

    assert(tree_remove(t)==i6);
    assert(get_tree_size(t)==6);

    assert(tree_remove(t)==i5);
    assert(get_tree_size(t)==5);

    assert(tree_remove(t)==i4);
    assert(get_tree_size(t)==4);

    assert(tree_remove(t)==i3);
    assert(get_tree_size(t)==3);

    assert(tree_remove(t)==i2);
    assert(get_tree_size(t)==2);

    assert(tree_remove(t)==i1);
    assert(get_tree_size(t)==1);

    assert(tree_remove(t)==i0);
    assert(get_tree_size(t)==0);

    // delete_tree(t,freeInt);
    // view_tree(t, viewInt, 0);
    // view_tree(t, viewInt, 1);
    // view_tree(t, viewInt, 2);
}

void testTreeSwapData()
{
    int* i1 = malloc(sizeof(int));
    int* i2 = malloc(sizeof(int));
    struct tree_node_t* node1 = new_tree_node(i1);
    struct tree_node_t* node2 = new_tree_node(i2);
    assert(get_tree_node_data(node1)!= i2);
    assert(get_tree_node_data(node2) !=i1);
    tree_swap_nodes_data(node1, node2);
    assert(get_tree_node_data(node1) == i2);
    assert(get_tree_node_data(node2) == i1);
}

/**********************************************************************************
 * heap_node_t test
 **********************************************************************************/

void testGetteurAndSetteurHeapNode()
{
    int* i1 = calloc(1, sizeof(int));
    *i1 = 3;
    unsigned long key = 0;
    struct heap_node_t* node = new_heap_node(key, i1);
    assert(get_heap_node_data(node)==i1);
    assert(get_heap_node_key(node)==key);
    unsigned int dictPos = 2;
    set_heap_node_dict_position(node, dictPos);
    assert(get_heap_node_dict_position(node)==dictPos);
    // view_heap_node(node, viewInt);
}

void testHeapBourrin()
{
    int* i1 = calloc(1, sizeof(int));
    *i1 = 3;
    unsigned long key1 = 1;
    unsigned int dictPos1 = 0;
    struct heap_node_t* heapNode1 = new_heap_node(key1, i1);

    int* i2 = calloc(1, sizeof(int));
    *i2 = 7;
    unsigned long key2 = 2;
    unsigned int dictPos2 = 1;
    struct heap_node_t* heapNode2 = new_heap_node(key2, i2);

    int* i3 = calloc(1, sizeof(int));
    *i3 = 9;
    unsigned long key3 = 3;
    unsigned int dictPos3 = 0;
    struct heap_node_t* heapNode3 = new_heap_node(key3, i3);

    int heapListType = 2;
    struct heap_t* H = new_heap(heapListType);
    struct list_t* heapList = get_heap(H);
    // list_insert_first(heapList, heapNode1);
    // view_list_heap(H, viewInt);
    // list_insert_first(heapList, heapNode2);
    // view_list_heap(H, viewInt);
}

void testListHeapInsert()
{
    int* data1 = calloc(1, sizeof(int));
    *data1 = 4;
    unsigned long key1 = 5;

    int* data2 = calloc(1, sizeof(int));
    *data2 = 9;
    unsigned long key2 = 10;

    int* data3 = calloc(1, sizeof(int));
    *data3 = 9;
    unsigned long key3 = 0;

    int* data4 = calloc(1, sizeof(int));
    *data4 = 5;
    unsigned long key4 = 2;

    int* data5 = calloc(1, sizeof(int));
    *data5 = 7;
    unsigned long key5 = 7;

    struct heap_t* H = new_heap(2);
    struct list_t* heapList = get_heap(H);
    struct dyn_table_t* dict = get_heap_dictionary(H);

    assert(list_heap_insert(H,key1,data1) == 0);
    assert(get_heap_node_data(get_list_node_data(get_list_head(heapList))) == data1);
    assert(get_heap_node_data(get_list_node_data(get_list_tail(heapList)))==data1);
    assert(get_heap_node_dict_position(get_list_node_data(get_list_head(heapList)))==0);
    assert(get_heap_node_key(get_list_node_data(get_list_head(heapList))) == key1);
    assert(get_dyn_table_used(dict)==1);
    assert(get_dyn_table_size(dict)==1);
    assert(get_dyn_table_data(dict,0) == get_list_head(heapList));
    // view_list_heap(H, viewInt);

    assert(list_heap_insert(H,key2,data2)==1);
    assert(get_heap_node_data(get_list_node_data(get_list_tail(heapList)))==data2);
    assert(get_heap_node_data(get_list_node_data(get_list_tail(heapList)))!=data1);
    assert(get_heap_node_dict_position(get_list_node_data(get_list_tail(heapList)))==1);
    assert(get_heap_node_key(get_list_node_data(get_list_tail(heapList)))==key2);
    assert(get_dyn_table_used(dict)==2);
    assert(get_dyn_table_size(dict)==2);
    assert(get_dyn_table_data(dict,1)==get_list_tail(heapList));
    // view_list_heap(H, viewInt);

    assert(list_heap_insert(H,key3,data3)==2);
    assert(get_heap_node_data(get_list_node_data(get_list_head(heapList)))==data3);
    assert(get_heap_node_key(get_list_node_data(get_list_head(heapList)))==key3);
    assert(get_heap_node_dict_position(get_list_node_data(get_list_head(heapList)))==2);
    assert(get_dyn_table_used(dict)==3);
    assert(get_dyn_table_size(dict)==4);
    assert(get_dyn_table_data(dict,2)==get_list_head(heapList));
    // view_list_heap(H,viewInt);

    assert(list_heap_insert(H,key4,data4)==3);
    assert(get_heap_node_data(get_list_node_data(get_successor(get_list_head(heapList)))) == data4);
    assert(get_heap_node_key(get_list_node_data(get_successor(get_list_head(heapList)))) == key4);
    assert(get_heap_node_dict_position(get_list_node_data(get_successor(get_list_head(heapList))))==3);
    assert(get_dyn_table_used(dict) == 4);
    assert(get_dyn_table_size(dict) == 4);
    assert(get_dyn_table_data(dict,3) == get_successor(get_list_head(heapList)));
    // view_list_heap(H, viewInt);
    // view_dyn_table(dict,viewHeapNodeIntInListNode);

    assert(get_heap_node_data(list_heap_extract_min(H))==data3);
    assert(get_list_size(heapList)==3);
    assert(get_dyn_table_data(dict,2)==NULL);
    assert(get_dyn_table_used(dict) == 4);
    // view_list_heap(H, viewInt);

    assert(get_heap_node_data(list_heap_extract_min(H))==data4);
    assert(get_list_size(heapList)==2);
    assert(get_dyn_table_data(dict,3)==NULL);


    assert(get_heap_node_data(list_heap_extract_min(H))==data1);
    assert(get_list_size(heapList)==1);
    assert(get_dyn_table_data(dict,0)==NULL);
    // view_list_heap(H, viewInt);
    // view_dyn_table(dict,viewHeapNodeIntInListNode);

    assert(get_heap_node_data(list_heap_extract_min(H))==data2);
    assert(get_list_size(heapList)==0);
    assert(list_is_empty(heapList));
    assert(get_dyn_table_data(dict,2)==NULL);

    view_list_heap(H, viewInt);
    // view_dyn_table(dict,viewHeapNodeIntInListNode);

    list_heap_insert(H, key5, data5);
    // view_list_heap(H, viewInt);
    // view_dyn_table(dict,viewHeapNodeIntInListNode);
}

void testIncreaseListHeapPriority()
{
    int* data1 = calloc(1, sizeof(int));
    *data1 = 4;
    unsigned long key1 = 5;

    int* data2 = calloc(1, sizeof(int));
    *data2 = 9;
    unsigned long key2 = 10;

    int* data3 = calloc(1, sizeof(int));
    *data3 = 5;
    unsigned long key3 = 15;

    int* data4 = calloc(1, sizeof(int));
    *data4 = 5;
    unsigned long key4 = 2;

    struct heap_t* H = new_heap(2);
    struct list_t* heapList = get_heap(H);
    struct dyn_table_t* dict = get_heap_dictionary(H);

    assert(list_heap_is_empty(H));

    list_heap_insert(H, key1, data1);
    list_heap_increase_priority(H, 0, 3);
    assert(!list_heap_is_empty(H));
    assert(get_heap_node_key(get_list_node_data(get_list_head(heapList)))==3);
    assert(get_heap_node_data(get_list_node_data(get_list_head(heapList)))==data1);
    assert(get_heap_node_dict_position(get_list_node_data(get_list_head(heapList)))==0);
    assert(get_dyn_table_data(dict,0)==get_list_head(heapList));
    // view_list_heap(H,viewInt);
    // view_dyn_table(dict,viewHeapNodeIntInListNode);
    list_heap_insert(H, key2, data2);
    // view_list_heap(H, viewInt);
    // view_dyn_table(dict, viewHeapNodeIntInListNode);
    list_heap_increase_priority(H, 1, 2);
    assert(get_heap_node_key(get_list_node_data(get_list_head(heapList)))==2);
    assert(get_heap_node_data(get_list_node_data(get_list_tail(heapList)))==data1);
    assert(get_heap_node_data(get_list_node_data(get_list_head(heapList)))==data2);
    assert(get_dyn_table_data(dict,0) == get_list_tail(heapList));
    assert(get_dyn_table_data(dict,1) == get_list_head(heapList));

    // view_list_heap(H,viewInt);
    // view_dyn_table(dict,viewHeapNodeIntInListNode);

    list_heap_insert(H, key3, data3);
    list_heap_increase_priority(H, 2, 1);

    assert(get_heap_node_key(get_list_node_data(get_list_head(heapList)))==1);
    assert(get_heap_node_data(get_list_node_data(get_successor(get_list_head(heapList))))==data2);
    assert(get_dyn_table_data(dict,2)==get_list_head(heapList));
    assert(get_heap_node_key(get_list_node_data(get_predecessor(get_list_tail(heapList))))==2);
    // view_list_heap(H, viewInt);
    // view_dyn_table(dict, viewHeapNodeIntInListNode);

    list_heap_increase_priority(H, 0, 1);

    // view_list_heap(H, viewInt);
    // view_dyn_table(dict, viewHeapNodeIntInListNode);
}

void testInsertdynTableHeap()
{
    int* data1 = calloc(1, sizeof(int));
    *data1 = 4;
    unsigned long key1 = 5;

    int* data2 = calloc(1, sizeof(int));
    *data2 = 9;
    unsigned long key2 = 10;

    int* data3 = calloc(1, sizeof(int));
    *data3 = 5;
    unsigned long key3 = 1;

    int* data4 = calloc(1, sizeof(int));
    *data4 = 6;
    unsigned long key4 = 0;


    struct heap_t* h = new_heap(0);
    struct dyn_table_t* dynTableHeap = get_heap(h);
    struct dyn_table_t* dict = get_heap_dictionary(h);

    assert(get_dyn_table_size(dynTableHeap)==1);
    assert(get_dyn_table_used(dynTableHeap)==0);
    assert(dyn_table_heap_insert(h, key1, data1)==0);
    assert(get_dyn_table_size(dynTableHeap)==1);
    assert(get_dyn_table_used(dynTableHeap)==1);
    assert(get_dyn_table_data(dynTableHeap,*(int*)get_dyn_table_data(dict,0))== get_dyn_table_data(dynTableHeap,0));
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict,viewInt);

    assert(dyn_table_heap_insert(h,key2,data2)==1);
    assert(get_dyn_table_data(dynTableHeap,*(int*)get_dyn_table_data(dict,1))== get_dyn_table_data(dynTableHeap,1));
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict,viewInt);


    assert(dyn_table_heap_insert(h,key3,data3)==2);
    assert(get_dyn_table_data(dynTableHeap,*(int*)get_dyn_table_data(dict,0))== get_dyn_table_data(dynTableHeap,2));
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(dyn_table_heap_insert(h,key4,data4)==3);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);
}

void testExtracMinDyntableHeap()
{
    int* data1 = calloc(1, sizeof(int));
    *data1 = 4;
    unsigned long key1 = 5;

    int* data2 = calloc(1, sizeof(int));
    *data2 = 9;
    unsigned long key2 = 10;

    int* data3 = calloc(1, sizeof(int));
    *data3 = 5;
    unsigned long key3 = 1;

    int* data4 = calloc(1, sizeof(int));
    *data4 = 6;
    unsigned long key4 = 0;


    struct heap_t* h = new_heap(0);
    struct dyn_table_t* dynTableHeap = get_heap(h);
    struct dyn_table_t* dict = get_heap_dictionary(h);

    assert(dyn_table_heap_insert(h,key1,data1) == 0);
    assert(!dyn_table_heap_is_empty(h));
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(get_heap_node_data(dyn_table_heap_extract_min(h)) == data1);
    assert(get_dyn_table_data(dict,0) == NULL);
    assert(dyn_table_heap_is_empty(h));
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(dyn_table_heap_insert(h,key1,data1) == 0);
    assert(get_heap_node_dict_position(get_dyn_table_data(dynTableHeap,0)) == 1);
    assert(get_dyn_table_size(dict)==2);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(dyn_table_heap_insert(h,key2,data2)==1);
    assert(get_heap_node_dict_position(get_dyn_table_data(dynTableHeap,1)) == 2);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(get_heap_node_data(dyn_table_heap_extract_min(h))==data1);
    assert(get_dyn_table_used(dict)==3);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(dyn_table_heap_insert(h,key3,data3)==1);
    assert(dyn_table_heap_insert(h,key4,data4)==2);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(get_heap_node_data(dyn_table_heap_extract_min(h))==data4);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);
}

void testDynTableIncreasePriority()
{
    int* data1 = calloc(1, sizeof(int));
    *data1 = 4;
    unsigned long key1 = 5;

    int* data2 = calloc(1, sizeof(int));
    *data2 = 9;
    unsigned long key2 = 10;

    int* data3 = calloc(1, sizeof(int));
    *data3 = 5;
    unsigned long key3 = 6;

    int* data4 = calloc(1, sizeof(int));
    *data4 = 6;
    unsigned long key4 = 15;


    struct heap_t* h = new_heap(0);
    struct dyn_table_t* dynTableHeap = get_heap(h);
    struct dyn_table_t* dict = get_heap_dictionary(h);

    dyn_table_heap_insert(h, key1, data1);
    dyn_table_heap_increase_priority(h, 0, 4);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    assert(get_heap_node_key(get_dyn_table_data(dynTableHeap,0))== 4);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    dyn_table_heap_insert(h, key2, data2);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);
    dyn_table_heap_increase_priority(h, 1, 3);
    assert(get_heap_node_key(get_dyn_table_data(dynTableHeap,0))==3);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    dyn_table_heap_insert(h, key3, data3);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);
    dyn_table_heap_increase_priority(h, 2, 2);
    assert(get_heap_node_key(get_dyn_table_data(dynTableHeap,0))==2);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);

    dyn_table_heap_insert(h, key4, data4);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);
    dyn_table_heap_increase_priority(h, 2, 1);
    assert(get_heap_node_key(get_dyn_table_data(dynTableHeap,0))==1);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);
    dyn_table_heap_increase_priority(h, 3, 2);
    assert(get_heap_node_key(get_dyn_table_data(dynTableHeap,1))==2);
    // view_dyn_table(dynTableHeap, viewHeapNode);
    // view_dyn_table(dict, viewInt);
}


void testViewDyntableHeap()
{
    int* data1 = calloc(1, sizeof(int));
    *data1 = 4;
    unsigned long key1 = 5;

    int* data2 = calloc(1, sizeof(int));
    *data2 = 9;
    unsigned long key2 = 10;

    int* data3 = calloc(1, sizeof(int));
    *data3 = 5;
    unsigned long key3 = 6;

    int* data4 = calloc(1, sizeof(int));
    *data4 = 6;
    unsigned long key4 = 15;

    int* data5 = calloc(1, sizeof(int));
    *data4 = 7;
    unsigned long key5 = 1;
    struct heap_t* h = new_heap(0);
    struct dyn_table_t* dynTableHeap = get_heap(h);
    dyn_table_heap_insert(h, key1, data1);
    dyn_table_heap_insert(h, key2, data2);
    dyn_table_heap_insert(h, key3, data3);
    dyn_table_heap_insert(h, key4, data4);
    dyn_table_heap_insert(h, key5, data5);

    // view_dyn_table_heap(h,viewHeapNode);
    // view_dyn_table(get_heap_dictionary(h),viewInt);
}

void testTreeHeapInsert()
{
    int* data1 = calloc(1, sizeof(int));
    *data1 = 4;
    unsigned long key1 = 5;

    int* data2 = calloc(1, sizeof(int));
    *data2 = 9;
    unsigned long key2 = 2;

    int* data3 = calloc(1, sizeof(int));
    *data3 = 5;
    unsigned long key3 = 6;

    int* data4 = calloc(1, sizeof(int));
    *data4 = 6;
    unsigned long key4 = 15;

    int* data5 = calloc(1, sizeof(int));
    *data5 = 7;

    struct heap_t* h = new_heap(2);
    struct tree_t* t = get_heap(h);
    struct dyn_table_t* dict = get_heap_dictionary(h);
    assert(tree_heap_insert(h,key1,data1) == 0);
    assert(get_tree_size(t)==1);
    assert(*(int*)get_dyn_table_data(dict,0)==0);
    // view_tree_heap(h,viewHeapNode);
    // view_dyn_table(dict,viewInt);

    assert(tree_heap_insert(h,key2,data2)==1);
    assert(get_tree_size(t)==2);
    assert(*(int*)get_dyn_table_data(dict,0)==1);
    assert(*(int*)get_dyn_table_data(dict,1)==0);
    view_tree_heap(h,viewHeapNode);
    view_dyn_table(dict,viewInt);
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
    // runTest("testInsertEtRemoveDyntable", testInsertEtRemoveDyntable);
    runTest("testGetteurEtSetteurNodeTree", testGetteurEtSetteurNodeTree);
    runTest("testGetteurAndSetteurTree", testGetteurAndSetteurTree);
    runTest("Test views tree", testViewsTree);
    runTest("Test insert, get at position and remove tree", testInsertAndgetNodeDataAndRemoveTree);
    runTest("Test swap tree data", testTreeSwapData);
    runTest("Test setteur et getteur heapNode", testGetteurAndSetteurHeapNode);
    runTest("Test heap bourrin", testHeapBourrin);
    runTest("Test list heap insert", testListHeapInsert);
    runTest("Test list heap increase priority", testIncreaseListHeapPriority);
    runTest("Test test Insert dynTableHeap", testInsertdynTableHeap);
    runTest("Test testExtracMinDyntableHeap", testExtracMinDyntableHeap);
    runTest("Test testDynTableIncreasePriority", testDynTableIncreasePriority);
    runTest("Test view dyn truc heap", testViewDyntableHeap);
    runTest("Test testTreeHeapInsert", testTreeHeapInsert);
    return 0;
}
