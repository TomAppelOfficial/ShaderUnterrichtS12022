#pragma once
#include <iostream>

//#define CheckError(x) if (x != 0) return x
#define CheckError(x) if (x != 0) { AllocConsole(); freopen("CONOUT$", "w", stdout); std::cout << x << "\n"; }
#define CheckErrorMessage(x, message) if (x != 0) { AllocConsole(); freopen("CONOUT$", "w", stdout); std::cout << x << " : " << message <<"\n"; }
#define ErrorMessage(_short, _number,_line , _message) { AllocConsole(); freopen("CONOUT$", "w", stdout); std::cout << "Error: " << _short << ":" << _number << " | Line: " << _line << " Message: " << _message << std::endl; }

//#define CheckFailed(hr, error) if (FAILED(hr)) return error
#define CheckFailed(_hr, _short, _line , _message) if (FAILED(_hr)) { AllocConsole(); freopen("CONOUT$", "w", stdout); std::cout << "Error: " << _short << " | Line: " << _line << " Message: " << _message << std::endl; }

class CE_Error
{
};

