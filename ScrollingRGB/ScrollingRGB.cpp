#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include <stdlib.h>

LRESULT CALLBACK ScrollProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
WNDPROC fnOldScr[3];
HWND hwndScrol[3], hwndLabel[3], hwndValue[3], hwndRect;
int color[3], iFocus;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	static TCHAR szAppName[] = _T("Colors1");
	static LPCWSTR szColorLabel[] = { _T("Red"), _T("Green"), _T("Blue") };
	HWND hWnd;
	WNDCLASSEX wc;
	int i;
	MSG msg;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(0L);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return FALSE;

	hWnd = CreateWindow(szAppName, _T("Color Scroll"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);
	if (!hWnd) return FALSE;
	hwndRect = CreateWindow(_T("static"), NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT, 0, 0, 0, 0, hWnd, (HMENU)9, hInstance, NULL);
	for (i = 0; i < 3; i++)
	{
		hwndScrol[i] = CreateWindow(_T("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT, 0, 0, 0, 0, hWnd, (HMENU)i, hInstance, NULL);
		hwndLabel[i] = CreateWindow(_T("static"), szColorLabel[i], WS_CHILD | WS_VISIBLE | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)(i + 3), hInstance, NULL);
		hwndValue[i] = CreateWindow(_T("static"), _T("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)(i + 6), hInstance, NULL);
		fnOldScr[i] = (WNDPROC)SetWindowLong(hwndScrol[i], GWL_WNDPROC, (LONG)ScrollProc);
		SetScrollRange(hwndScrol[i], SB_CTL, 0, 255, FALSE);
		SetScrollPos(hwndScrol[i], SB_CTL, 0, FALSE);
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static COLORREF crPrim[3] = { RGB(255,0,0), RGB(0,255,0), RGB(0,0,255) };
	static HBRUSH hBrush[3], hBrushStatic;
	static int cyChar;
	static TCHAR szbuffer[10];
	int i, cx, cy;
	RECT rcColor;
	switch (uMsg) {
	case WM_CREATE:
		for (i = 0; i < 3; i++)
		{
			hBrush[i] = CreateSolidBrush(crPrim[i]);
		}
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		cyChar = HIWORD(GetDialogBaseUnits());
		break;
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		SetRect(&rcColor, cx / 2, 0, cx, cy);
		MoveWindow(hwndRect, 0, 0, cx / 2, cy, TRUE);
		for (i = 0; i < 3; i++)
		{
			MoveWindow(hwndScrol[i], (2 * i + 1) * cx / 14, 2 * cyChar, cx / 14, cy - 4 * cyChar, TRUE);
			MoveWindow(hwndLabel[i], (4 * i + 1) * cx / 28, cyChar / 2, cx / 7, cyChar, TRUE);
			MoveWindow(hwndValue[i], (4 * i + 1) * cx / 28, cy - 3 * cyChar / 2, cx / 7, cyChar, TRUE);
		}
		SetFocus(hWnd);
		break;
	case WM_SETFOCUS:
		SetFocus(hwndScrol[iFocus]);
		break;
	case WM_VSCROLL:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		switch (LOWORD(wParam))
		{
		case SB_PAGEDOWN:
			color[i] += 15;
		case SB_LINEDOWN:
			color[i] = min(255, color[i] - 1);
			break;
		case SB_PAGEUP:
			color[i] -= 15;
			break;
		case SB_TOP:
			color[i] = 0;
			break;
		case SB_BOTTOM:
			color[i] = 255;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			color[i] = HIWORD(wParam);
			break;
		default:
			break;
		}
		SetScrollPos(hwndScrol[i], SB_CTL, color[i], TRUE);
		SetWindowText(hwndValue[i], _itot(color[i], szbuffer, 10));
		DeleteObject((HBRUSH)SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(color[0], color[1], color[2]))));
		InvalidateRect(hWnd, &rcColor, TRUE);
		break;
	case WM_CTLCOLORSCROLLBAR:
		i =
			GetWindowLong((HWND)lParam, GWL_ID);
		return (LRESULT)hBrush[i];
	case WM_CTLCOLORSTATIC:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		if (i >= 3 or i <= 8)
		{
			SetTextColor((HDC)wParam, crPrim[i %

				3]);
			SetBkColor((HDC)wParam, GetSysColor(COLOR_BTNHIGHLIGHT));
			return (LRESULT)hBrushStatic;
		}
		break;
	case WM_SYSCOLORCHANGE:
		DeleteObject(hBrushStatic);
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ScrollProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int i = GetWindowLong(hWnd, GWL_ID);
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
		{
			SetFocus(hwndScrol[(i + (GetKeyState(VK_SHIFT) < 0 ? 2 : 1)) % 3]);
		}
		break;
	case WM_SETFOCUS:
		iFocus = i;
		break;
	}
	return CallWindowProc(fnOldScr[i], hWnd, msg, wParam, lParam);
}