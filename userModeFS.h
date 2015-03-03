#ifndef USERMODEFS_H
#define USERMODEFS_H


#define PATHLEN_MAX 1024
#define MAX_ROOTS 256

char *root[MAX_ROOTS];
int nroots;
int monitorInit(const char *file);
int userFSMain(struct fuse_args *args,int use_readir_method2);
extern int symlink_mode;
#endif
