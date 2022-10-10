#include "platform/platform.h"
#include "sbx-args.h"
#include "sbxn/sbxn.h"
#include <stdio.h>

void testPrint(const char *message) {
    printf("SBX: %s\n", message);
}

int main(int argc, const char **argv) {
    SbxArgs args = { 0 };
    SbxArgsStatus argsStatus = sbx_args_parse(argc, argv, &args);
    if(argsStatus != SBX_ARGS_VALID) {
        printf("%s\n", argv[1]);
        return argsStatus;
    }

    SbxApi api = {
        .print = testPrint
    };

    ClientLibrary clientLib = { 0 };

    while(1) {
        if(shared_lib_load_or_reload(&clientLib, args.libFileName)) {
            sbx_init *initFunc = shared_lib_get_proc(clientLib.handle, XSTR(SBX_INIT_NAME));
            initFunc(&api);
        }
        Sleep(100);
    }

}