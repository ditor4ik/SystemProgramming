#define _USE_MATH_DEFINES
#include<Windows.h>
#include<tchar.h>
#include <stdlib.h>
#include <ctime>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawRectangle(HWND hwnd);
int cxClient, cyClient;
//==================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("MyClass");
	MSG msg;
	WNDCLASSEX wc;
	//Заполняем структуру класса окна
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//Регистрируем класс окна
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hMainWnd = CreateWindow(szClassName, _T("A Hello1 Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	//Показываем окно
	ShowWindow(hMainWnd, nCmdShow);
	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam) {
	static POINT apt[4];
	HDC hdc;
	static int t;

	PAINTSTRUCT ps;
	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hwnd, 1, 100, NULL);
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		DrawRectangle(hwnd);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
//void CreateRect(Rect rect, Start)
void DrawRectangle(HWND hwnd)
{
	HBRUSH hBrush;
	HDC hdc;
	RECT rect;

	if (cxClient == 0 || cyClient == 0)
		return;
	int x = rand() % cxClient, y = rand() % cyClient;
	int width = x + rand() % cxClient / 4, height = y + rand() % cyClient / 4;
	SetRect(&rect, x, y, width, height);
	if (rand() % 2) hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	else hBrush = CreateHatchBrush(rand() % 6, RGB(rand() % 256, rand() % 256, rand() % 256));

	hdc = GetDC(hwnd);
	FillRect(hdc, &rect, hBrush);
	ReleaseDC(hwnd, hdc);
	DeleteObject(hBrush);
}