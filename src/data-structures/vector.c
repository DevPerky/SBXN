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

    if(data != NULL) {
        memcpy(((char*)vector->data) + vector->size * vector->elementSize, data, vector->elementSize);
    }
    else {
        ds_vec_memset(vector, vector->size, 0);
    }
    
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
        vector->data = malloc(newSize * vector->elementSize);
        if(vector->data == NULL) {
            return DS_FAIL_ALLOC;
        }
    }
    else {
        vector->data = realloc(vector->data, newSize * vector->elementSize);
        if(vector->data == NULL) {
            return DS_FAIL_ALLOC;
        }
    }

    vector->capacity = newSize;
    return DS_OK;
}

DataStructureStatus ds_vec_write(Vector *vector, size_t index, void *data) {
    if(index > vector->size - 1) {
        return DS_OUT_OF_BOUNDS;
    }

    memcpy((char*)vector->data + index * vector->elementSize, data, vector->elementSize);
    return DS_OK;
}

DataStructureStatus ds_vec_memset(Vector *vector, size_t index, int value) {
    if(index > vector->size - 1) {
        return DS_OUT_OF_BOUNDS;
    }

    memset((char*)vector->data + index * vector->elementSize, value, vector->elementSize);
}
