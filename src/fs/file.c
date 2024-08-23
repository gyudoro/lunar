#include "fs/file.h"

#include <stdio.h>

#include "common/types.h"
#include "debug/log.h"

void fileOpen(File *file, const char *name)
{
	logMessage(LOG_TRACE, "fileOpen()");
	logMessage(LOG_DEBUG, "Opening file %s...", name);

	file->name = name;
	file->data = fopen(name, "rb");

	if (file->data == NULL)
		logMessage(LOG_OS, "Could not open file %s", name);
}

void fileClose(File *file)
{
	logMessage(LOG_TRACE, "fileClose()");

	fclose(file->data);
}

i8 fileGetChar(File *file)
{
	i8 res;

	logMessage(LOG_TRACE, "fileGetChar()");
	res = fgetc(file->data);

	if (res == EOF && ferror(file->data))
		logMessage(LOG_OS, "fgetc() threw error");

	return res;
}

u16 fileGetShort(File *file)
{
	u16 total;
	i8 res;

	logMessage(LOG_TRACE, "fileGetShort()");

	total = 0;
	res = fileGetChar(file);

	if (res == EOF)
		logMessage(LOG_FATAL, "Failed to read 2 bytes");

	total += (u8)res;
	total <<= 8;

	res = fileGetChar(file);

	if (res == EOF)
		logMessage(LOG_FATAL, "Failed to read 2 bytes");

	total += (u8)res;
	return total;
}

u32 fileGetLong(File *file)
{
	u32 total;
	i8 res;

	logMessage(LOG_TRACE, "fileGetLong()");

	total = 0;
	res = fileGetChar(file);

	if (res == EOF)
		logMessage(LOG_FATAL, "Failed to read 4 bytes");

	total += (u8)res;
	total <<= 8;

	res = fileGetChar(file);

	if (res == EOF)
		logMessage(LOG_FATAL, "Failed to read 4 bytes");

	total += (u8)res;
	total <<= 8;

	res = fileGetChar(file);

	if (res == EOF)
		logMessage(LOG_FATAL, "Failed to read 4 bytes");

	total += (u8)res;
	total <<= 8;

	res = fileGetChar(file);

	if (res == EOF)
		logMessage(LOG_FATAL, "Failed to read 4 bytes");

	total += (u8)res;
	return total;
}

void fileSeek(File *file, long offset)
{
	int res;

	res = fseek(file->data, offset, SEEK_SET);

	if (res != 0)
		logMessage(LOG_OS, "fseek() returned %d", res);
}

void fileDebug(File *file)
{
	long pos;

	logMessage(LOG_DEBUG, "File name: %s", file->name);
	logMessage(LOG_DEBUG, "File pointer: %p", file->data);

	pos = ftell(file->data);

	if (pos == -1L)
		logMessage(LOG_OS, "ftell() returned -1L");

	logMessage(LOG_DEBUG, "File cursor: %ld", pos);
}
