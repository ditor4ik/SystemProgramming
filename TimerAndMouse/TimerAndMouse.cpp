#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<xstring>
typedef std::basic_string < TCHAR, std::char_traits<TCHAR>, std::allocator < TCHAR>> String;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
TCHAR r_str[] = _T("Нажата правая кнопка мыши");
TCHAR l_str[] = _T("Нажата левая кнопка мыши");


//==================================================================================
int WINAPI WinMain(HINSTANCE This, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
	wc.hInstance = This;
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
	hMainWnd = CreateWindow(szClassName, _T("Massage"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		This, NULL);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT massage, WPARAM wParam,

	LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	int x, y;
	static int t;
	static String str;
	TCHAR s[10], str1[20] = _T("Секунды: ");
	switch (massage) {

	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	case WM_TIMER:
		t++;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hDC = GetDC(hWnd);
		TextOut(hDC, x, y, r_str, _tcsclen(r_str));
		ReleaseDC(hWnd, hDC);
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hDC = GetDC(hWnd);
		TextOut(hDC, x, y, l_str, _tcsclen(l_str));
		ReleaseDC(hWnd, hDC);
		break;
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		str += (TCHAR)wParam;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		_tcscat(str1 + 9, _itot(t, s, 10));
		TextOut(hDC, 0, 0, str1, _tcsclen(str1));
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, massage, wParam, lParam);
	}
	return 0;

}