#include "../include/heap.h"


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "../include/dyntable.h"

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
    case 0:
        H->heap = new_dyn_table();
        H->heap_insert = dyn_table_heap_insert;
        H->heap_extract_min = dyn_table_heap_extract_min;
        H->heap_increase_priority = dyn_table_heap_increase_priority;
        H->heap_is_empty = dyn_table_heap_is_empty;
        H->view_heap = view_dyn_table_heap;
        H->delete_heap = delete_dyn_table_heap;
        break;
    case 1:
        H->heap = new_tree();
        H->heap_insert = tree_heap_insert;
        H->heap_extract_min = tree_heap_extract_min;
        H->heap_increase_priority = tree_heap_increase_priority;
        H->heap_is_empty = tree_heap_is_empty;
        H->view_heap = view_tree_heap;
        H->delete_heap = delete_tree_heap;
        break;
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


void dyn_table_heap_update_upwards(struct heap_t* H, unsigned int position)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));

    if (position != 0)
    {
        struct dyn_table_t* dynTableHeap = get_heap(H);
        struct dyn_table_t* dict = get_heap_dictionary(H);
        unsigned int posPere = (position - 1) / 2;
        unsigned long keyFils = get_heap_node_key(get_dyn_table_data(dynTableHeap, position));
        unsigned long keyPere = get_heap_node_key(get_dyn_table_data(dynTableHeap, posPere));


        if (keyFils < keyPere)
        {
            unsigned int posFilsDict = get_heap_node_dict_position(get_dyn_table_data(dynTableHeap, position));
            unsigned int posPereDict = get_heap_node_dict_position(get_dyn_table_data(dynTableHeap, posPere));
            dyn_table_swap_nodes_data(dynTableHeap, position, posPere);
            dyn_table_swap_nodes_data(dict, posFilsDict, posPereDict);

            dyn_table_heap_update_upwards(H, posPere);
        }
    }
}

unsigned int dyn_table_heap_insert(struct heap_t* H, unsigned long key, void* data)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct heap_node_t* newHeapNode = new_heap_node(key, data);
    struct dyn_table_t* dynTableHeap = get_heap(H);
    struct dyn_table_t* dict = get_heap_dictionary(H);

    unsigned int position = get_dyn_table_used(dynTableHeap);
    int* posDict = malloc(sizeof(int));
    *posDict = (int)get_dyn_table_used(dynTableHeap);

    set_heap_node_dict_position(newHeapNode, get_dyn_table_used(dict));
    dyn_table_insert(dynTableHeap, newHeapNode);
    dyn_table_insert(dict, posDict);
    dyn_table_heap_update_upwards(H, position);

    return position;
}

void dyn_table_heap_update_downwards(struct heap_t* H, unsigned int position)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    unsigned int posFilsGauche = 2 * position + 1;

    // Si position fg est plus grande, alors le tas n'a pas de fils et c'est ciao
    if (posFilsGauche < get_dyn_table_used(get_heap(H)))
    {
        struct dyn_table_t* dyntableHeap = get_heap(H);
        struct dyn_table_t* dict = get_heap_dictionary(H);
        unsigned int keyPere = get_heap_node_key(get_dyn_table_data(dyntableHeap, position));
        unsigned int posMin = position;
        unsigned int keyMin = keyPere;
        unsigned int posFilsDroit = 2 * position + 2;

        // Si vrai, il y a aussi un fils droit à comparer
        if (posFilsDroit < get_dyn_table_used(dyntableHeap))
        {
            unsigned int keyFD = get_heap_node_key(get_dyn_table_data(dyntableHeap, posFilsDroit));
            if (keyFD < keyPere)
            {
                posMin = posFilsDroit;
                keyMin = keyFD;
            }
        }

        unsigned int keyFG = get_heap_node_key(get_dyn_table_data(dyntableHeap, posFilsGauche));
        if (keyFG < keyMin)
        {
            posMin = posFilsGauche;
        }
        if (posMin != position)
        {
            printf("pos min %d\n",posMin);
            unsigned int posDicoFils = get_heap_node_dict_position(get_dyn_table_data(dyntableHeap,posMin));
            unsigned int posDicoPere = get_heap_node_dict_position(get_dyn_table_data(dyntableHeap,position));
            dyn_table_swap_nodes_data(dict,posDicoFils,posDicoPere);
            dyn_table_swap_nodes_data(dyntableHeap, position, posMin);
            // unsigned int posFilsMinDict = *(int*)get_dyn_table_data(dict, posMin);
            // unsigned int posPereDict = *(int*)get_dyn_table_data(dict, position);
            // dyn_table_swap_nodes_data(dict, posFilsMinDict, posPereDict);
            dyn_table_heap_update_downwards(H, posMin);
        }
    }
}

