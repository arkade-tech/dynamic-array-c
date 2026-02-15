#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Return codes for API operations.
 */
typedef enum {
    DA_OK = 0,
    DA_ERR_ALLOC = -1,
    DA_ERR_BOUNDS = -2,
    DA_ERR_INVALID = -3
} da_status;

typedef struct DynArray DynArray;

/**
 * @brief Creates a new Generic Dynamic Array.
 * @param capacity Initial reserve capacity (e.g., 16).
 * @return Opaque handle or NULL on failure.
 */
DynArray* da_create(size_t capacity);

/**
 * @brief Appends a generic item (pointer) to the array.
 * @param da Array handle.
 * @param item Pointer to the data (user owns the memory).
 */
da_status da_push(DynArray* da, void* item);

/**
 * @brief Retrieves item at index.
 * @return Pointer to item, or NULL if out of bounds.
 */
void* da_get(const DynArray* da, size_t index);

/**
 * @brief Removes item at index, shifting others left.
 * @return The pointer that was removed (so user can free it).
 */
void* da_delete(DynArray* da, size_t index);

/**
 * @brief Replaces item at index.
 */
da_status da_set(DynArray* da, size_t index, void* item);

/**
 * @brief Utility: Returns size.
 */
size_t da_size(const DynArray* da);

/**
 * @brief Utility: Returns capacity.
 */
size_t da_capacity(const DynArray* da);

/**
 * @brief Destroys the container.
 * @note Does NOT free the items (user must free them first).
 */
void da_destroy(DynArray* da);

/**
 * @brief Iteration Macro
 * Usage: da_foreach(list, MyType*, item) { printf("%d", item->id); }
 */
#define da_foreach(array, type, iter) \
    for (size_t _i = 0; _i < da_size(array) && ((iter = (type)da_get(array, _i))); ++_i)

#endif // DYN_ARRAY_H
