#include<Windows.h>
#include<tchar.h>
#include<cmath>
double TWO_PI = (2.0 * 3.14159);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//==================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	TCHAR szClassName[] = _T("MyClass");
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
	RegisterClassEx(&wc);
	hwnd = CreateWindow(szClassName, _T("SHIZIK"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//Показываем окно
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static int iEnd[] = { PS_ENDCAP_ROUND, PS_ENDCAP_SQUARE,
	PS_ENDCAP_FLAT };
	static int iJoin[] = { PS_JOIN_ROUND, PS_JOIN_BEVEL,
	PS_JOIN_MITER };
	HDC hdc;
	PAINTSTRUCT ps;
	static int sx, sy;
	LOGBRUSH lb;
	int i;
	switch (uMsg) {
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 100, 100, NULL);
		SetViewportExtEx(hdc, sx, sy, NULL);
		lb.lbStyle = BS_SOLID;
		lb.lbColor = RGB(128, 128, 128);
		lb.lbHatch = 0;
		for (i = 0; i < 3; i++)
		{
			SelectObject(hdc,
				ExtCreatePen(PS_SOLID | PS_GEOMETRIC |
					iEnd[i] | iJoin[i], 10,
					&lb, 0, NULL));
			BeginPath(hdc);
			MoveToEx(hdc, 10 + 30 * i, 25, NULL);
			LineTo(hdc, 20 + 30 * i, 75);
			LineTo(hdc, 30 + 30 * i, 25);
			EndPath(hdc);
			StrokePath(hdc);
			DeleteObject(
				SelectObject(hdc,
					GetStockObject(BLACK_PEN)));
			MoveToEx(hdc, 10 + 30 * i, 25, NULL);
			LineTo(hdc, 20 + 30 * i, 75);
			LineTo(hdc, 30 + 30 * i, 25);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}