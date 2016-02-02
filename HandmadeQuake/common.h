#pragma once

#define MAX_NUM_ARGVS 50

extern int32 com_argc;
extern char* com_argv[MAX_NUM_ARGVS];

// implementation is platform dependent
void COM_dprintf(char* format, ...);

void COM_parseCmdLine(char *lpCmdLine);
int32 COM_checkParm(char* parm);