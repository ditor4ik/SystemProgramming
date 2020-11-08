#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("MainFrame");
//==================================================================================
int APIENTRY WinMain(HINSTANCE This,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	TCHAR szTitle[] = _T("Фигуры");
	MSG msg;
	WNDCLASS wc;
	//Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = This;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	//Регистрируем класс окна
	if (!RegisterClass(&wc)) return 0;

	//Создаем основное окно приложения
	HWND hwnd = CreateWindow(szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hwnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	HFONT oldFont, newFont;
	int SizeFont;
	float SizeIn = 0;
	static int sx, sy;
	TCHAR s[10];
	TCHAR str[] = _T("дюйм");
	switch (uMsg) {
	case WM_SIZE:
		sx = LOWORD(lParam) / 2;
		sy = HIWORD(lParam) / 2;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		for (SizeFont = 8; SizeFont < 97; SizeFont += 8)
		{
			newFont = CreateFont(SizeFont - SizeFont * (3 / 4), SizeFont, 0, 0, 0, 0, 0, 0,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Times New Roman"));
			oldFont = (HFONT)SelectObject(hdc, newFont);
			_itot(float(float(SizeFont) * 0.010378), s, 10);
			TextOut(hdc, 0, SizeFont * 4, str, _tcsclen(str));
			//TextOut(hdc, SizeFont * 6, SizeFont * 4, s, _tcslen(s));
			SelectObject(hdc, oldFont);
			DeleteObject(newFont);
		}
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