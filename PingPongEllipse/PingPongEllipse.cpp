#include<Windows.h>
#include<tchar.h>
#include"Resource.h"
#include <math.h>
char szClassName[] = "Name";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG msg;
	hInst = hInstance;
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
	wc.lpszClassName = _T("szClassName");
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);
	hWnd = CreateWindow(_T("szClassName"), _T("szClassName"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!SetTimer(hWnd, 1, 50, NULL))
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, hdcMem;
	HBRUSH hBrush;
	static int xCenter, yCenter, cxClient, cyClient, cxTotal, cyTotal, cxRadius, cyRadius, cxMove, cyMove, xPixel, yPixel;
	static HBITMAP hBitmap;
	int iScale;
	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hWnd);
		xPixel = GetDeviceCaps(hdc, ASPECTX);
		yPixel = GetDeviceCaps(hdc, ASPECTY);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_SIZE:
		xCenter = (cxClient = LOWORD(lParam)) / 2;
		yCenter = (cyClient = HIWORD(lParam)) / 2;
		iScale = min(cxClient * xPixel, cyClient * yPixel) / 16;
		cxRadius = iScale / xPixel;
		cyRadius = iScale / yPixel;
		cxMove = max(1, cxRadius / 2);
		cyMove = max(1, cyRadius / 2);
		cxTotal = 2 * (cxRadius + cxMove);
		cyTotal = 2 * (cyRadius + cyMove);
		if (hBitmap)
			DeleteObject(hBitmap);
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, cxTotal, cyTotal);
		ReleaseDC(hWnd, hdc);
		SelectObject(hdcMem, hBitmap);
		Rectangle(hdcMem, -1, -1, cxTotal + 1, cyTotal + 1);
		hBrush = CreateHatchBrush(HS_DIAGCROSS, 0L);
		SelectObject(hdcMem, hBrush);
		SetBkColor(hdcMem, RGB(255, 0, 255));
		Ellipse(hdcMem, cxMove, cyMove, cxTotal - cxMove, cyTotal - cyMove);
		DeleteDC(hdcMem);
		DeleteObject(hBrush);
		break;
	case WM_TIMER:
		if (!hBitmap)
			break;
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBitmap);
		BitBlt(hdc, xCenter - cxTotal / 2, yCenter - cyTotal / 2, cxTotal, cyTotal, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdc);
		DeleteDC(hdcMem);
		xCenter += cxMove;
		yCenter += cyMove;
		if ((xCenter + cxRadius >= cxClient) || (xCenter - cxRadius < -0))
			cxMove = -cxMove;
		if ((yCenter + cyRadius >= cyClient) || (yCenter - cyRadius < -0))
			cyMove = -cyMove;
		break;


	case WM_DESTROY:
		if (hBitmap)
			DeleteObject(hBitmap);
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}