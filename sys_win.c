#include <Windows.h>
#include <stdio.h>

#define MAX_NUM_ARGVS 50

int argc = 0;
char *largv[MAX_NUM_ARGVS];

int COM_CheckParm(char* parm);
void dprintf(char* format, ...);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	while (*lpCmdLine != '\0' && argc < MAX_NUM_ARGVS)
	{
		while (*lpCmdLine == ' ')
			lpCmdLine++;

		if (*lpCmdLine == '\0')
			break;

		largv[argc++] = lpCmdLine;

		do {
			lpCmdLine++;
		} while (*lpCmdLine > ' ' && *lpCmdLine <= '~'); // printable chars except space

		if (*lpCmdLine == '\0')
			break;

		*lpCmdLine = '\0';
		lpCmdLine++;
	}

	int alphaIndex = COM_CheckParm("-setalpha");

	dprintf("alphaIndex = %d\n", alphaIndex);

	return 0;
}

int COM_CheckParm(char* parm)
{
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(parm, largv[i]) == 0)
			return i;
	}
	return -1;
}

void dprintf(char* format, ...)
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