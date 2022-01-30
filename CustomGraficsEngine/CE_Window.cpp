#include "CE_Window.h"
#include "Keyboard.h"

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

void CE_Window::Init(HINSTANCE _hInstance, int _nShowCmd, INT _xPos, INT _width, INT _yPos, INT _height, LPCWSTR _name)
{
	width = _width;
	height = _height;
	name = _name;

	WNDCLASS wc = {};
	wc.hInstance = _hInstance;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.lpszClassName = name;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;

	if (!RegisterClass(&wc)) ErrorMessage("CE_Window", 1, 20, "Erstellen des WNDCLASS fehlgeschlagen");

	RECT rect = { _xPos, _yPos, width, height };
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&rect, style, false);

	windowHandler = CreateWindow(wc.lpszClassName, 
		wc.lpszClassName, 
		style, rect.left, 
		rect.top, 
		rect.right - rect.left, 
		rect.bottom - rect.top, 
		nullptr, nullptr, 
		_hInstance, nullptr);

	if (!windowHandler) ErrorMessage("CE_Window", 2, 35, "Erstellen des WindowHandlers ist fehlgeschlagen");

	ShowWindow(windowHandler, _nShowCmd);
	SetFocus(windowHandler);
}


bool CE_Window::Run()
{
	MSG msg = {};
	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT) return false;
	}
	return true;
}

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {
	switch (_msg) {
	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(_msg, _wParam, _lParam);
		return 0;
	case WM_KEYDOWN:
		DirectX::Keyboard::ProcessMessage(_msg, _wParam, _lParam);
		if (_wParam == VK_ESCAPE) {
			DestroyWindow(_hWnd);
		}
		return 0;
	case WM_KEYUP:
		DirectX::Keyboard::ProcessMessage(_msg, _wParam, _lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}
