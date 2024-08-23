#ifndef FS_FILE_H
#define FS_FILE_H

#include <stdio.h>

#include "common/types.h"

typedef struct {
	FILE *data;
	const char *name;
} File;

void fileOpen(File *file, const char *name);
void fileClose(File *file);

i8 fileGetChar(File *file);
u16 fileGetShort(File *file);
u32 fileGetLong(File *file);
void fileSeek(File *file, long offset);

void fileDebug(File *file);

#endif /* FS_FILE_H */
