#include "../include/heap.h"


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "../include/dyntable.h"
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/util.h"

/**********************************************************************************
 * heap_node_t
 **********************************************************************************/

struct heap_node_t* new_heap_node(unsigned long key, void* data)
{
    struct heap_node_t* newHeapNode = calloc(1, sizeof(struct heap_node_t));
    assert(newHeapNode);
    newHeapNode->data = data;
    newHeapNode->key = key;
    return newHeapNode;
}

unsigned long get_heap_node_key(const struct heap_node_t* node)
{
    assert(node);
    return node->key;
}


void* get_heap_node_data(const struct heap_node_t* node)
{
    assert(node);
    return node->data;
}


unsigned int get_heap_node_dict_position(const struct heap_node_t* node)
{
    assert(node);
    return node->dict_position;
}

void set_heap_node_key(struct heap_node_t* node, unsigned long newKey)
{
    assert(node);
    node->key = newKey;
}

void set_heap_node_data(struct heap_node_t* node, void* newData)
{
    assert(node);
    node->data = newData;
}

void set_heap_node_dict_position(struct heap_node_t* node, unsigned int newPosition)
{
    assert(node);
    node->dict_position = newPosition;
}


// type =
//    0 (Dynamic Table Heap)
//    1 (Complete Binary Tree Heap)
//    2 (Ordered List Heap)
struct heap_t* new_heap(int type)
{
    struct heap_t* H = calloc(1, sizeof(struct heap_t));
    if (H == NULL)
    {
        ShowMessage("heap:new_heap : The memory is full", 1);
        return NULL;
    }
    H->dict = new_dyn_table();
    switch (type)
    {
    // case 0:
    //     H->heap = new_dyn_table();
    //     H->heap_insert = dyn_table_heap_insert;
    //     H->heap_extract_min = dyn_table_heap_extract_min;
    //     H->heap_increase_priority = dyn_table_heap_increase_priority;
    //     H->heap_is_empty = dyn_table_heap_is_empty;
    //     H->view_heap = view_dyn_table_heap;
    //     H->delete_heap = delete_dyn_table_heap;
    //     break;
    // case 1:
    //     H->heap = new_tree();
    //     H->heap_insert = tree_heap_insert;
    //     H->heap_extract_min = tree_heap_extract_min;
    //     H->heap_increase_priority = tree_heap_increase_priority;
    //     H->heap_is_empty = tree_heap_is_empty;
    //     H->view_heap = view_tree_heap;
    //     H->delete_heap = delete_tree_heap;
    //     break;
    case 2:
        H->heap = new_list();
        H->heap_insert = list_heap_insert;
        // H->heap_extract_min = list_heap_extract_min;
        // H->heap_increase_priority = list_heap_increase_priority;
        // H->heap_is_empty = list_heap_is_empty;
        H->view_heap = view_list_heap;
        // H->delete_heap = delete_list_heap;
        break;
    default:
        ShowMessage("heap:new_heap : Unknown heap type", 1);
        return NULL;
    }
    return H;
}

void* get_heap(const struct heap_t* H)
{
    assert(H);
    return H->heap;
}

struct dyn_table_t* get_heap_dictionary(const struct heap_t* H)
{
    assert(H);
    return H->dict;
}



/**********************************************************************************
 * ORDERED LIST HEAP
 **********************************************************************************/

// N'oubliez pas à mettre à jour le dictionnaire, si besoin !

unsigned int list_heap_insert(struct heap_t * H, unsigned long key, void * data)
{
    assert(H);
    struct list_t * heapList = get_heap(H);
    struct heap_node_t * newHeapNode = new_heap_node(key,data);
    struct list_node_t * listNode = new_list_node(newHeapNode);
    if (list_is_empty(heapList) || key < get_heap_node_key(get_list_node_data(get_list_head(heapList))))
    {
        list_insert_first(heapList,newHeapNode);
    }
    else if (key >= get_heap_node_key(get_list_node_data(get_list_tail(heapList))))
    {
        list_insert_last(heapList,newHeapNode);
    }
    else
    {
        struct list_node_t * it = get_list_head(heapList);
        while (it != NULL && key > get_heap_node_key(get_list_node_data(it)) )
        {
            it = get_successor(it);

        }
        list_insert_after(heapList,newHeapNode,get_predecessor(it));
    }
}

void view_list_heap(const struct heap_t * H, void (*viewHeapNode)(const void *))
{
    assert(H);
    struct list_t * heapList = get_heap(H);
    printf("Nombre de noeud dans la heap list %u\n",get_list_size(heapList));
    for (const struct list_node_t * it = get_list_head(heapList);it != NULL; it = get_successor(it))
    {
        const struct heap_node_t * node = get_list_node_data(it);
        printf("********************************* == HEAP NODE == ***********************************\n");
        printf("Data : ");
        viewHeapNode(get_heap_node_data(node));

        printf("\n");
        printf("Dict Pos = %d\nKey = %d\n",get_heap_node_dict_position(node),get_heap_node_key(node));
        printf("********************************** == == ************************************************\n");
    }
    printf("\n");
}