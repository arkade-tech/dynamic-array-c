#include "dyn_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MIN_CAPACITY 8
#define GROWTH_FACTOR 2
#define SHRINK_THRESHOLD 0.25
#define SHRINK_FACTOR 0.5

struct DynArray {
    void** items;
    size_t size;
    size_t capacity;
};

static da_status da_resize(DynArray* da, size_t new_cap) {
    if (new_cap < MIN_CAPACITY) new_cap = MIN_CAPACITY;
    
    void** new_items = realloc(da->items, new_cap * sizeof(void*));
    if (!new_items) return DA_ERR_ALLOC;

    da->items = new_items;
    da->capacity = new_cap;
    return DA_OK;
}

DynArray* da_create(size_t capacity) {
    if (capacity < MIN_CAPACITY) capacity = MIN_CAPACITY;
    
    DynArray* da = calloc(1, sizeof(DynArray));
    if (!da) return NULL;

    da->items = malloc(capacity * sizeof(void*));
    if (!da->items) {
        free(da);
        return NULL;
    }

    da->size = 0;
    da->capacity = capacity;
    return da;
}

da_status da_push(DynArray* da, void* item) {
    if (!da) return DA_ERR_INVALID;

    if (da->size >= da->capacity) {
        if (da_resize(da, da->capacity * GROWTH_FACTOR) != DA_OK) {
            return DA_ERR_ALLOC;
        }
    }
    da->items[da->size++] = item;
    return DA_OK;
}

void* da_get(const DynArray* da, size_t index) {
    if (!da || index >= da->size) return NULL;
    return da->items[index];
}

da_status da_set(DynArray* da, size_t index, void* item) {
    if (!da || index >= da->size) return DA_ERR_BOUNDS;
    da->items[index] = item;
    return DA_OK;
}

void* da_delete(DynArray* da, size_t index) {
    if (!da || index >= da->size) return NULL;

    void* removed_item = da->items[index];

    // Shift left
    size_t move_count = da->size - index - 1;
    if (move_count > 0) {
        memmove(&da->items[index], &da->items[index + 1], move_count * sizeof(void*));
    }
    da->size--;

    // Hysteresis Shrink
    if (da->size > 0 && da->size <= (da->capacity * SHRINK_THRESHOLD)) {
        da_resize(da, da->capacity * SHRINK_FACTOR);
    }

    return removed_item;
}

size_t da_size(const DynArray* da) { return da ? da->size : 0; }
size_t da_capacity(const DynArray* da) { return da ? da->capacity : 0; }

void da_destroy(DynArray* da) {
    if (da) {
        free(da->items);
        free(da);
    }
}
