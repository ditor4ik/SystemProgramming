#define _USE_MATH_DEFINE
#include<Windows.h>
#include<tchar.h>
#include <cmath>
#include <stdio.h>
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
	HBRUSH yBrush;


	switch (uMsg) {
	case WM_CREATE:
		hpen1 = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		hpen2 = CreatePen(PS_SOLID, 4, RGB(255, 0, 255));
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 2 * WIDTH, -2 * HEIGHT, NULL);
		SetViewportExtEx(hDC, sx / 2, sy / 2, NULL);
		SetViewportOrgEx(hDC, 0, sy / 12, NULL);
		yBrush = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hDC, yBrush);
		Ellipse(hDC, 0, 0, 60, 60);
		TextOut(hDC, 70, 40, _T("сплошное заполнение"), strlen("сплошное заполнение"));


		for (int i = 2; i <= 7; i++) {
			SetWindowExtEx(hDC, 2 * WIDTH, -2 * HEIGHT, NULL);
			SetViewportExtEx(hDC, sx / 2, sy / 2, NULL);
			SetViewportOrgEx(hDC, 0, i * sy / 12, NULL);

			switch (i) {
			case 2:
				yBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 0));
				SelectObject(hDC, yBrush);
				Rectangle(hDC, 0, 0, 60, 60);
				TextOut(hDC, 70, 40, _T("HS_BDIAGONAL - слева направо и снизу вверх"), strlen("HS_BDIAGONAL - слева направо и снизу вверх"));
				break;
			case 3:
				yBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 0));
				SelectObject(hDC, yBrush);
				Rectangle(hDC, 0, 0, 60, 60);
				TextOut(hDC, 70, 40, _T("HS_CROSS - горизантальная и вертикальная штриховка"), strlen("HS_CROSS - горизантальная и вертикальная штриховка"));
				break;
			case 4:
				yBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 0));
				SelectObject(hDC, yBrush);
				Rectangle(hDC, 0, 0, 60, 60);
				TextOut(hDC, 70, 40, _T("HS_DIAGCROSS - под углом в 45 градусов"), strlen("HS_DIAGCROSS - под углом в 45 градусов"));
				break;
			case 5:
				yBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 0));
				SelectObject(hDC, yBrush);
				Rectangle(hDC, 0, 0, 60, 60);
				TextOut(hDC, 70, 40, _T("HS_FDIAGONAL - слева-направа и сверху вниз"), strlen("HS_FDIAGONAL - слева-направа и сверху вниз"));
				break;
			case 6:
				yBrush = CreateHatchBrush(HS_HORIZONTAL, RGB(0, 0, 0));
				SelectObject(hDC, yBrush);
				Rectangle(hDC, 0, 0, 60, 60);
				TextOut(hDC, 70, 40, _T("HS_HORIZONTAL - горизантальная штриховка"), strlen("HS_HORIZONTAL - горизантальная штриховка"));
				break;
			case 7:
				yBrush = CreateHatchBrush(HS_VERTICAL, RGB(0, 0, 0));
				SelectObject(hDC, yBrush);
				Rectangle(hDC, 0, 0, 60, 60);
				TextOut(hDC, 70, 40, _T("HS_VERTICAL - вертикальная штриховка"), strlen("HS_VERTICAL - вертикальная штриховка"));
				break;
			}
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