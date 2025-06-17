#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/util.h"


/**
 * Construit et initialise un nouveau nœud d'une liste doublement chaînée.
 * Le paramètre \p data correspond à la donnée à affecter au nouveau nœud.
 *
 * @param[in] data
 * @return le nouveau nœud créé
 */
static struct list_node_t *new_list_node(void *data){
    struct list_node_t * newListNode = calloc(1, sizeof(struct list_node_t));
    assert(newListNode);
    newListNode->data = data;
    return newListNode;
}

void * get_list_node_data(const struct list_node_t * node){
    assert(node);
    return node->data;
}