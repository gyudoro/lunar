#include "fs/header.h"

#include "debug/log.h"
#include "fs/file.h"

void dataHeaderRead(DataHeader *header, File *file)
{
	logMessage(LOG_TRACE, "dataHeaderRead()");

	header->console = fileGetChar(file);
	header->game = fileGetShort(file);
	header->country = fileGetChar(file);
	header->maker = fileGetShort(file);

	header->id = fileGetChar(file);
	header->version = fileGetChar(file);

	fileSeek(file, 0x420);

	header->mainLocation = fileGetLong(file);
	header->fstLocation = fileGetLong(file);
	header->fstSize = fileGetLong(file);
	header->fstSizeMax = fileGetLong(file);
}

void dataHeaderDebug(DataHeader *header)
{
	logMessage(LOG_TRACE, "dataHeaderDebug()");

	logMessage(LOG_DEBUG, "Console ID: %c", header->console);
	logMessage(LOG_DEBUG, "Gamecode: %x", (int)header->game);
	logMessage(LOG_DEBUG, "Country Code: %c", header->country);
	logMessage(LOG_DEBUG, "Maker Code: %x", (int)header->maker);

	logMessage(LOG_DEBUG, "Disk ID: %x", (int)header->id);
	logMessage(LOG_DEBUG, "Version: %x", (int)header->version);

	logMessage(LOG_DEBUG, "Main Location: %ld",
	           (long)header->mainLocation); 

	logMessage(LOG_DEBUG, "FST Location: %ld",
	           (long)header->fstLocation); 

	logMessage(LOG_DEBUG, "FST Size: %ld", (long)header->fstSize); 

	logMessage(LOG_DEBUG, "FST Max Size: %ld",
	           (long)header->fstSizeMax); 
}
