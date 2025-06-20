#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/util.h"

/********************************************************************
 * tree_node_t
 ********************************************************************/


struct tree_node_t *new_tree_node(void *data) {
    struct tree_node_t *node = calloc(1, sizeof(struct tree_node_t));
    assert(node);
    node->data = data;
    return node;
}
void * get_tree_node_data(const struct tree_node_t * node){
    assert(node);
    return node->data;
}