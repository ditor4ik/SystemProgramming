#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<windowsx.h>
#define MI_FULL 100
#define MI_HALF 101

HBRUSH hBlueBrush, hYellowBrush;
int sw;
HPEN hpen;
MSG msg;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("menudemo");
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = _T("menudemo");
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(szClassName, _T("menudemo"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	ShowWindow(hMainWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Луна");
	TCHAR str1[] = _T("Полная");
	TCHAR str2[] = _T("Убывающая");
	static int sx, sy;
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MI_HALF:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_FULL:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_CREATE:
		hBlueBrush = CreateSolidBrush(RGB(50, 50, 255));
		hYellowBrush = CreateSolidBrush(RGB(255, 211, 0));
		hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, MI_FULL, str1);
		AppendMenu(hPopupMenu, MF_STRING, MI_HALF, str2);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hWnd, hMenu);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		FillRect(hdc, &ps.rcPaint, hBlueBrush);
		SelectBrush(hdc, hYellowBrush);
		if (sw == 1 or sw == 2)
		{
			Ellipse(hdc, sx / 2 - 200, sy / 2 - 200, sx / 2 + 200, sy / 2 + 200);
			if (sw == 1) {
				SelectBrush(hdc, hBlueBrush);
				SelectPen(hdc, hpen);
				Ellipse(hdc, sx / 2 - 70, sy / 2 - 190, sx / 2 + 470, sy / 2 + 190);
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hYellowBrush);
		DeleteObject(hBlueBrush);
		DeleteObject(hpen);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}