struct heap_node_t* dyn_table_heap_extract_min(struct heap_t* H)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct dyn_table_t* dynTableHeap = get_heap(H);
    struct dyn_table_t* dict = get_heap_dictionary(H);

    dyn_table_swap_nodes_data(dynTableHeap, 0, get_dyn_table_used(dynTableHeap) - 1);
    struct heap_node_t* heapNodeMin = dyn_table_remove(dynTableHeap);
    unsigned int posDicoMin = get_heap_node_dict_position(heapNodeMin);

    if (!dyn_table_is_empty(dynTableHeap))
    {
        struct heap_node_t* lastNode = get_dyn_table_data(dynTableHeap, 0);
        unsigned int posDicoLast = get_heap_node_dict_position(lastNode);
        dyn_table_swap_nodes_data(dict, posDicoLast, posDicoMin);
    }

    set_dyn_table_data(dict, posDicoMin,NULL);
    dyn_table_heap_update_downwards(H, 0);

    return heapNodeMin;
}

void dyn_table_heap_increase_priority(struct heap_t* H, unsigned int dict_position, unsigned long newKey)
{
    assert(H);
    assert(get_heap_dictionary(H));
    assert(get_heap(H));
    struct dyn_table_t* dict = get_heap_dictionary(H);
    struct dyn_table_t* dyntableHeap = get_heap(H);

    unsigned int posDansTas = *(int*)get_dyn_table_data(dict, dict_position);
    struct heap_node_t* updatedNode = get_dyn_table_data(dyntableHeap, posDansTas);

    set_heap_node_key(updatedNode, newKey);
    dyn_table_heap_update_upwards(H, posDansTas);
}

int dyn_table_heap_is_empty(const void* H)
{
    assert(H);
    assert(get_heap(H));
    return dyn_table_is_empty(get_heap(H));
}

void view_dyn_table_heap(const struct heap_t* H, void (*viewHeapNode)(const void*))
{
    assert(H);
    assert(get_heap(H));

    view_dyn_table(get_heap(H), viewHeapNode);
}

void delete_dyn_table_heap(struct heap_t* H, void (*freeHeapNode)(void*))
{
    assert(H);
    assert(get_heap(H));
    delete_dyn_table(get_heap(H), freeHeapNode);
    delete_dyn_table(get_heap_dictionary(H), freeInt);
    free(H);
}


/**********************************************************************************
 * COMPLETE BINARY TREE HEAP
 **********************************************************************************/


void tree_heap_update_upwards(struct heap_t* H, unsigned int position, struct tree_node_t* node)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));

    if (position != 0)
    {
        struct tree_t* t = get_heap(H);
        unsigned long keyFils = get_heap_node_key(get_tree_node_data(node));
        struct tree_node_t* nodePere = tree_find_node(t, (position - 1) / 2);
        unsigned long keyPere = get_heap_node_key(get_tree_node_data(nodePere));

        if (keyFils < keyPere)
        {
            struct dyn_table_t* dict = get_heap_dictionary(H);
            dyn_table_swap_nodes_data(dict, get_heap_node_dict_position(get_tree_node_data(node)),
                                      get_heap_node_dict_position(get_tree_node_data(nodePere)));
            tree_swap_nodes_data(node, nodePere);

            tree_heap_update_upwards(H, (position - 1) / 2, nodePere);
        }
    }
}



unsigned int tree_heap_insert(struct heap_t* H, unsigned long key, void* data)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct heap_node_t* newHeapNode = new_heap_node(key, data);
    struct tree_t* treeHeap = get_heap(H);
    struct dyn_table_t* dict = get_heap_dictionary(H);
    unsigned int* position = malloc(sizeof(unsigned int));
    *position = get_dyn_table_used(dict);
    set_heap_node_dict_position(newHeapNode, get_dyn_table_used(dict));

    dyn_table_insert(dict, position);
    tree_insert(treeHeap, newHeapNode);
    struct tree_node_t* treeNode = tree_find_node(treeHeap, get_tree_size(treeHeap) - 1);
    tree_heap_update_upwards(H, get_tree_size(treeHeap) - 1, treeNode);
    return get_heap_node_dict_position(newHeapNode);
}

void tree_heap_increase_priority(struct heap_t* H, unsigned int dict_position, unsigned long newKey)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct tree_t* treeHeap = get_heap(H);
    struct dyn_table_t* dict = get_heap_dictionary(H);

    unsigned int positionDansLarbre = *(unsigned int*)get_dyn_table_data(dict, dict_position);
    struct tree_node_t* treeNode = tree_find_node(treeHeap, positionDansLarbre);
    struct heap_node_t* heapNode = get_tree_node_data(treeNode);

    set_heap_node_key(heapNode, newKey);
    tree_heap_update_upwards(H, positionDansLarbre, treeNode);
}

