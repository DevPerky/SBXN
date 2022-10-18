#include "vector.h"
#include "stdlib.h"
#include "memory.h"

DataStructureStatus ds_vec_push(Vector *vector, void *data) {
    if(vector->size + 1 > vector->capacity) {
        size_t newCapacity = vector->capacity << 1;
        if(newCapacity == 0) {
            newCapacity = 1;
        }

        DataStructureStatus dss = ds_vec_resize(vector, newCapacity);
        if(dss != DS_OK) {
            return dss;
        }
    }

    memcpy(&(vector->data[vector->size]), data, vector->elementSize);
    
    vector->size++;
    return DS_OK;
}

DataStructureStatus ds_vec_pop(Vector *vector) {
    if(vector->size == 0) {
        return DS_EMPTY;
    }

    if(vector->size - 1 < (vector->capacity >> 1)) {
        ds_vec_resize(vector, vector->capacity >> 1);
    }

    vector->size--;
    return DS_OK;
}

DataStructureStatus ds_vec_resize(Vector *vector, size_t newSize) {
    if(vector->data == NULL) {
        vector->data = (uint8_t*)malloc(newSize * vector->elementSize);
        if(vector->data == NULL) {
            return DS_FAIL_ALLOC;
        }
    }
    else {
        vector->data = (uint8_t*)realloc(vector->data, newSize * vector->elementSize);
        if(vector->data == NULL) {
            return DS_FAIL_ALLOC;
        }
    }

    vector->capacity = newSize;
    return DS_OK;
}
