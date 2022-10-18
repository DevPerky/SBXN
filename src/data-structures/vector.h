#ifndef VECTOR_H
#define VECTOR_H
#include <stdint.h>
#include "data-structures.h"

#define DS_ELEMENT_SIZE_NAME elementSize

typedef struct {
    const size_t    DS_ELEMENT_SIZE_NAME;
    uint8_t         *data;

    size_t          size;
    size_t          capacity;
}Vector;

#define DS_VEC_INIT(type) { .DS_ELEMENT_SIZE_NAME = sizeof(type) }

DataStructureStatus ds_vec_push(Vector *vector, void *data);
DataStructureStatus ds_vec_pop(Vector *vector);
DataStructureStatus ds_vec_resize(Vector *vector, size_t newSize);



#endif