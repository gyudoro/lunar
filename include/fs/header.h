#ifndef FS_HEADER_H
#define FS_HEADER_H

#include "fs/file.h"

typedef struct {
	u8 console;
	u16 game;
	u8 country;
	u16 maker;

	u8 id;
	u8 version;

	/* the rest is TODO */

	u32 mainLocation;
	u32 fstLocation;
	u32 fstSize;
	u32 fstSizeMax;
} DataHeader;

void dataHeaderRead(DataHeader *header, File *file);
void dataHeaderDebug(DataHeader *header);

#endif /* FS_HEADER_H */
