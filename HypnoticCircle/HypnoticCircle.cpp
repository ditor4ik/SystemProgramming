#define _USE_MATH_DEFINE
#include<Windows.h>
#include<tchar.h>
#include <cmath>
const int WIDTH = 314;
const int HEIGHT = 200;
const double K = 4.0;
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
	return msg.wParam;
	char path[100];



}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,

	LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	int x_str, y_str;
	static HPEN hpen1, hpen2;
	static int sx, sy;
	double x;
	double PI = 3.14;
	double a = 2 * PI * 1;


	switch (uMsg) {
	case WM_CREATE:
		hpen1 = CreatePen(PS_SOLID, 4, RGB(255, 136, 0));
		hpen2 = CreatePen(PS_SOLID, 4, RGB(173, 252, 144));
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 1300, 1200, NULL);
		SetViewportExtEx(hDC, sx, sy * 6 / 4, NULL);
		SetViewportOrgEx(hDC, sx / 1 / 2, sy / 2, NULL);
		SelectObject(hDC, hpen2);
		MoveToEx(hDC, -WIDTH, 0, NULL);
		LineTo(hDC, WIDTH, 0);
		MoveToEx(hDC, 0, HEIGHT, NULL);
		LineTo(hDC, 0, -HEIGHT);
		SelectObject(hDC, hpen1);
		MoveToEx(hDC, 0, 0, NULL);
		for (double i = 0; i < 100; i += 0.1) {
			double phi = -i * 0.5;
			int r = K * i;
			int X = r * cos(phi);
			int Y = r * sin(phi);
			LineTo(hDC, X, Y);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hpen1);
		DeleteObject(hpen2);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}