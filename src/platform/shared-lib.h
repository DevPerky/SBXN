#ifndef SHARED_LIB_H
#define SHARED_LIB_H

#ifdef _WIN32
#include <Windows.h>
typedef HMODULE LibHandle;
#endif

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


#endif