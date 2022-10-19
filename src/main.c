#include "platform/platform.h"
#include "sbx-args.h"
#include "sbxn/sbxn.h"
#include "data-structures/gen-handle-array.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

GhArray testGhArray = DS_GH_ARRAY_INIT(int);

void testPrint(const char *message) {
    printf("SBX: %s\n", message);
}

int main(int argc, const char **argv) {
    SbxArgs args = { 0 };
    if(sbx_args_parse(argc, argv, &args) != SBX_ARGS_VALID) {
        printf("%s\n", argv[1]);
        return 1;
    }

    SbxApi api = {
        .print = testPrint,
    };

    ClientLibrary clientLib = { 0 };
    GenHandle handle, handle2;
    DataStructureStatus testStatus;
    int testInt = 10;
    int testInt2 = 20;
    testStatus = ds_gh_array_allocate(&testGhArray, &handle);
    testStatus = ds_gh_array_allocate(&testGhArray, &handle2);

    testStatus = ds_gh_array_free(&testGhArray, handle);

    testStatus = ds_gh_array_write(&testGhArray, handle2, &testInt2);
    testStatus = ds_gh_array_write(&testGhArray, handle, &testInt);
    testStatus = ds_gh_array_allocate(&testGhArray, &handle);
    testStatus = ds_gh_array_write(&testGhArray, handle, &testInt);
    testInt = *(int*)ds_gh_array_dereference(&testGhArray, handle);
    testInt2 = *(int*)ds_gh_array_dereference(&testGhArray, handle2);

    while(1) {
        SharedLibLoadStatus status = shared_lib_load_or_reload(&clientLib, args.libFileName);
        switch(status) {
            case SHARED_LIB_NEW:
                printf("Succesfully loaded %s\n", args.libFileName);
                clientLib.initFunc(&api);
            break;
            case SHARED_LIB_FAIL_COPY:
                fprintf(stderr, "Failed copying %s to %s\n", args.libFileName, tempLibFileName);
                break;
            case SHARED_LIB_FAIL_LOAD:
                fprintf(stderr, "Failed loading copy of file %s\n", args.libFileName);
                break;
            case SHARED_LIB_FAIL_FREE:
                fprintf(stderr, "Failed loading %s, couldn't free %s\n", args.libFileName, tempLibFileName);
                break;
            case SHARED_LIB_NOT_FOUND:
                fprintf(stderr, "Couldn't find file %s\n", args.libFileName);
                break;
            case SHARED_LIB_INIT_NOT_FOUND:
                fprintf(stderr, "Failed loading library %s, SBX_INIT function is missing\n", args.libFileName);
                break;
            case SHARED_LIB_UPDATE_NOT_FOUND:
                fprintf(stderr, "Failed loading library %s, SBX_UPDATE function is missing\n", args.libFileName);
                break;
            case SHARED_LIB_SAME: break;
            default:
                fprintf(stderr, "Failed loading library %s because of an undetermined error\n", args.libFileName);

        }

        if(status == SHARED_LIB_NEW || status == SHARED_LIB_SAME) {
            clientLib.updateFunc(10);
        }
        
        Sleep(1);
    }

}