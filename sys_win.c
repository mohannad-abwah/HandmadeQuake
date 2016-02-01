#include "quakedef.h"
#include "winquake.h"

#include <stdio.h>

void parseCmdLine(uchar *lpCmdLine);

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow)
{
	COM_parseCmdLine(lpCmdLine);

	int32 alphaIndex = COM_checkParm("-setalpha");
	int32 alphaValue = Q_atoi(com_argv[alphaIndex + 1]);

	COM_dprintf("alphaValue = %d\n", alphaValue);

	return 0;
}

// declared in common.h but implementation is platform dependent
void COM_dprintf(uchar* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	size_t n = vsnprintf(NULL, 0, format, argptr) + sizeof(uchar);
	uchar* buffer = (uchar*)malloc(n * sizeof(uchar));

	vsnprintf(buffer, n, format, argptr);
	OutputDebugString(buffer);

	va_end(argptr);
	free(buffer);
}
