#include<Windows.h>
#include<string.h>
#include<tchar.h>
#include "sysmets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("MyClass");
	MSG msg;
	WNDCLASSEX wc;
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
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(szClassName, _T("A Hello1 Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
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
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxChar, cxCaps, cyChar, cyClient, iVscrollPos;
	TCHAR szBuffer[10];
	TEXTMETRIC tm;
	int i, y;
	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hWnd);
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hWnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 0, 0, _T("Размер графических элементов Windows (Авдюнин Дмитрий)"), 55);
		for (i = 0; i < NUMLINES; i++)
		{
			TextOut(hdc, cxChar, cyChar * (1 + i), sysmetrics[i].szLabel, _tcslen(sysmetrics[i].szLabel));
			TextOut(hdc, cxChar + 22 * cxCaps, cyChar * (1 + i), sysmetrics[i].szDesc, _tcslen(sysmetrics[i].szDesc));
			SetTextAlign(hdc, TA_RIGHT | TA_TOP);
			TextOut(hdc, cxChar + 22 * cxCaps + 40 * cxChar, cyChar * (1 + i), szBuffer, wsprintf(szBuffer, _T("%d"), GetSystemMetrics(sysmetrics[i].iIndex)));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
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