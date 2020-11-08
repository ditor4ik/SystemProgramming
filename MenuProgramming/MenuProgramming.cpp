#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>
#include"menudemo.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR str[] = _T("Наклонный текст");
TCHAR szClassName[] = _T("MyClass");
HPEN hRedPen, hGreenPen, hBluePen, hPurplePen;
HBRUSH hYellowBrush, hGreenBrush, hBlueBrush, hPurpleBrush;
int sw;
//==================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HWND hMainWnd;

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hmenu, hpopupmenu, hpopupmenu1;
	TCHAR str0[] = _T("Фон");
	TCHAR str6[] = _T("Признаки");
	TCHAR str1[] = _T("Синий");
	TCHAR str2[] = _T("Зеленый");
	TCHAR str3[] = _T("Выход");
	TCHAR str4[] = _T("заблокированный");
	TCHAR str5[] = _T("Желтый");
	TCHAR str7[] = _T("Фиолетовый");


	switch (uMsg) {
	case WM_COMMAND:
		hmenu = GetMenu(hWnd);
		switch (LOWORD(wParam)) {
		case MI_BLUE:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_GREEN:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_YELLOW:
			sw = 3;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_PURPLE:
			sw = 5;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_EXIT:
			DestroyWindow(hWnd);
			break;
		case MI_ENABLED:
			sw = 4;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	case WM_CREATE:
		hBlueBrush = CreateSolidBrush(RGB(100, 100, 255));
		hGreenBrush = CreateSolidBrush(RGB(100, 255, 100));
		hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
		hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
		hGreenBrush = CreateSolidBrush(RGB(100, 255, 100));
		hPurpleBrush = CreateSolidBrush(RGB(100, 50, 255));
		hmenu = CreateMenu();
		hpopupmenu = CreatePopupMenu();
		AppendMenu(hpopupmenu, MF_STRING, MI_BLUE, str1);
		AppendMenu(hpopupmenu, MF_STRING, MI_GREEN, str2);
		AppendMenu(hpopupmenu, MF_STRING, MI_YELLOW, str5);
		AppendMenu(hpopupmenu, MF_STRING, MI_PURPLE, str7);
		AppendMenu(hpopupmenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hpopupmenu, MF_STRING, MI_EXIT, str3);
		AppendMenu(hmenu, MF_POPUP, (UINT)hpopupmenu, str0);
		hpopupmenu1 = CreatePopupMenu();

		AppendMenu(hpopupmenu1, MF_STRING, MI_ENABLED, str5);
		AppendMenu(hpopupmenu1, MF_STRING, MI_DISABLED, str7);
		AppendMenu(hpopupmenu1, MF_STRING, MI_GRAYED, str4);

		AppendMenu(hmenu, MF_POPUP, (UINT)hpopupmenu1, str6);

		EnableMenuItem(hmenu, MI_ENABLED, MI_ENABLED);
		EnableMenuItem(hmenu, MI_DISABLED, MI_DISABLED);
		EnableMenuItem(hmenu, MI_GRAYED, MI_GRAYED);
		SetMenu(hWnd, hmenu);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (sw == 1)
			FillRect(hdc, &ps.rcPaint,
				hBlueBrush);
		if (sw == 2)
			FillRect(hdc, &ps.rcPaint, hGreenBrush);
		if (sw == 3)
			FillRect(hdc, &ps.rcPaint, hYellowBrush);
		if (sw == 5)
			FillRect(hdc, &ps.rcPaint, hPurpleBrush);
		if (sw == 4)
			FillRect(hdc, &ps.rcPaint, hYellowBrush);

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