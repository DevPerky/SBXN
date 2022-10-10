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


#endif