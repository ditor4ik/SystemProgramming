﻿#include<Windows.h>
#include<tchar.h>
RECT pRect = { -100, -100, 100, 100 };
RECT pEllipse = { -120, -80, 120, 80 };
RECT pSm = { -60, -40, 60, 40 };
const int WIDTH = 400;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,

	LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static int sx, sy;
	HRGN hRgnEllipse;
	HRGN hRgn;
	static HBRUSH hBrush;
	switch (uMsg) {
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_CREATE:
		hBrush = CreateSolidBrush(RGB(200, 46, 27));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, WIDTH, -WIDTH, NULL);
		SetViewportExtEx(hdc, sx, sy, NULL);
		SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);
		hRgn = CreateRectRgnIndirect(&pRect);
		hRgnEllipse = CreateEllipticRgnIndirect(&pEllipse);
		CombineRgn(hRgn, hRgn, hRgnEllipse, RGN_DIFF);
		DeleteObject(hRgnEllipse);
		hRgnEllipse = CreateEllipticRgnIndirect(&pSm);
		CombineRgn(hRgn, hRgn, hRgnEllipse, RGN_OR);
		DeleteObject(hRgnEllipse);
		FillRgn(hdc, hRgn, hBrush);
		DeleteObject(hRgn);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}