#pragma once
#include <memory>
#include <Windows.h>
#include "Keyboard.h"

#include "CE_Error.h"
#include "CE_Window.h"
#include "CE_Renderer.h"
#include "CE_Camera.h"
#include "CE_Timer.h"


#include "CE_ObjectPool.h"
#include "CE_Scence.h"
#include "CE_TestScene.h"

#define CORE CE_Core::Instance()
#define CORE_DEVICE CE_Core::Instance()->GetDevice()
#define CORE_DEVICECONTEXT CE_Core::Instance()->GetDeviceContext()
#define CORE_MAINCAM CE_Core::Instance()->GetMainCamera()
#define CORE_OBJECTPOOL CE_Core::Instance()->GetObjectPool()
#define CORE_DELTA_TIME CE_Core::Instance()->GetDeltaTime()

class CE_Core
{
public:
	CE_Core();
	static std::shared_ptr<CE_Core> Instance();

	int Init(HINSTANCE _hInstance, HINSTANCE __hPrevInstance, LPSTR _lpCmdLine, int nShowCmd);

	void Run();
	void Finish();

	inline ID3D11Device* GetDevice() { return renderer->D3DDevice(); }
	inline ID3D11DeviceContext* GetDeviceContext() { return renderer->D3DDeviceContext(); }
	inline const std::shared_ptr<CE_Camera> GetMainCamera() { return mainCamera; }
	inline const std::shared_ptr<CE_ObjectPool> GetObjectPool() { return objectPool; }
	inline const float GetDeltaTime() { return timer->DeltaTime();  }
private:
	static std::shared_ptr<CE_Core> instance;

	std::shared_ptr<CE_Window> window;
	std::shared_ptr<CE_Renderer> renderer;

	std::shared_ptr<CE_Camera> mainCamera;
	std::unique_ptr<CE_Timer> timer;
	std::shared_ptr<CE_ObjectPool> objectPool;

	std::unique_ptr<CE_TestScene> testScene;
	std::unique_ptr<Keyboard> keyboard;

	void Update();
	void Render();

	bool isRunning = false;

	INT width = 1920;
	INT height = 1080;

	float m_step = 0;
};

