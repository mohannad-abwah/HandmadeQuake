#include <Windows.h>

#define WINDOW_CLASS_NAME L"Module2"
#define WINDOW_NAME L"Lesson 2.1"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = MainWndProc;
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

	return EXIT_SUCCESS;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}