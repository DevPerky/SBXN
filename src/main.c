#include "platform/platform.h"
#include "sbx-args.h"
#include "sbxn/sbxn.h"
#define STR(X) #X

int main(int argc, const char **argv) {
    SbxArgs args = { 0 };
    SbxArgsStatus argsStatus = sbx_args_parse(argc, argv, &args);
    if(argsStatus != SBX_ARGS_VALID) {
        return argsStatus;
    }

    LibHandle lib = shared_lib_load(args.libFileName);
    sbx_init *initFunc = shared_lib_get_proc(lib, STR(SBX_INIT_NAME));
    initFunc();
}