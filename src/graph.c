#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "../include/util.h"
#include "../include/list.h"
#include "../include/dyntable.h"
#define INFINITY ULONG_MAX
/**********************************************************************************
 * vertex_t
 **********************************************************************************/

struct vertex_t* new_vertex(char* id)
{
    struct vertex_t* newVertex = calloc(1, sizeof(struct vertex_t));
    assert(newVertex);
    newVertex->id = id;
    newVertex->incidence_list = new_list();
    newVertex->total_distance = INFINITY;
    newVertex->predecessor = NULL;
    newVertex->dict_position = UINT_MAX;
    return newVertex;
}

char* get_vertex_id(const struct vertex_t* V)
{
    assert(V);
    return V->id;
}

struct list_t* get_vertex_incidence_list(const struct vertex_t* V)
{
    assert(V);
    return V->incidence_list;
}

unsigned long get_vertex_total_distance(const struct vertex_t* V)
{
    assert(V);
    return V->total_distance;
}

struct vertex_t* get_vertex_predecessor(const struct vertex_t* V)
{
    assert(V);
    return V->predecessor;
}

unsigned int get_vertex_dict_position(const struct vertex_t* V)
{
    assert(V);
    return V->dict_position;
}

void set_vertex_total_distance(struct vertex_t* V, unsigned long newDistance)
{
    assert(V);
    V->total_distance = newDistance;
}

void set_vertex_predecessor(struct vertex_t* V, struct vertex_t* newPredecessor)
{
    assert(V);
    V->predecessor = newPredecessor;
}

void set_vertex_dict_position(struct vertex_t* V, unsigned int newPosition)
{
    assert(V);
    V->dict_position = newPosition;
}

void vertex_add_incident_edge(struct vertex_t* V, struct edge_t* E)
{
    assert(V);
    assert(E);
    list_insert_last(get_vertex_incidence_list(V), E);
}

void delete_vertex(void* V)
{
    assert(V);
    struct vertex_t* vertexed = (struct vertex_t*)V;
    delete_list(get_vertex_incidence_list(vertexed),NULL);
    free(get_vertex_id(vertexed));
    free(vertexed);
}

void view_vertex(const void* vertex)
{
    assert(vertex);
    struct vertex_t* V = (struct vertex_t*)vertex;

    printf("Vertex : %s\n", get_vertex_id(V));
    printf("total_distance = %lu\n", get_vertex_total_distance(V));
    if (get_vertex_predecessor(V) != NULL)
        printf("predecessor = %s\n", get_vertex_id(get_vertex_predecessor(V)));
    else
        printf("predecessor = NULL\n");
    if (get_vertex_dict_position(V) != UINT_MAX)
        printf("dict position = %u\n", get_vertex_dict_position(V));
    else
        printf("dict position = NULL\n");
    view_list(get_vertex_incidence_list(V), view_edge);
}


/**********************************************************************************
 * edge_t
 **********************************************************************************/

struct edge_t* new_edge(struct vertex_t* U, struct vertex_t* V, unsigned int distance)
{
    struct edge_t* newEdge = calloc(1, sizeof(struct edge_t));
    assert(newEdge);
    newEdge->U = U;
    newEdge->V = V;
    newEdge->distance = distance;
    return newEdge;
}

struct vertex_t* get_edge_endpoint_U(const struct edge_t* E)
{
    assert(E);
    return E->U;
}

struct vertex_t* get_edge_endpoint_V(const struct edge_t* E)
{
    assert(E);
    return E->V;
}

unsigned int get_edge_distance(const struct edge_t* E)
{
    assert(E);
    return E->distance;
}

void delete_edge(void* E)
{
    assert(E);
    struct edge_t* edged = (struct edge_t*)E;
    free(E);
}

void view_edge(const void* edge)
{
    struct edge_t* E = (struct edge_t*)edge;
    printf("[(%s,%s),%u]", get_vertex_id(get_edge_endpoint_U(E)), get_vertex_id(get_edge_endpoint_V(E)),
           get_edge_distance(E));
}

