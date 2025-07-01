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
        H->heap_extract_min = list_heap_extract_min;
        H->heap_increase_priority = list_heap_increase_priority;
        H->heap_is_empty = list_heap_is_empty;
        H->view_heap = view_list_heap;
        H->delete_heap = delete_list_heap;
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
 * DYNAMIC TABLE HEAP
 **********************************************************************************/


 void dyn_table_heap_update_upwards(struct heap_t *H, unsigned int position)
{

}



/**********************************************************************************
 * ORDERED LIST HEAP
 **********************************************************************************/

// N'oubliez pas à mettre à jour le dictionnaire, si besoin !

unsigned int list_heap_insert(struct heap_t* H, unsigned long key, void* data)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct list_t* heapList = get_heap(H);
    struct heap_node_t* newHeapNode = new_heap_node(key, data);

    // listNode contiendra l'element de liste à placer dans le dictionnaire !
    struct list_node_t* listNode;

    if (list_is_empty(heapList) || key < get_heap_node_key(get_list_node_data(get_list_head(heapList))))
    {
        list_insert_first(heapList, newHeapNode);
        listNode = get_list_head(heapList);
    }
    else if (key >= get_heap_node_key(get_list_node_data(get_list_tail(heapList))))
    {
        list_insert_last(heapList, newHeapNode);
        listNode = get_list_tail(heapList);
    }
    else
    {
        struct list_node_t* it = get_list_head(heapList);
        while (it != NULL && key > get_heap_node_key(get_list_node_data(it)))
        {
            it = get_successor(it);
        }
        list_insert_after(heapList, newHeapNode, get_predecessor(it));
        listNode = get_predecessor(it);
    }
    unsigned int dictPos = get_dyn_table_used(get_heap_dictionary(H));
    set_heap_node_dict_position(newHeapNode, dictPos);
    dyn_table_insert(get_heap_dictionary(H), listNode);
    // On met l'élément qui contient le heap node dans le dictionnaire
    return dictPos;
}

struct heap_node_t* list_heap_extract_min(struct heap_t* H)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    assert(!list_is_empty(get_heap(H)));

    struct list_t* heapList = get_heap(H);
    struct dyn_table_t* dict = get_heap_dictionary(H);
    struct heap_node_t* heapNode = list_remove_first(heapList);
    set_dyn_table_data(dict, get_heap_node_dict_position(heapNode),NULL);

    return heapNode;
}

void list_heap_increase_priority(struct heap_t * H, unsigned int dict_position, unsigned long newKey)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct dyn_table_t * dict = get_heap_dictionary(H);
    struct list_node_t * listNode = get_dyn_table_data(dict,dict_position);
    struct heap_node_t * heapNode = get_list_node_data(listNode);
    set_heap_node_key(heapNode,newKey);

    while (get_predecessor(listNode) != NULL && newKey < get_heap_node_key(get_list_node_data(get_predecessor(listNode))))
    {
        unsigned int precDicPos = get_heap_node_dict_position(get_list_node_data(get_predecessor(listNode)));
        dyn_table_swap_nodes_data(dict,precDicPos,dict_position);
        list_swap_nodes_data(listNode,get_predecessor(listNode));
        listNode = get_predecessor(listNode);
    }


}

int list_heap_is_empty(const void * H)
{
    assert(H);
    assert(get_heap(H));
    return list_is_empty(get_heap(H));
}

void view_list_heap(const struct heap_t* H, void (*viewHeapNode)(const void*))
{
    assert(H);
    struct list_t* heapList = get_heap(H);
    printf("Nombre de noeud dans la heap list %u\n", get_list_size(heapList));
    for (const struct list_node_t* it = get_list_head(heapList); it != NULL; it = get_successor(it))
    {
        const struct heap_node_t* node = get_list_node_data(it);
        printf("********************************* == HEAP NODE == ***********************************\n");
        printf("Data : ");
        viewHeapNode(get_heap_node_data(node));

        printf("\n");
        printf("Dict Pos = %d\nKey = %d\n", get_heap_node_dict_position(node), get_heap_node_key(node));
        printf("********************************** == == ************************************************\n");
    }
    printf("\n");
}

void delete_list_heap(struct heap_t * H, void (*freeHeapNode)(void *))
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    delete_list(get_heap(H),freeHeapNode);
    delete_dyn_table(get_heap_dictionary(H),NULL);
    free(H);

}