void tree_heap_update_downwards(struct heap_t* H, struct tree_node_t* node)
{
    assert(H);
    assert(node);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));

    if (get_left(node) || get_right(node))
    {
        struct dyn_table_t* dict = get_heap_dictionary(H);
        struct heap_node_t* heapNodePere = get_tree_node_data(node);
        unsigned int keyPere = get_heap_node_key(heapNodePere);
        unsigned int posDictPere = get_heap_node_dict_position(heapNodePere);
        unsigned int keyMin = keyPere;
        unsigned int posMin = posDictPere;
        struct tree_node_t* nodeTreeMin = node;

        if (get_right(node))
        {
            struct heap_node_t* heapNodeFd = get_tree_node_data(get_right(node));
            unsigned int keyFd = get_heap_node_key(heapNodeFd);
            if (keyFd < keyPere)
            {
                keyMin = keyFd;
                posMin = get_heap_node_dict_position(heapNodeFd);
                nodeTreeMin = get_right(node);
            }
        }

        struct heap_node_t* heapNodeFg = get_tree_node_data(get_left(node));
        unsigned int keyFg = get_heap_node_key(heapNodeFg);

        if (keyFg < keyMin)
        {
            posMin = get_heap_node_dict_position(heapNodeFg);
            nodeTreeMin = get_left(node);
        }
        if (node != nodeTreeMin)
        {
            dyn_table_swap_nodes_data(dict, posDictPere, posMin);
            tree_swap_nodes_data(node, nodeTreeMin);
            tree_heap_update_downwards(H, nodeTreeMin);
        }
    }
}

struct heap_node_t * tree_heap_extract_min(struct heap_t * H)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct tree_t * treeHeap = get_heap(H);
    struct dyn_table_t * dict = get_heap_dictionary(H);

    struct tree_node_t * minNode = get_tree_root(treeHeap);
    unsigned int dictPosMin = get_heap_node_dict_position(get_tree_node_data(minNode));

    struct tree_node_t * lastNode = tree_find_node(treeHeap,get_tree_size(treeHeap)-1);
    unsigned int dictPosLast = get_heap_node_dict_position(get_tree_node_data(lastNode));


    dyn_table_swap_nodes_data(dict,dictPosMin,dictPosLast);
    set_dyn_table_data(dict,dictPosMin,NULL);
    tree_swap_nodes_data(minNode,lastNode);

    struct tree_node_t* noeudRacine = get_tree_root(treeHeap);
    struct heap_node_t* minHeapNode = tree_remove(treeHeap);
    tree_heap_update_downwards(H,noeudRacine);
    return minHeapNode;
}



int tree_heap_is_empty(const void* H)
{
    assert(H);
    assert(get_heap(H));
    return tree_is_empty(get_heap(H));
}

void delete_tree_heap(struct heap_t* H, void (*freeHeapNode)(void*))
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    delete_tree(get_heap(H), freeHeapNode);
    free(H);
}

void view_tree_heap(const struct heap_t* H, void (*viewHeapNode)(const void*))
{
    assert(H);
    assert(get_heap(H));
    struct tree_t* heapTree = get_heap(H);
    view_tree(heapTree, viewHeapNode, 0);
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

void list_heap_increase_priority(struct heap_t* H, unsigned int dict_position, unsigned long newKey)
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    struct dyn_table_t* dict = get_heap_dictionary(H);
    struct list_node_t* listNode = get_dyn_table_data(dict, dict_position);
    struct heap_node_t* heapNode = get_list_node_data(listNode);
    set_heap_node_key(heapNode, newKey);

    while (get_predecessor(listNode) != NULL && newKey < get_heap_node_key(
        get_list_node_data(get_predecessor(listNode))))
    {
        unsigned int precDicPos = get_heap_node_dict_position(get_list_node_data(get_predecessor(listNode)));
        dyn_table_swap_nodes_data(dict, precDicPos, dict_position);
        list_swap_nodes_data(listNode, get_predecessor(listNode));
        listNode = get_predecessor(listNode);
    }
}

int list_heap_is_empty(const void* H)
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

void delete_list_heap(struct heap_t* H, void (*freeHeapNode)(void*))
{
    assert(H);
    assert(get_heap(H));
    assert(get_heap_dictionary(H));
    delete_list(get_heap(H), freeHeapNode);
    delete_dyn_table(get_heap_dictionary(H),NULL);
    free(H);
}
