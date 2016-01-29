#include <Windows.h>
#include <stdint.h>
#include <stdio.h>

typedef uint8_t uchar;
typedef int32_t int32;
typedef uint32_t uint32;

#define MAX_NUM_ARGVS 50

int32 argc = 0;
uchar* largv[MAX_NUM_ARGVS];

int32 COM_CheckParm(uchar* parm);
int32 Q_strcmp(uchar* s1, uchar* s2);
int32 Q_atoi(uchar* str);
void dprintf(uchar* format, ...);

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow)
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

	int32 alphaIndex = COM_CheckParm("-setalpha");
	int32 alphaValue = Q_atoi(largv[alphaIndex + 1]);

	dprintf("alphaValue = %d\n", alphaValue);

	return 0;
}

int32 COM_CheckParm(uchar* parm)
{
	for (int32 i = 0; i < argc; i++)
	{
		if (Q_strcmp(parm, largv[i]) == 0)
			return i;
	}
	return -1;
}

int32 Q_strcmp(uchar* s1, uchar* s2)
{
	while (*s1 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

int32 Q_atoi(uchar* str)
{
	int32 sign = 1;
	int32 val = 0;

	if (*str == '-')
	{
		sign = -1;
		*str++;
	}

	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) //hex
	{
		str += 2;
		uchar c;
		while (*str != '\0')
		{
			c = *str++;
			val *= 16;
			if (c >= 'a' && c <= 'f')
				val += c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val += c - 'a' + 10;
			else
				val += c - '0';
		}
	}
	else //decimal
	{
		uchar c;
		while (*str != '\0')
		{
			c = *str++;
			val *= 10;
			val += c - '0';
		}
	}
	return sign * val;
}

void dprintf(uchar* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	size_t n = vsnprintf(NULL, 0, format, argptr) + sizeof(uchar);
	uchar* buffer = (uchar*)malloc(n * sizeof(uchar));

	vsnprintf(buffer, n, format, argptr);
	OutputDebugStringA(buffer);

	va_end(argptr);
	free(buffer);
}