#include <Windows.h>
#include <stdio.h>
#include "host.h"

#define TARGET_FRAMERATE 60
#define WINDOW_CLASS_NAME L"Module2"
#define WINDOW_NAME L"Lesson 2.6"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static BOOL isRunning = TRUE;

float sys_initFloatTime(void);
float sys_floatTime(void);
void sys_shutdown(void);
LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void dprintf(char* format, ...);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = mainWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = WINDOW_CLASS_NAME;

	if (!RegisterClass(&wc))
		exit(EXIT_FAILURE);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;

	RECT r = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&r, windowStyle, FALSE);

	HWND mainWindow = CreateWindowEx(
		0,
		WINDOW_CLASS_NAME,
		WINDOW_NAME,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		hInstance,
		0);

	ShowWindow(mainWindow, SW_SHOWDEFAULT);

	HDC deviceContext = GetDC(mainWindow);
	PatBlt(deviceContext, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACKNESS);
	ReleaseDC(mainWindow, deviceContext);

	host_init();

	MSG msg;
	float newTime, oldTime, targetTime, accumulatedTime;

	targetTime = 1.f / TARGET_FRAMERATE;
	oldTime = sys_initFloatTime();
	accumulatedTime = 0.f;

	while (isRunning)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		newTime = sys_floatTime();
		accumulatedTime += newTime - oldTime;
		oldTime = newTime;
		if (accumulatedTime > targetTime)
		{
			host_frame(targetTime);
			accumulatedTime -= targetTime;
		}
	}

	//FIXME THIS HAS A WARP-SPEED EFFECT IN THE GAME IF FRAMRATE DROPS!!!!!!!!

	host_shutdown();

	return EXIT_SUCCESS;
}

LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_ACTIVATE:
			break;

		case WM_CREATE:
			break;

		case WM_DESTROY:
			sys_shutdown();
			break;

		default:
			result = DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
	}

	return result;
}

static LONGLONG initialTimeCount;
static double secondsPerTick;

float sys_initFloatTime(void)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	secondsPerTick = 1.0 / frequency.QuadPart;

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	initialTimeCount = counter.QuadPart;

	return 0.0f;
}

float sys_floatTime(void)
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	LONGLONG interval = counter.QuadPart - initialTimeCount;

	return (float) (interval * secondsPerTick);
}

void sys_shutdown(void)
{
	isRunning = FALSE;
}

void dprintf(char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	size_t n = vsnprintf(NULL, 0, format, argptr) + sizeof(char);
	char* buffer = (char*) malloc(n * sizeof(char));

	vsnprintf(buffer, n, format, argptr);
	OutputDebugStringA(buffer);

	va_end(argptr);
	free(buffer);
}