#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/util.h"

/********************************************************************
 * tree_node_t
 ********************************************************************/


struct tree_node_t* new_tree_node(void* data)
{
    struct tree_node_t* node = calloc(1, sizeof(struct tree_node_t));
    assert(node);
    node->data = data;
    return node;
}

void* get_tree_node_data(const struct tree_node_t* node)
{
    assert(node);
    return node->data;
}


struct tree_node_t* get_right(const struct tree_node_t* node)
{
    assert(node);
    return node->right;
}

struct tree_node_t* get_left(const struct tree_node_t* node)
{
    assert(node);
    return node->left;
}

void set_left(struct tree_node_t* node, struct tree_node_t* newLeft)
{
    assert(node);
    node->left = newLeft;
}

void set_right(struct tree_node_t* node, struct tree_node_t* newRight)
{
    assert(node);
    node->right = newRight;
}

void set_tree_node_data(struct tree_node_t* node, void* newData)
{
    assert(node);
    node->data = newData;
}
