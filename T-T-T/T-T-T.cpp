#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>
#include<commdlg.h>
#include<fstream>
#include<vector>
#include<string>
#include"Header.h"
TCHAR ChildClassName[MAX_LOADSTRING] = _T("Child");
const int LineH = 16;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szChildClass[] = _T("Checker_Child");
HINSTANCE hinst;
HMENU hmenu, hpopup;
//==================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	TCHAR szAppName[] = _T("Checker");
	HWND hMainWnd;
	MSG msg;
	WNDCLASSEX wc;
	hinst = hInstance;
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
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(hInstance, szAppName);
	//Регистрируем класс окна
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hMainWnd = CreateWindow(szAppName, _T("Крестики-нолики"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
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

}
ATOM MyRegisterChildClass() {
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = ChildWndProc;
	wcex.hInstance = hinst;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = ChildClassName;
	return RegisterClassEx(&wcex);
}
static HFONT nF;
static HWND hChild[9];
unsigned char k[9] = { 0 };
char text[] = { ' ','x','0' };
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int i;
	static int sx, sy;
	TCHAR str1[] = _T("NEW");
	TCHAR str2[] = _T("EXIT");
	TCHAR str0[] = _T("MENU");
	switch (uMsg) {
	case WM_CREATE:
		MyRegisterChildClass();
		for (i = 0; i < 9; i++)
			hChild[i] = CreateWindow(ChildClassName, NULL, WS_CHILD | WS_DLGFRAME | WS_VISIBLE, 0, 0, 0, 0, hwnd, NULL, hinst, NULL);
		hmenu = CreateMenu();
		hpopup = CreatePopupMenu();
		AppendMenu(hpopup, MF_STRING, ID_NEW, str1);
		AppendMenu(hpopup, MF_STRING, IDM_EXIT, str2);
		AppendMenu(hmenu, MF_POPUP, (UINT)hpopup, str0);
		SetMenu(hwnd, hmenu);
		break;
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)break;
		sx = LOWORD(lParam) / 3;
		sy = HIWORD(lParam) / 3;
		if (nF)DeleteObject(nF);
		nF = CreateFont(min(sx, sy), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
		for (i = 0; i < 9; i++) {
			MoveWindow(hChild[i], (i % 3) * sx, (i / 3) * sy, sx, sy, TRUE);
			UpdateWindow(hChild[i]);
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_NEW:
			for (i = 0; i < 9; i++) {
				k[i] = 0;
				InvalidateRect(hChild[i], NULL, 1);
				UpdateWindow(hChild[i]);
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}
LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	int i, s;
	char* ch;
	switch (uMsg)
	{
	case WM_CREATE:
		SetWindowWord(hwnd, 0, 0);
		return 0;
	case WM_LBUTTONDOWN:
		for (i = 0; hwnd != hChild[i]; i++);
		if (k[i])break;
		else k[i] = 1;
		InvalidateRect(hwnd, NULL, 1);
		UpdateWindow(hwnd);
		srand(lParam);
		for (i = s = 0; i < 9; i++)
			if (k[i])s++;
		if (s == 9)
			MessageBox(hwnd, _T("Для новой игры выбирайте New"), _T("Конец игры"), MB_OK | MB_ICONQUESTION);
		else {
			while (true) {
				s = rand() * 9 / (RAND_MAX + 1);
				if (k[s]) continue;
				k[s] = 2;
				InvalidateRect(hChild[s], NULL, 1);
				UpdateWindow(hChild[s]);
				break;
			}
		}
		break;

	case WM_PAINT:

		for (i = 0; hwnd != hChild[i]; i++);
		if (k[i]) {
			ch = text + k[i];
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rt);
			SelectObject(hdc, nF);
			DrawTextA(hdc, ch, 1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
		}
		else DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}