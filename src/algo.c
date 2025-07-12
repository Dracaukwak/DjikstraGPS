#include "../include/algo.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#include "../include/util.h"
#include "../include/dyntable.h"
#include "../include/list.h"
#include "../include/heap.h"
#include "../include/graph.h"

#define INFINITY ULONG_MAX

void Dijkstra(graph G, const char* source_name, int heap_type)
{
    // switch (heap_type)
    // {
    // case 0:
    //     printf("DIJKSTRA TAS TABLEAU\n");
    //     break;
    // case 1:
    //     printf("DIJKSTRA TAS ARBRE\n");
    //     break;
    // case 2:
    //     printf("DIJKSTRA TAS LISTE\n");
    //     break;
    // }
    struct heap_t* heap = new_heap(heap_type);

    for (int i = 0; i < get_dyn_table_used(G); i++)
    {
        struct vertex_t* v = get_dyn_table_data(G, i);
        if (strcmp(get_vertex_id(v), source_name) == 0)
        {
            set_vertex_total_distance(v, 0);
        }
        unsigned int dictPos = heap->heap_insert(heap, get_vertex_total_distance(v), v);
        set_vertex_dict_position(v, dictPos);
    }

    while (!heap->heap_is_empty(heap))
    {
        struct heap_node_t* temp = heap->heap_extract_min(heap);
        struct vertex_t* U = get_heap_node_data(temp);
        struct list_t* adjacents = get_vertex_incidence_list(U);

        for (struct list_node_t* it = get_list_head(adjacents); it != NULL; it = get_successor(it))
        {
            struct edge_t* E = get_list_node_data(it);
            struct vertex_t* V;
            if (get_edge_endpoint_U(E) == U)
            {
                V = get_edge_endpoint_V(E);
            }
            else
            {
                V = get_edge_endpoint_U(E);
            }
            unsigned long distanceU = get_vertex_total_distance(U);
            unsigned long distanceV = get_vertex_total_distance(V);
            unsigned long poids = get_edge_distance(E);
            if (distanceU + poids < distanceV)
            {
                set_vertex_total_distance(V, distanceU + poids);
                set_vertex_predecessor(V, U);
                heap->heap_increase_priority(heap, get_vertex_dict_position(V), distanceU + poids);
            }
        }
        free(temp);
    }
    heap->delete_heap(heap,NULL);
}

void view_solution(graph G, const char* source_name)
{
    printf("SOLUTION\n");
    printf("%u\n", get_dyn_table_used(G));
    printf("%s\n", source_name);
    for (unsigned int v = 0; v < get_dyn_table_used(G); v++)
    {
        struct vertex_t* V = get_dyn_table_data(G, v);
        if (strcmp(get_vertex_id(V), source_name) != 0)
        {
            printf("%s %lu %s\n",get_vertex_id(V), get_vertex_total_distance(V),get_vertex_id(get_vertex_predecessor(V)));
        }
    }
}

void save_solution(const char* out_filename, graph G, const char* source_name)
{
    assert(G);
    FILE* fd;
    if ((fd = fopen(out_filename, "w")) == NULL)
    {
        ShowMessage("algo:save_solution : Error while open out file", 1);
    }
    fprintf(fd, "%u\n", get_dyn_table_used(G));
    fprintf(fd, "%s\n", source_name);
    for (unsigned int v = 0; v < get_dyn_table_used(G); v++)
    {
        struct vertex_t* V = get_dyn_table_data(G, v);
        if (strcmp(get_vertex_id(V), source_name) != 0)
        {
            fprintf(fd, "%s %u %s\n", get_vertex_id(V), get_vertex_total_distance(V),
                    get_vertex_id(get_vertex_predecessor(V)));
        }
    }
}
