#include <Windows.h>
#include <stdio.h>

#define WINDOW_CLASS_NAME L"Module2"
#define WINDOW_NAME L"Lesson 2.3"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

BOOL isRunning = TRUE;

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

	const LARGE_INTEGER frequency;
	LARGE_INTEGER tick, tock;
	MSG msg;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&tick);
	while (isRunning)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		QueryPerformanceCounter(&tock);

		LONGLONG interval = tock.QuadPart - tick.QuadPart;
		double timeLapsed = (double) interval / frequency.QuadPart;

		dprintf("Time elapsed: %3.7f\n", timeLapsed);

		QueryPerformanceCounter(&tick);

		Sleep(100);
	}

	return EXIT_SUCCESS;
}

LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_KEYUP:
			isRunning = FALSE;
			break;

		default:
			result = DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
	}

	return result;
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