#include "quakedef.h"

int32 com_argc = 0;
uchar* com_argv[MAX_NUM_ARGVS];

int32 COM_checkParm(uchar* parm)
{
	for (int32 i = 0; i < com_argc; i++)
	{
		if (Q_strcmp(parm, com_argv[i]) == 0)
			return i;
	}
	return -1;
}

void COM_parseCmdLine(uchar *lpCmdLine)
{
	while (*lpCmdLine != '\0' && com_argc < MAX_NUM_ARGVS)
	{
		while (*lpCmdLine == ' ')
			lpCmdLine++;

		if (*lpCmdLine == '\0')
			break;

		com_argv[com_argc++] = lpCmdLine;

		do {
			lpCmdLine++;
		} while (*lpCmdLine > ' ' && *lpCmdLine <= '~'); // printable chars except space

		if (*lpCmdLine == '\0')
			break;

		*lpCmdLine = '\0';
		lpCmdLine++;
	}
}