#include<Windows.h>
#define DIVISIONS 5
#define MoveTo(hdc, x, y) MoveToEx(hdc, x, y, NULL)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
char szChildClass[] = "Checker3_child";

int WINAPI WinMain(HINSTANCE This, //Дескриптор текущего приложения
	HINSTANCE Prev, //В современных системах всегда 0
	PSTR cmd, //Командная строка
	int mode) //Режим отображения окна
{
	static char szAppName[] = "Checker3";
	HWND hWnd; //Дескриптор главного окна программы
	MSG msg; //Структура для хранения сообщения
	WNDCLASSEX wc;//Класс окна
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.lpfnWndProc = WndProc; //Имя класса окна
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных класса
	wc.hInstance = This;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL; //Нет меню
	wc.lpszClassName = szAppName; //Нет меню
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);//Регистрация класса окна
	wc.lpfnWndProc = ChildWndProc;
	wc.cbWndExtra = sizeof(WORD); //Нет дополнительных данных окна
	wc.hIcon = NULL;
	wc.lpszClassName = szChildClass;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(szAppName,//Имя класса окна
		"Icon and Cursor Demo",//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y Размеры окна
		CW_USEDEFAULT,//Width
		CW_USEDEFAULT,//Height
		//Дескриптор родительской информации нет
		NULL,//Нет меню
		NULL,//Дескриптор приложения
		This, NULL);//Дополнительной информации нет
	ShowWindow(hWnd, mode);//Показать окно
	UpdateWindow(hWnd);
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);//Посылает сообщение функции WndProc()
	}
	return msg.wParam;

}
//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndChild[DIVISIONS][DIVISIONS];
	int cxBlock, cyBlock, x, y;
	//Обработчик сообщений
	switch (message)
	{
	case WM_CREATE:
		for (x = 0; x < DIVISIONS; x++)
			for (y = 0; y < DIVISIONS; y++) {
				hwndChild[x][y] = CreateWindow(szChildClass, NULL,
					WS_CHILDWINDOW | WS_VISIBLE,
					0, 0, 0, 0,
					hWnd, (HMENU)(y << 0 | x),
					(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
					NULL);
			}
		return 0;
	case WM_SIZE:
		cxBlock = LOWORD(lParam) / DIVISIONS;
		cyBlock = HIWORD(lParam) / DIVISIONS;
		for (x = 0; x < DIVISIONS; x++)
			for (y = 0; y < DIVISIONS; y++)
				MoveWindow(hwndChild[x][y],
					x * cxBlock, y * cyBlock,
					cxBlock, cyBlock, TRUE);
		return 0;
	case WM_LBUTTONDOWN:
		MessageBeep(0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;//Завершение программы
		//Обработка сообщений по умолчанию
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		SetWindowWord(hWnd, 0, 0);
		return 0;
	case WM_LBUTTONDOWN:
		SetWindowWord(hWnd, 0, 1 ^ GetWindowWord(hWnd, 0));
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		Rectangle(hdc, 0, 0, rect.right, rect.bottom);
		if (GetWindowWord(hWnd, 0)) {
			MoveTo(hdc, 0, 0);
			LineTo(hdc, rect.right, rect.bottom);
			MoveTo(hdc, 0, rect.bottom);
			LineTo(hdc, rect.right, 0);
		}
		EndPaint(hWnd, &ps);
		return 0;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
}