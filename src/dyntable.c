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

void *get_dyn_table_data(const struct dyn_table_t *table, unsigned int position) {
    assert(table);
    assert(table->T);
    assert(position < table->used);
    return table->T[position];
}

unsigned int get_dyn_table_size(const struct dyn_table_t *table) {
    assert(table);
    return table->size;
}

unsigned int get_dyn_table_used(const struct dyn_table_t *table) {
    assert(table);
    return table->used;
}

int dyn_table_is_full(const struct dyn_table_t *table) {
    assert(table);
    return table->used == table->size;
}

int dyn_table_is_quasi_empty(const struct dyn_table_t *table) {
    assert(table);
    return table->used < (table->size / 4);
}

int dyn_table_is_empty(const struct dyn_table_t *table) {
    assert(table);
    return table->used == 0;
}

void set_dyn_table_data(struct dyn_table_t *table, unsigned int position, void *newData) {
    assert(table && table->T);
    assert(position < table->size);
    table->T[position] = newData;
}

void set_dyn_table_size(struct dyn_table_t *table, unsigned int newSize) {
    assert(table);
    table->size = newSize;
}

void increase_dyn_table_used(struct dyn_table_t *table) {
    assert(table);
    assert(!dyn_table_is_full(table));
    table->used++;
}

void decrease_dyn_table_used(struct dyn_table_t *table) {
    assert(table);
    assert(!dyn_table_is_empty(table));
    table->used--;
}

void delete_dyn_table(struct dyn_table_t *table, void (*freeData)(void *)) {
    assert(table);
    if (freeData) {
        for (int i = 0; i < get_dyn_table_used(table); i++) {
            freeData(get_dyn_table_data(table, i));
        }

    }
    free(table->T);
    free(table);
}

void view_dyn_table(const struct dyn_table_t *table, void (*viewData)(const void *)) {
    assert(table);
    printf("Size: %d\nUsed: %d\n", get_dyn_table_size(table), get_dyn_table_used(table));
    printf("[");
    for (int i = 0; i < get_dyn_table_used(table); i++) {
        viewData(get_dyn_table_data(table, i));
        if (i < get_dyn_table_used(table) - 1) {
            printf(", ");
        }

    }
    printf("]\n");
}

/**
 * Dédoubler la taille du tableau dynamique \p table.
 *
 * @param table
 */
static void scale_up(struct dyn_table_t *table) {
    assert(table);
    table->T = realloc(table->T, 2 * table->size * sizeof(void *));
    assert(table->T);
    table->size *= 2;
}

/**
 * Diviser par 2 la taille du tableau dynamique \p table.
 *
 * @param table
 */
static void scale_down(struct dyn_table_t *table) {
    assert(table);
    table->T = realloc(table->T, (table->size / 2) * sizeof(void *));
    assert(table->T);
    table->size /= 2;
}

void dyn_table_insert(struct dyn_table_t *table, void *data) {
    assert(table);
    if (dyn_table_is_full(table)) {
        scale_up(table);
    }
    set_dyn_table_data(table, get_dyn_table_used(table), data);
    increase_dyn_table_used(table);
}

void *dyn_table_remove(struct dyn_table_t *table) {
    assert(table);
    assert(!dyn_table_is_empty(table));
    void *data = get_dyn_table_data(table, get_dyn_table_used(table) - 1);
    set_dyn_table_data(table, get_dyn_table_used(table) - 1, NULL);
    decrease_dyn_table_used(table);
    if (dyn_table_is_quasi_empty(table)) {
        scale_down(table);
    }
    return data;
}

void dyn_table_swap_nodes_data(struct dyn_table_t *table, unsigned int pos1, unsigned int pos2) {
    assert(table);
    assert(pos1 < get_dyn_table_used(table) && pos2 < get_dyn_table_used(table));

    void *aux = get_dyn_table_data(table, pos1);
    set_dyn_table_data(table, pos1, get_dyn_table_data(table, pos2));
    set_dyn_table_data(table, pos2, aux);
}