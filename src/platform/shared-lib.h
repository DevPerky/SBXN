#ifndef SHARED_LIB_H
#define SHARED_LIB_H
#include "sbxn/sbxn.h"

#ifdef _WIN32
#include <Windows.h>
typedef HMODULE LibHandle;
typedef FILETIME FileTime;
#endif

const char *tempLibFileName = "lib_temp.dll";

typedef enum {
    SHARED_LIB_NOT_FOUND,
    SHARED_LIB_NEW,
    SHARED_LIB_SAME,
    SHARED_LIB_FAIL_COPY,
    SHARED_LIB_FAIL_LOAD,
    SHARED_LIB_FAIL_FREE,
    SHARED_LIB_INIT_NOT_FOUND,
    SHARED_LIB_UPDATE_NOT_FOUND
}SharedLibLoadStatus;

typedef struct {
    LibHandle   handle;
    FileTime    loadTime;

    SbxInit     *initFunc;
    SbxUpdate   *updateFunc;
}ClientLibrary;


LibHandle shared_lib_load(const char *fileName) {
#ifdef _WIN32
    return LoadLibraryA(fileName);
#endif
}

SharedLibLoadStatus shared_lib_load_or_reload(ClientLibrary *library, const char *fileName) {
#ifdef _WIN32

    FILETIME touchTime = { 0 };
    WIN32_FIND_DATA findData;

    if(FindFirstFileA(fileName, &findData) == INVALID_HANDLE_VALUE) {
        return SHARED_LIB_NOT_FOUND;
    }

    touchTime = findData.ftLastAccessTime;

    if(CompareFileTime(&(library->loadTime), &touchTime) < 0) {
        Sleep(1);
        if(library->handle) {
            if(!FreeLibrary(library->handle)) {
                return SHARED_LIB_FAIL_FREE;
            }
        }

        if(!CopyFileA(fileName, tempLibFileName, 0)) {
            return SHARED_LIB_FAIL_COPY;
        }

        Sleep(100);

        library->handle = shared_lib_load(tempLibFileName);
        if(library->handle == NULL) {
            return SHARED_LIB_FAIL_LOAD;
        }

        library->initFunc = (SbxInit*)GetProcAddress(library->handle, XSTR(SBX_INIT_NAME));
        if(library->initFunc == NULL) {
            return SHARED_LIB_INIT_NOT_FOUND;
        }
        
        library->updateFunc = (SbxUpdate*)GetProcAddress(library->handle, XSTR(SBX_UPDATE_NAME));
        if(library->updateFunc == NULL) {
            return SHARED_LIB_UPDATE_NOT_FOUND;
        }
        
        library->loadTime = touchTime;
        return SHARED_LIB_NEW;
    }
    
    return SHARED_LIB_SAME;
#endif
}




#endif