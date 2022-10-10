#include "platform/platform.h"
#include "sbx-args.h"
#include "sbxn/sbxn.h"
#include <stdio.h>

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
        .print = testPrint
    };

    ClientLibrary clientLib = { 0 };

    while(1) {
        if(shared_lib_load_or_reload(&clientLib, args.libFileName)) {
            if(clientLib.initFunc) {
                clientLib.initFunc(&api);
            }
        }

        if(clientLib.updateFunc) {
            clientLib.updateFunc(100);
        }

        Sleep(100);
    }

}