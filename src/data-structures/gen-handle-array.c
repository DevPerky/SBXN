#include "gen-handle-array.h"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

DataStructureStatus ds_gh_array_allocate(GhArray *ghArray, GenHandle *handle) {
    if(ghArray->freeList == NULL) {
        assert(ds_vec_push(&ghArray->dataVec, NULL) == DS_OK);
        GenHandle newHandle = { .index = ghArray->dataVec.size - 1 };
        assert(ds_vec_push(&ghArray->handleVec, &newHandle) == DS_OK);

        *handle = newHandle;
        return DS_OK;
    }
    else {
        GenHandle newHandle = *ghArray->freeList->handle;
        GenHandleFreeList *nextFree = ghArray->freeList->next;
        free(ghArray->freeList);
        ghArray->freeList = nextFree;

        ds_vec_memset(&ghArray->dataVec, newHandle.index, 0);
        *handle = newHandle;
        return DS_OK;
    }
}

DataStructureStatus ds_gh_array_free(GhArray *ghArray, GenHandle handle) {
    if(handle.index > ghArray->dataVec.size - 1
        || handle.index > ghArray->handleVec.size - 1) {
        return DS_OUT_OF_BOUNDS;
    }

    if(DS_VEC_AT(ghArray->handleVec, GenHandle, handle.index)
        .generation != handle.generation) {
        return DS_INVALID;
    }

    GenHandleFreeList freeList = { 
        .handle = &DS_VEC_AT(ghArray->handleVec, GenHandle, handle.index), 
        .next = ghArray->freeList
    };

    freeList.handle->generation++;

    ghArray->freeList = (GenHandleFreeList*)malloc(sizeof(freeList));
    *ghArray->freeList = freeList;

    return DS_OK;
}

void *ds_gh_array_dereference(GhArray *ghArray, GenHandle handle) {
    if(handle.index >= ghArray->dataVec.size) {
        return NULL;
    }

    if(handle.generation != DS_VEC_AT(ghArray->handleVec, GenHandle, handle.index).generation) {
        return NULL;
    }

    return (char*)ghArray->dataVec.data + handle.index * ghArray->dataVec.elementSize;
}

DataStructureStatus ds_gh_array_write(GhArray *ghArray, GenHandle handle, void *data) {
    void *dest = ds_gh_array_dereference(ghArray, handle);
    if(dest == NULL) {
        return DS_NULL_REFERENCE;
    }

    memcpy(dest, data, ghArray->dataVec.elementSize);
    return DS_OK;
}



