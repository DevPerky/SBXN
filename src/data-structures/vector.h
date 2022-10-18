#ifndef VECTOR_H
#define VECTOR_H
#include <stdint.h>
#include "data-structures.h"

#define DS_ELEMENT_SIZE_NAME elementSize

typedef struct {
    const size_t    DS_ELEMENT_SIZE_NAME;
    void            *data;

    size_t          size;
    size_t          capacity;
}Vector;

#define DS_VEC_INIT(type) { .DS_ELEMENT_SIZE_NAME = sizeof(type) }
#define DS_VEC_FRONT(dsVec, type) ( ((type*)dsVec.data)[dsVec.size-1] )

DataStructureStatus ds_vec_push(Vector *vector, void *data);
DataStructureStatus ds_vec_pop(Vector *vector);
DataStructureStatus ds_vec_resize(Vector *vector, size_t newSize);
DataStructureStatus ds_vec_set(Vector *vector, size_t index, void *data);
DataStructureStatus ds_vec_memset(Vector *vector, size_t index, int value);



#endif