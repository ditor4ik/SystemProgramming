#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<xstring>

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> String;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY _tWinMain(HINSTANCE This,
	HINSTANCE Prev,
	LPTSTR cmd,
	int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	//Заполняем структуру класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
	wc.hCursor = LoadCursor(NULL, IDC_NO);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//Регистрируем класс окна
	if (!RegisterClass(&wc)) return 0;

	//Создаем основное окно приложения
	hWnd = CreateWindow(WinName,
		_T("Каркас Windows-приложения"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hWnd, mode);
	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT massage,
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int x, y, a, b;
	double angle;
	static int sx, sy;
	int R = 100;
	float M_PI = 3.14f;
	switch (massage) {
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		a = sx / 2;
		b = sy / 2;
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);

		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, sy);
		for (angle = .0; angle < 2 * M_PI; angle += 0.1)
		{
			x = a + R * (1 - cos(angle)) * cos(angle);
			y = b - R * (1 - cos(angle)) * sin(angle);
			LineTo(hdc, x, y);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, massage, wParam, lParam);
	}
	return 0;

}