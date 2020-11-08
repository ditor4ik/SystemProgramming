#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR str[] = _T("наклонный текст");
TCHAR szClassName[] = _T("MainFrame");
//==================================================================================
int APIENTRY WinMain(HINSTANCE This,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	TCHAR szTitle[] = _T("Фигуры");
	MSG msg;
	WNDCLASS wc;
	//Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = This;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	//Регистрируем класс окна
	if (!RegisterClass(&wc)) return 0;

	//Создаем основное окно приложения
	HWND hwnd = CreateWindow(szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hwnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	HFONT oldFont, newFont;
	int Escapement;
	static int sx, sy;
	switch (uMsg) {
	case WM_SIZE:
		sx = LOWORD(lParam) / 2;
		sy = HIWORD(lParam) / 2;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (Escapement = 0; Escapement < 3600; Escapement += 200)
		{
			newFont = CreateFont(25, 20, Escapement, 0, 0, 0, 1, 0,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Times New Roman"));

			oldFont = (HFONT)SelectObject(hdc, newFont);
			TextOut(hdc, sx, sy, str, _tcsclen(str));
			SelectObject(hdc, oldFont);
			DeleteObject(newFont);
		}
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