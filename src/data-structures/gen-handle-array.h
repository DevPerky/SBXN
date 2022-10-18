#ifndef GEN_HANDLE_ARRAY_H
#define GEN_HANDLE_ARRAY_H
#include <stdint.h>
#include "vector.h"

#define DS_GH_INDEX_WIDTH 56

#define DS_GH_ARRAY_INIT(type) { .dataVec = DS_VEC_INIT(type), .handleVec = DS_VEC_INIT(size_t) }

typedef struct {
    uint64_t index : DS_GH_INDEX_WIDTH;
    uint64_t generation : 64 - DS_GH_INDEX_WIDTH; 
}GenHandle;

typedef struct {
    Vector dataVec;
    Vector handleVec;
}GhArray;

DataStructureStatus ds_gh_array_allocate(GhArray *ghArray, GenHandle *handle);


#endif