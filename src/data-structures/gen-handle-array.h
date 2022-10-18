#ifndef GEN_HANDLE_ARRAY_H
#define GEN_HANDLE_ARRAY_H
#include <stdint.h>
#include "vector.h"

#define DS_GH_INDEX_WIDTH 56


typedef struct {
    uint64_t index : DS_GH_INDEX_WIDTH;
    uint64_t generation : 64 - DS_GH_INDEX_WIDTH; 
}GenHandle;

typedef struct GenHandleFreeList {
    struct GenHandleFreeList *next;
    GenHandle *handle;
}GenHandleFreeList;

typedef struct {
    Vector dataVec;
    Vector handleVec;

    GenHandleFreeList *freeList;
}GhArray;

#define DS_GH_ARRAY_INIT(type) {\
    .dataVec = DS_VEC_INIT(type),\
    .handleVec = DS_VEC_INIT(GenHandle)\
}

DataStructureStatus ds_gh_array_allocate(GhArray *ghArray, GenHandle *handle);
DataStructureStatus ds_gh_array_free(GhArray *ghArray, GenHandle handle);


#endif