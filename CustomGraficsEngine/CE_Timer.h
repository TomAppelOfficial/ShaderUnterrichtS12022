#pragma once
#include <Windows.h>

#pragma comment(lib, "Winmm.lib")

class CE_Timer
{
public:
	void Init();
	void Update();

	float DeltaTime() { return deltaTime; }

private:
	float deltaTime = 0.0f;
	float lastTimestamp = 0.0f;
};

