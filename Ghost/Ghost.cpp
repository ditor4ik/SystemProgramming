#include<Windows.h>
#include<tchar.h>
#include "resource.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;
int APIENTRY _tWinMain(HINSTANCE This, //Дескриптор текущего приложения
	HINSTANCE Prev, //В современных системах всегда 0
	LPTSTR cmd, //Командная строка
	int mode) //Режим отображения окна

{
	HWND hWnd; //Дескриптор главного окна программы
	MSG msg; //Структура для хранения сообщения
	hInst = This;
	WNDCLASS wc;//Класс окна
	//Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; //Имя класса окна
	wc.lpfnWndProc = WndProc; //Имя класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.lpszMenuName = NULL; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(WinName,//Имя класса окна
		_T("Каркас Windows-приложения"),//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y Размеры окна
		CW_USEDEFAULT,//Width
		CW_USEDEFAULT,//Height
		HWND_DESKTOP,//Дескриптор родительской информации нет
		NULL,//Нет меню
		This,//Дескриптор приложения
		NULL);//Дополнительной информации нет
	ShowWindow(hWnd, mode);//Показать окно
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);//Посылает сообщение функции WndProc()
	}
	return 0;

}
//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	int i, x, y, p, q;
	static int k;
	static bool Capture;
	static POINT pts[3];
	static HDC memDC;
	static HBITMAP hPicture;
	static BITMAP bm;
	static HPEN hPen;
	switch (message)
	{
	case WM_CREATE:
		hPicture = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hPicture, sizeof(bm), &bm);
		hPen = CreatePen(PS_SOLID, 4, RGB(0,0,255));
		GetClientRect(hWnd, &rt);
		x = (rt.right - bm.bmWidth) / 2;
		y = (rt.bottom - bm.bmHeight) / 2;
		pts[0].x = pts[2].x = x;
		pts[0].y = pts[1].y = y;
		pts[1].x = x + bm.bmWidth;
		pts[2].y = y + bm.bmHeight;
		hdc = GetDC(hWnd);
		memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hPicture);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		for (k = 0; k < 3; k++) {
			p = x - pts[k].x;
			q = y - pts[k].y;
			if (p*p + q * q < 16)
			{
				SetCapture(hWnd);
				Capture = true;
				return 0;
			}
		}
		break;
	case WM_MOUSEMOVE:
		if (Capture)
		{
			pts[k].x = LOWORD(lParam);
			pts[k].y = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		if (Capture)
		{
			ReleaseCapture();
			Capture = false;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		PlgBlt(hdc, pts, memDC, 0, 0, bm.bmWidth, bm.bmHeight, 0, 0, 0);
		SelectObject(hdc, (HPEN)hPen);
		for (i = 0; i < 3; i++)
			Ellipse(hdc, pts[i].x - 4, pts[i].y - 4, pts[i].x + 4, pts[i].y + 4);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(memDC);
		DeleteObject(hPen);
		PostQuitMessage(0); 
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}