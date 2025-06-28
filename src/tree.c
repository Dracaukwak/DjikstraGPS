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

struct tree_t* new_tree()
{
    struct tree_t* tree = calloc(1, sizeof(struct tree_t));
    assert(tree);
    return tree;
}

int tree_is_empty(const struct tree_t* T)
{
    assert(T);
    return T->size == 0;
}

unsigned int get_tree_size(const struct tree_t* T)
{
    assert(T);
    return T->size;
}


struct tree_node_t* get_tree_root(const struct tree_t* T)
{
    assert(T);
    return T->root;
}

void increase_tree_size(struct tree_t* T)
{
    assert(T);
    T->size++;
}

void decrease_tree_size(struct tree_t* T)
{
    assert(T);
    T->size--;
}

void set_tree_root(struct tree_t* T, struct tree_node_t* newRoot)
{
    assert(T);
    T->root = newRoot;
}

void free_subtree(struct tree_node_t* node, void (*freeData)(void*))
{
    if (node != NULL)
    {
        free_subtree(get_left(node), freeData);
        free_subtree(get_right(node), freeData);
        if (freeData)
        {
            freeData(get_tree_node_data(node));
        }
        free(node);
    }
}

void delete_tree(struct tree_t* T, void (*freeData)(void*))
{
    assert(T);
    free_subtree(get_tree_root(T), freeData);
    free(T);
    printf("Arbre detruit !\n");
}

void view_preorder(const struct tree_node_t* node, void (*viewData)(const void*))
{
    if (node != NULL)
    {
        viewData(get_tree_node_data(node));
        view_preorder(get_left(node), viewData);
        view_preorder(get_right(node), viewData);
    }
}


void view_inorder(const struct tree_node_t* node, void (*viewData)(const void*))
{
    if (node != NULL)
    {
        view_inorder(get_left(node), viewData);
        viewData(get_tree_node_data(node));
        view_inorder(get_right(node), viewData);
    }
}


void view_postorder(const struct tree_node_t* node, void (*viewData)(const void*))
{
    if (node != NULL)
    {
        view_postorder(get_left(node), viewData);
        view_postorder(get_right(node), viewData);
        viewData(get_tree_node_data(node));
    }
}

void view_tree(const struct tree_t* T, void (*viewData)(const void*), int order)
{
    assert(T);
    switch (order)
    {
    case 0:
        printf("Ordre Prefixe\n");
        view_preorder(get_tree_root(T), viewData);
        printf("\n");
        break;
    case 1:
        printf("Ordre Postfixe\n");
        view_postorder(get_tree_root(T), viewData);
        printf("\n");
        break;
    case 2:
        printf("Ordre Infixe\n");
        view_inorder(get_tree_root(T), viewData);
        printf("\n");
        break;
    default:
        printf("Ordre inconnu\n");
    }
}
