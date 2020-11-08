#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>

#define ID_ALL 100
#define ID_COPY 101
#define ID_PAST 102
#define ID_CUT 103

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szAppName[] = "PopPad1";
HMENU hmenu, hpopup;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG msg;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	!RegisterClassEx(&wc);
	hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hwndEdit;
	switch (uMsg) {
	case WM_CREATE:
		hwndEdit = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
			WS_BORDER | ES_LEFT | ES_MULTILINE |
			ES_AUTOHSCROLL | ES_AUTOVSCROLL,
			0, 0, 0, 0,
			hWnd, (HMENU)1,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hmenu = CreateMenu();
		hpopup = CreatePopupMenu();
		AppendMenu(hpopup, MF_STRING, ID_COPY, "Копировать");
		AppendMenu(hpopup, MF_STRING, ID_PAST, "Вставить");
		AppendMenu(hpopup, MF_STRING, ID_CUT, "Вырезать");
		AppendMenu(hmenu, MF_POPUP, (UINT)hpopup, "Редактирование");
		SetMenu(hWnd, hmenu);
		return 0;
	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		return 0;
	case WM_SIZE:
		MoveWindow(hwndEdit, 0, 0, LOWORD(lParam),
			HIWORD(lParam), TRUE);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1:
			if (HIWORD(wParam) == EN_ERRSPACE ||
				HIWORD(wParam) == EN_MAXTEXT)
				MessageBox(hWnd, "Edit control out of space.",
					szAppName, MB_OK | MB_ICONSTOP);
			break;
		case ID_COPY:
			SendMessage(hwndEdit, WM_COPY, 0, 0);
			break;
		case ID_PAST:
			SendMessage(hwndEdit, WM_PASTE, 0, 0);
			break;
		case ID_CUT:
			SendMessage(hwndEdit, WM_CUT, 0, 0);
			break;
		default:
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}