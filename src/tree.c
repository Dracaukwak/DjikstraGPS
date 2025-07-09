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
        if (freeData && get_tree_node_data(node) != NULL)
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
    // printf("Arbre detruit !\n");
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

struct tree_node_t* insert_into_subtree(struct tree_node_t* node, unsigned int position, void* data)
{
    if (position == 0)
    {
        return new_tree_node(data);
    }
    else
    {
        int hauteur = (unsigned int)log2(position + 1);
        int nbNoeudDernierNiveau = (unsigned int)pow(2, hauteur);
        int millieu = nbNoeudDernierNiveau / 2;
        int index = position - (nbNoeudDernierNiveau - 1);


        if (index < millieu)
        {
            set_left(node,
                     insert_into_subtree(get_left(node), (unsigned int)position - pow(2, hauteur - 1), data));
        }
        else
        {
            set_right(node,
                      insert_into_subtree(get_right(node), (unsigned int)position - pow(2, hauteur), data));
        }
        return node;
    }
}

void tree_insert(struct tree_t* T, void* data)
{
    assert(T);
    set_tree_root(T, insert_into_subtree(get_tree_root(T), get_tree_size(T), data));
    increase_tree_size(T);
}

struct tree_node_t* remove_from_subtree(struct tree_node_t* node, unsigned int position, void** data)
{
    if (position == 0)
    {
        *data = get_tree_node_data(node);
        free(node);
        return NULL;
    }
    else
    {
        int hauteur = (int)log2(position + 1);
        int nbNoeudDernierNiveau = (int)pow(2, hauteur);
        int millieu = nbNoeudDernierNiveau / 2;
        int index = position - (nbNoeudDernierNiveau - 1);

        if (index < millieu)
        {
            set_left(node, remove_from_subtree(get_left(node), (unsigned int)position - pow(2, hauteur - 1), data));
        }
        else
        {
            set_right(node, remove_from_subtree(get_right(node), (unsigned int)position - pow(2, hauteur), data));
        }
        return node;
    }
}

void* tree_remove(struct tree_t* T)
{
    assert(T);
    assert(get_tree_root(T));
    void * data = NULL;
    set_tree_root(T,remove_from_subtree(get_tree_root(T),get_tree_size(T)-1,&data));
    decrease_tree_size(T);
    return data;

}

struct tree_node_t *get_tree_node_at_position(struct tree_node_t *node, unsigned int position)
{
    if (position == 0)
    {
        return node;
    }
    else
    {
        int hauteur = (int)log2(position+1);
        int nbNoeudDernierNiveau = (int)pow(2,hauteur);
        int millieu = nbNoeudDernierNiveau/2;
        int index = position - (nbNoeudDernierNiveau -1);

        if (index < millieu)
        {
            return get_tree_node_at_position(get_left(node),position - pow(2,hauteur-1));
        }
        else
        {
            return get_tree_node_at_position(get_right(node),position - pow(2,hauteur));

        }
    }
}

struct tree_node_t* tree_find_node(struct tree_t* T, unsigned int position)
{
    assert(T);
    assert(get_tree_root(T));
    assert(position < get_tree_size(T));
    return get_tree_node_at_position(get_tree_root(T),position);
}

void tree_swap_nodes_data(struct tree_node_t* node1, struct tree_node_t* node2)
{
    assert(node1 && node2);
    void * aux = get_tree_node_data(node1);
    set_tree_node_data(node1,get_tree_node_data(node2));
    set_tree_node_data(node2,aux);
}