#ifndef PLATFORM_H
#define PLATFORM_H
#ifdef _WIN32
#include <Windows.h>
typedef HMODULE LibHandle;
#endif

LibHandle loadDll(const char *fileName) {
#ifdef _WIN32
    return LoadLibraryA(fileName);
#endif


}


#endif