#include "quakedef.h"
#include "winquake.h"

#include <stdio.h>

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow)
{
	COM_parseCmdLine(lpCmdLine);

	int32 alphaIndex = COM_checkParm("-setalpha");
	int32 alphaValue = Q_atoi(com_argv[alphaIndex + 1]);

	COM_dprintf("alphaValue = %d\n", alphaValue);

	return EXIT_SUCCESS;
}

// declared in common.h but implementation is platform dependent
void COM_dprintf(char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	size_t n = vsnprintf(NULL, 0, format, argptr) + sizeof(char);
	char* buffer = (char*)malloc(n * sizeof(char));

	vsnprintf(buffer, n, format, argptr);
	OutputDebugStringA(buffer);

	va_end(argptr);
	free(buffer);
}
