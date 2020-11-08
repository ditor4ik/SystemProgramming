#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define ID_COMBODAY 100
#define ID_COMBOMONTH 101
#define ID_COMBOYEAR 102
#define ID_TAKE 103
#define ID_EXIT 104
LPSTR ReturnDate(int day, int month, int year);

char szAppName[] = "PopPad1";

HINSTANCE hInst;
HBRUSH hBrush;

HWND hComboBox, hListBox, hComboYear, hExit, hTake;

char Buf1[80], Buf[80];
HDC hdc1, memdc;
PAINTSTRUCT ps;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG lpMsg;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return 0;
	hWnd = CreateWindow(szAppName, "Демонстрация списков", WS_OVERLAPPEDWINDOW, 100, 100, 300, 500, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessageW(&lpMsg);
	}
	return (int)lpMsg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int i;
	int date, month, year;
	int maxX = 0, maxY = 0;

	char day[2];

	HBITMAP hbit;

	LPCSTR masMonth[12] = {
	"Январь", "Февраль", "Март", "Апрель","Май","Июнь",
	"Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"
	};
	switch (uMsg) {
	case WM_CREATE:
		hdc1 = GetDC(hWnd);

		maxX = GetSystemMetrics(SM_CXSCREEN);
		maxY = GetSystemMetrics(SM_CYSCREEN);

		hComboBox = CreateWindow("Combobox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			CBS_DROPDOWNLIST | CBS_HASSTRINGS,
			90, 80, 100, 200, hWnd, (HMENU)ID_COMBODAY, hInst, NULL);

		hListBox = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			WS_TABSTOP | WS_BORDER,
			90, 140, 100, 200, hWnd, (HMENU)ID_COMBOMONTH, hInst, NULL);

		hComboYear = CreateWindow("Combobox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
			90, 360, 100, 200, hWnd, (HMENU)ID_COMBOYEAR, hInst, NULL);

		hTake = CreateWindow("button", "Выбрать", WS_CHILD | WS_VISIBLE,
			90, 415, 100, 27, hWnd, (HMENU)ID_TAKE, hInst, NULL);

		hExit = CreateWindow("button", "Выход", WS_CHILD | WS_VISIBLE,
			90, 450, 100, 27, hWnd, (HMENU)ID_EXIT, hInst, NULL);

		for (i = 1; i < 32; i++)
		{
			_itoa(i, day, 10);

			SendMessage(hComboBox, CB_ADDSTRING, 1, (LPARAM)day);
		}

		SendMessage(hComboBox, CB_SETCURSEL, 0, 0L);

		for (i = 0; i < 12; i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 1, (LPARAM)masMonth[i]);
		}

		SendMessage(hListBox, LB_SETCURSEL, (WPARAM)5, 0L);

		SendMessage(hComboYear, CB_ADDSTRING, 1, (LPARAM)"2018");
		SendMessage(hComboYear, CB_ADDSTRING, 1, (LPARAM)"2019");
		SendMessage(hComboYear, CB_ADDSTRING, 1, (LPARAM)"2020");

		SendMessage(hComboYear, CB_SETCURSEL, 0, 0L);

		memdc = CreateCompatibleDC(hdc1);
		hbit = CreateCompatibleBitmap(hdc1, maxX, maxY);
		SelectObject(memdc, hbit);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(memdc, hBrush);
		PatBlt(memdc, 0, 0, maxX, maxY, PATCOPY);
		ReleaseDC(hWnd, hdc1);
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_TAKE:
			date = SendMessage(hComboBox, CB_GETCURSEL, 0, 0L);
			month = SendMessage(hListBox, LB_GETCURSEL, 0, 0L);
			year = SendMessage(hComboYear, CB_GETCURSEL, 0, 0L);
			SendMessage(hComboYear, CB_GETLBTEXT, (WPARAM)year, (LPARAM)Buf1);
			lstrcpy(Buf, ReturnDate(date, month, atoi(Buf1)));
			MessageBox(NULL, Buf, "", MB_OK);
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
LPSTR ReturnDate(int day, int month, int year) {
	char myDay[80] = "", myYear[8] = "";

	_itoa(day + 1, myDay, 10);

	lstrcat(myDay, "-e");

	switch (month + 1) {
	case 1: lstrcat(myDay, " Января "); break;
	case 2: lstrcat(myDay, " февраля "); break;
	case 3: lstrcat(myDay, " Марта "); break;
	case 4: lstrcat(myDay, " Апреля "); break;
	case 5: lstrcat(myDay, " Мая "); break;
	case 6: lstrcat(myDay, " Июня "); break;
	case 7: lstrcat(myDay, " Июля "); break;
	case 8: lstrcat(myDay, " Августа "); break;
	case 9: lstrcat(myDay, " Сентября "); break;
	case 10: lstrcat(myDay, " Октября "); break;
	case 11: lstrcat(myDay, " Ноября "); break;
	case 12: lstrcat(myDay, " Декабря "); break;
	default: lstrcat(myDay, " Июня "); break;
	}

	_itoa(year, myYear, 10);
	lstrcat(myYear, " r. ");

	lstrcat(myDay, myYear);

	return myDay;
}