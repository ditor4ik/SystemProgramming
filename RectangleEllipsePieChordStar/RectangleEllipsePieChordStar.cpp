#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>
POINT pt[6] = { {550,150}, {575,190}, {500,175}, {600,165}, {525,190},{550,150} };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//TCHAR text[] = _T("Текст для вывода в окне");
TCHAR szClassName[] = _T("MyClass");
HPEN hRedPen, hGreenPen, hBluePen, hPurplePen;
HBRUSH hYellowBrush, hGreenBrush, hBlueBrush, hPurpleBrush;
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
	TCHAR szText1[] = _T("Rectangle( )");
	TCHAR szText2[] = _T("Ellipse( )");
	TCHAR szText3[] = _T("Pie( )");
	TCHAR szText4[] = _T("Chord( )");
	TCHAR szText5[] = _T("Star(Авдюнин)");
	switch (uMsg) {
	case WM_CREATE:
		hRedPen = CreatePen(PS_SOLID, 4, RGB(150, 0, 0));
		hGreenPen = CreatePen(PS_SOLID, 10, RGB(0, 150, 0));
		hBluePen = CreatePen(PS_SOLID, 20, RGB(0, 0, 150));
		hPurplePen = CreatePen(PS_SOLID, 20, RGB(190, 87, 255));
		hYellowBrush = CreateSolidBrush(RGB(255, 120, 120));
		hGreenBrush = CreateSolidBrush(RGB(120, 255, 120));
		hBlueBrush = CreateSolidBrush(RGB(120, 120, 255));
		hPurpleBrush = CreateSolidBrush(RGB(89, 255, 156));
		break;


	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		SetBkColor(hdc, RGB(200, 200, 100)); // NenTeii Gon

		SetTextColor(hdc, RGB(0, 0, 200)); // Cunui upnor

		TextOut(hdc, 25, 5, szText1, _tcsclen(szText1));
		TextOut(hdc, 155, 5, szText2, _tcsclen(szText2));
		TextOut(hdc, 280, 5, szText3, _tcsclen(szText3));
		TextOut(hdc, 395, 5, szText4, _tcsclen(szText4));
		TextOut(hdc, 525, 5, szText5, _tcsclen(szText5));

		Rectangle(hdc, 10, 40, 110, 140);
		SelectPen(hdc, hRedPen);
		SelectBrush(hdc, hYellowBrush);
		Ellipse(hdc, 130, 40, 230, 140);
		SelectPen(hdc, hGreenPen);
		SelectBrush(hdc, hGreenBrush);
		Pie(hdc, 250, 40, 350, 140, 350, 140, 250, 140);
		SelectPen(hdc, hBluePen);
		SelectBrush(hdc, hBlueBrush);
		Chord(hdc, 370, 40, 470, 140, 470, 125, 370, 125);
		Polyline(hdc, pt, 6);
		BeginPath(hdc);
		SelectPen(hdc, hRedPen);
		Polyline(hdc, pt, 6);

		CloseFigure(hdc);
		EndPath(hdc);
		Polyline(hdc, pt, 6);
		SelectPen(hdc, hPurplePen);
		SelectBrush(hdc, hGreenBrush);
		//SelectObject(hdc, hGreenBrush);
		SetPolyFillMode(hdc, WINDING);
		FillPath(hdc);


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