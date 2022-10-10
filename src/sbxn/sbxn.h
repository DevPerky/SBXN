#ifndef SBXN_H
#define SBXN_H

typedef void (*SbxPrint)(const char *message);

typedef struct {
    SbxPrint print;
}SbxApi;

#define XSTR(X) STR(X)
#define STR(X) #X

#define SBX_INIT_NAME sbx_init_stub
#define SBX_INIT_NAME_STR = #SBX_INIT_NAME
#define SBX_INIT(name) void name(SbxApi *api)
typedef SBX_INIT(sbx_init);

#endif