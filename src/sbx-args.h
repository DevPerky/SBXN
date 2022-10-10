#ifndef SBX_ARGS_H
#define SBX_ARGS_H

typedef struct {
    const char *libFileName;
}SbxArgs;

typedef enum {
    SBX_ARGS_VALID,
    SBX_ARGS_TOO_FEW
}SbxArgsStatus;

SbxArgsStatus sbx_args_parse(int argc, const char **argv, SbxArgs *args);

#endif