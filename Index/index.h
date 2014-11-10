#ifndef INDEX_H
#define INDEX_H

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>
#include <unistd.h>
#include <ctype.h>
#include "listcoll.h"

void checkContents(LinkedIndexObjListPtr list, char *to_read, char *to_write);
int isDir(char *to_read);
void readDir(LinkedIndexObjListPtr list, char *to_read);
char* toLower(char *str);
void readFile(LinkedIndexObjListPtr list, char *to_read, char *d_name);
void writeFile(LinkedIndexObjListPtr list, char *to_write);
char* apdir(char *base, char* to_append);
void writeList(LinkedIndexObjListPtr list, char *fp);
int rmrf(char *path);
int unc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

#endif
