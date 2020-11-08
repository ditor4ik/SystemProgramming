#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR text[] = _T("Текст для вывода в окне");
TCHAR szClassName[] = _T("MyClass");
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
	TEXTMETRIC tm;
	TCHAR str[256];
	RECT rt;
	SIZE size;
	switch (uMsg) {


	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		SetBkColor(hdc, RGB(255, 255, 0)); // NenTeii Gon

		SetTextColor(hdc, RGB(0, 0, 128)); // Cunui upnor

		TextOut(hdc, 0, 0, text, _tcsclen(text));

		SetBkMode(hdc, TRANSPARENT); // Npospaursih gon

		SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));

		GetTextMetrics(hdc, &tm);

		_stprintf(str, _T("tmHeignt = %d\ntmInternalLeading=%d\ntmExternalLeading = %d\ntmAscent = % d\ntmDescent = % d\n"), tm.tmHeight, tm.tmInternalLeading, tm.tmExternalLeading, tm.tmAscent, tm.tmDescent);
		SetRect(&rt, 0, 20, 150, 100);

		DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT);

		GetTextExtentPoint32(hdc, text, _tcsclen(text), &size);

		_stprintf(str, _T("Ширина строки = %d\nВысота строки = %d"), size.cx, size.cy);

		SetRect(&rt, 0, 100, 158, 150);

		DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT);

		SelectObject(hdc, GetStockObject(DEVICE_DEFAULT_FONT));
		SetBkMode(hdc, OPAQUE);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 0, 140, _T("Авдюнин Дмитрий DEVICE_DEFAULT_FONT"), 34);

		SelectObject(hdc, GetStockObject(ANSI_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 0, 165, _T("Авдюнин Дмитрий ANSI_FIXED_FONT"), 30);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, OPAQUE);
		SetTextColor(hdc, RGB(0, 0, 255));
		SetBkColor(hdc, RGB(0, 255, 255));
		TextOut(hdc, 0, 180, _T("Авдюнин Дмитрий DEFAULT_GUI_FONT"), 32);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, OPAQUE);
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 0, 195, _T("Авдюнин Дмитрий SYSTEM_FIXED_FONT"), 32);

		SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 0, 255));
		SetBkColor(hdc, RGB(255, 0, 255));
		TextOut(hdc, 0, 210, _T("Авдюнин Дмитрий ANSI_VAR_FONT"), 28);

		SelectObject(hdc, GetStockObject(SYSTEM_FONT));
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(255, 0, 0));
		TextOut(hdc, 0, 250, _T("Авдюнин Дмитрий SYSTEM_FONT"), 34);

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