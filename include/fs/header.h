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
} Header;

typedef struct {
	u8 date[9];

	u32 entrypoint;
	u32 size;
	u32 trailerSize;
} Apploader;

void headerRead(Header *header, File *file);
void headerDebug(Header *header);

#endif /* FS_HEADER_H */
