#include "gen-handle-array.h"

DataStructureStatus ds_gh_array_allocate(GhArray *ghArray, GenHandle *handle) {

    while(ghArray->handleVec.size > 0) {
        GenHandle freeHandle;
        freeHandle = DS_VEC_FRONT(ghArray->handleVec, GenHandle);        

        DataStructureStatus popStatus = ds_vec_pop(&ghArray->handleVec);
        if(popStatus != DS_OK) {
            return popStatus;
        }

        if(freeHandle.index < ghArray->dataVec.size) {
            DataStructureStatus memsetStatus = ds_vec_memset(
                &ghArray->dataVec, freeHandle.index, 0
            );

            if(memsetStatus != DS_OK) {
                return memsetStatus;
            }

            *handle = freeHandle;
            return DS_OK;
        }
    }

    DataStructureStatus pushStatus = ds_vec_push(&ghArray->dataVec, NULL);
    if(pushStatus != DS_OK) {
        return pushStatus;
    }

    GenHandle freeHandle = { .generation = 0, .index = ghArray->dataVec.size - 1 };
    *handle = freeHandle;
    
    return DS_OK;
}
