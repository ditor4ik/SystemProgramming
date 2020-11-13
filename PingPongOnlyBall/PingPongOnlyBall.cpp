#include<Windows.h>
#include<tchar.h>
#include "resource.h"

HMENU menu;
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
const int SPAN = 10;
#include <math.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC hdc;
	int mx, my;
	static double mod, vx, vy, xt, yt;
	static HDC memDC;
	static HPEN hpen;
	static int x, y, cx, cy, scrx, scry;
	static HBITMAP hCircle;
	static bool play;
	
	switch (message)
	{
	case WM_CREATE:
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hCircle = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_SMALLBALL));;
		hdc = GetDC(hWnd);
		memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hCircle);
		ReleaseDC(hWnd, hdc);
		menu = LoadMenu(hInst, MAKEINTRESOURCE(IDC_MENU));
		SetMenu(hWnd, menu);
		break;
	case WM_SIZE:
		scrx = LOWORD(lParam);
		scry = HIWORD(lParam);
		x = (cx = scrx / 2) - 16;
		y = (cy = scry / 2) - 16;
		break;
	case WM_LBUTTONDOWN:
		if (!play)
		{
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			vx = mx - cx;
			vy = my - cy;
			mod = sqrt(vx * vx + vy * vy);
			vx = vx / mod;
			vy = vy / mod;
			hdc = GetDC(hWnd);
			SelectObject(hdc, hpen);
			MoveToEx(hdc, cx, cy, 0);
			LineTo(hdc, mx, my);
			LineTo(hdc, mx - (vx - vy) * SPAN, my - (vy + vx) * SPAN);
			MoveToEx(hdc, mx - (vx + vy) * SPAN, my - (vy - vx) * SPAN, 0);
			LineTo(hdc, mx, my);
			ReleaseDC(hWnd, hdc);
			play = true;
		}
		break;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		BitBlt(hdc, x, y, 32, 32, NULL, 0, 0, PATCOPY);
		if (x + 31 > scrx || x < 1) vx = -vx;
		if (y + 31 > scry || y < 1) vy = -vy;
		xt += vx * 10;
		yt += vy * 10;
		x = int(xt + 0.5);
		y = int(yt + 0.5);
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			
		case ID_PLAY_PLAYBEGIN:
			SetTimer(hWnd, 1,(int)(sqrt(double(cx*cx+cy*cy))/mod)*10, NULL);
			xt = x;
			yt = y;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_PLAY_PLAYEND:
			KillTimer(hWnd,1);
			x = cx - 16;
			y = cy - 16;
			InvalidateRect(hWnd, NULL, TRUE);
			play = false;
			break;
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(memDC);
		DeleteObject(hpen);
		PostQuitMessage(0); 
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}