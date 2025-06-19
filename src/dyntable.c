#include "../include/dyntable.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../include/util.h"

struct dyn_table_t *new_dyn_table() {
    struct dyn_table_t *newTable = calloc(1, sizeof(struct dyn_table_t));
    assert(newTable);
    newTable->T = calloc(1, sizeof(void *));
    assert(newTable->T);
    newTable->size = 1;
    return newTable;
}

void * get_dyn_table_data(const struct dyn_table_t * table, unsigned int position){
    assert(table);
    assert(table->T);
    assert(position < table->used);
    return table->T[position];
}