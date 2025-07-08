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

void Dijkstra(graph G, const char * source_name, int heap_type)
{
    struct heap_t * heap = new_heap(heap_type);

    for (int i = 0; i < get_dyn_table_used(G);i++)
    {
        if (strcmp(get_vertex_id(get_dyn_table_data(G,i)),source_name) == 0)
        {
            struct vertex_t * depart = get_dyn_table_data(G,i);
            set_vertex_total_distance(depart,0);
            unsigned int dictPos = heap->heap_insert(heap,get_vertex_total_distance(depart),depart);
            set_vertex_dict_position(depart,dictPos);
        }
    }

    while (!heap->heap_is_empty(heap))
    {

    }

}