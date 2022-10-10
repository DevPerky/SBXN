#ifndef SHARED_LIB_H
#define SHARED_LIB_H
#include "sbxn/sbxn.h"

#ifdef _WIN32
#include <Windows.h>
typedef HMODULE LibHandle;
typedef FILETIME FileTime;
#endif

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

void *shared_lib_get_proc(LibHandle libHandle, const char *procName) {
#ifdef _WIN32
    return GetProcAddress(libHandle, procName);
#endif
}

int shared_lib_load_or_reload(ClientLibrary *library, const char *fileName) {
#ifdef _WIN32

    const char *tempFileName = "lib_temp.dll";
    FILETIME touchTime = { 0 };
    WIN32_FIND_DATA findData;
    
    FindFirstFileA(fileName, &findData);
    touchTime = findData.ftLastWriteTime;

    if(CompareFileTime(&(library->loadTime), &touchTime) != 0) {
        if(library->handle) {
            FreeLibrary(library->handle);
        }

        CopyFileA(fileName, tempFileName, 0);

        library->handle = shared_lib_load(tempFileName);
        library->loadTime = touchTime;
        library->initFunc = shared_lib_get_proc(library->handle, XSTR(SBX_INIT_NAME));
        library->updateFunc = shared_lib_get_proc(library->handle, XSTR(SBX_UPDATE_NAME));
        
        return 1;
    }
    
    return 0;
#endif
}




#endif