/**********************************************************************************
 * graph_t
 **********************************************************************************/


graph read_graph(const char* filename)
{
    FILE* fd;
    if ((fd = fopen(filename, "rt")) == NULL)
    {
        ShowMessage("graph:read_graph : Error while opening graph input file", 1);
    }
    //Construction du tableau des sommets du graphe
    graph G = new_dyn_table();

    //Lecture du nombre de sommets
    int n;
    if (fscanf(fd, "%d", &n) != 1)
    {
        ShowMessage("graph:read_graph : Error while reading vertices number", 1);
    }
    // Lecture des sommets
    for (int i = 0; i < n; i++)
    {
        char buffer[BUFSIZ];
        unsigned long id_length;

        if (fscanf(fd, "%s", buffer) != 1)
        {
            ShowMessage("graph:read_graph : Error while reading vertice id", 1);
        }
        id_length = strlen(buffer) + 1;
        char* id = calloc(id_length, sizeof(char));
        strcpy(id, buffer);
        struct vertex_t* v = new_vertex(id);
        dyn_table_insert(G, v);
    }
    // Lecture du nombre d'arêtes
    int m;
    if (fscanf(fd, "%d", &m) != 1)
    {
        ShowMessage("graph:read_graph : Error while reading edges number", 1);
    }

    // Lecture des arêtes
    for (int j = 0; j < m; j++)
    {
        char U_id[BUFSIZ], V_id[BUFSIZ];
        unsigned int distance;

        if (fscanf(fd, "%s %s %u", U_id, V_id, &distance) != 3)
        {
            ShowMessage("graph:read_graph : Error while reading edge characteristics", 1);
        }

        // Trouver la position de l'extrémité U_id dans le graphe
        int u = 0;
        while (u < n && strcmp(U_id, get_vertex_id(get_dyn_table_data(G, u))) != 0)
        {
            u++;
        }
        if (u == n)
        {
            ShowMessage("graph:read_graph : The vertex U_id does not exist in the graph", 1);
        }
        struct vertex_t* U = get_dyn_table_data(G, u);

        // Trouver la position de l'extrémité V_id dans le graphe
        int v = 0;
        while (v < n && strcmp(V_id, get_vertex_id(get_dyn_table_data(G, v))) != 0)
        {
            v++;
        }
        if (v == n)
        {
            ShowMessage("graph:read_graph : The vertex V_id does not exist in the graph", 1);
        }

        struct vertex_t* V = get_dyn_table_data(G, v);
        struct edge_t* E = new_edge(U, V, distance);
        vertex_add_incident_edge(V, E);
        vertex_add_incident_edge(U, E);
    }
    fclose(fd);
    return G;
}

struct list_t* get_graph_edges(graph G)
{
    assert(G);
    struct list_t* edges = new_list();

    for (unsigned int v = 0; v < get_dyn_table_used(G); v++)
    {
        struct vertex_t* V = get_dyn_table_data(G, v);
        struct list_node_t* curr_node = get_list_head(get_vertex_incidence_list(V));

        while (curr_node)
        {
            struct edge_t* E = get_list_node_data(curr_node);
            if (!list_data_exist(edges, E))
            {
                list_insert_last(edges, E);
            }
            curr_node = get_successor(curr_node);
        }
    }
    return edges;
}

void view_graph(graph G)
{
    assert(G);
    printf("Graph :\n");
    view_dyn_table(G, view_vertex);
}

void delete_graph(graph G)
{
    assert(G);
    delete_list(get_graph_edges(G), delete_edge);
    delete_dyn_table(G, delete_vertex);
}

void reset_graph(graph G)
{
    assert(G);
    for (int v = 0; v < get_dyn_table_used(G); v++)
    {
        struct vertex_t* V = get_dyn_table_data(G, v);

        set_vertex_dict_position(V,UINT_MAX);
        set_vertex_total_distance(V,INFINITY);
        set_vertex_predecessor(V,NULL);
    }
}
