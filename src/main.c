#include <stdio.h>

#include "debug/log.h"
#include "fs/file.h"
#include "fs/header.h"

int main(int argc, char *argv[])
{
	Header header;
	File file;

	(void)argc;
	(void)argv;

	logMessage(LOG_TRACE, "main()");
	logSignals();

	fileOpen(&file, "disk.iso");
	fileDebug(&file);

	headerRead(&header, &file);
	headerDebug(&header);

	fileClose(&file);

	return 0;
}
