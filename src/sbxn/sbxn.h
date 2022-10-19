#ifndef SBXN_H
#define SBXN_H

typedef void (*SbxPrint)(const char *message);

typedef struct {
    char placeHolder;
}SbxApi;

#define XSTR(X) STR(X)
#define STR(X) #X

#define SBX_INIT_NAME sbx_init_stub
#define SBX_INIT(name) void name(SbxApi api)
typedef SBX_INIT(SbxInit);

#define SBX_UPDATE_NAME sbx_update_stub
#define SBX_UPDATE(name) void name(float deltaTime)
typedef SBX_UPDATE(SbxUpdate);

#endif