#include "sbx-args.h"
#include <assert.h>
#include <string.h>

SbxArgsStatus sbx_args_parse(int argc, const char **argv, SbxArgs *args) {
    if(argc < 2) {
        return SBX_ARGS_TOO_FEW;
    }

    args->libFileName = argv[1];
}
