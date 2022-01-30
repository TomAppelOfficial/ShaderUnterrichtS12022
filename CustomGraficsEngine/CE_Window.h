#pragma once
#include <Windows.h>

#include "CE_Error.h"

class CE_Window
{
public:
	void Init(HINSTANCE _hInstance, int _nShowCmd, INT _xPos, INT _width, INT _yPos, INT _height, LPCWSTR _name);
	
	inline INT Width() { return width; }
	inline INT Height() { return height; }

	bool Run();

	HWND GetWindowHandler() { return windowHandler; }

private:
	INT width;
	INT height;

	LPCWSTR name;

	HWND windowHandler = NULL;
};

