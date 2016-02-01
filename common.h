#pragma once

#define MAX_NUM_ARGVS 50

extern int32 com_argc;
extern uchar* com_argv[MAX_NUM_ARGVS];

// implementation is platform dependent
void COM_dprintf(uchar* format, ...);

void COM_parseCmdLine(uchar *lpCmdLine);
int32 COM_checkParm(uchar* parm);