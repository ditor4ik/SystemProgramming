
#include<Windows.h>
#include<tchar.h>
#define MAXPOINTS 1000
#define MoveTo(hdc, x,y) MoveToEx(hdc, x,y,NULL)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	static TCHAR szAppName[] = _T("Connect");
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	//Заполняем структуру класса окна

	wndclass.cbSize = sizeof(wndclass);

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_SHIELD);
	wndclass.hCursor = LoadCursor(NULL, IDC_NO);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	//Регистрируем класс окна
	//Создаем основное окно приложения
	hwnd = CreateWindow(szAppName,
		_T("Connect-the-Points Mouse Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	static POINT points[MAXPOINTS];
	static int iCount;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, j;
	switch (iMsg) {
	case WM_LBUTTONDOWN:
		iCount = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON && iCount < 1000)
		{
			points[iCount].x = LOWORD(lParam);
			points[iCount++].y = HIWORD(lParam);
			hdc = GetDC(hwnd);
			SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), 0L);
			ReleaseDC(hwnd, hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetCursor(LoadIcon(NULL, IDC_WAIT));
		ShowCursor(TRUE);
		for (i = 0; i < iCount - 1; i++) {
			for (j = i + 1; j < iCount; j++) {
				MoveTo(hdc, points[i].x, points[i].y);
				LineTo(hdc, points[j].x, points[j].y);
			}
		}
		ShowCursor(FALSE);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default: return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
	return 0;

}