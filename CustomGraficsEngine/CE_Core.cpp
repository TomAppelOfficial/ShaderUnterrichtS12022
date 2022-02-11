#include "CE_Core.h"

CE_Core::CE_Core()
{
}

std::shared_ptr<CE_Core> CE_Core::instance = nullptr;
/// <summary>
/// Instance ist ein Singleton der CE_Core Klasse. Wenn noch keine Instance besteht wird eine neue erstellt
/// </summary>
/// <returns>Git ein Shared-Pointer vom Type CE_Core zurück</returns>
std::shared_ptr<CE_Core> CE_Core::Instance()
{
	if (instance == nullptr) {
		instance = std::make_shared<CE_Core>();
	}
	return instance;
}

int CE_Core::Init(HINSTANCE _hInstance, HINSTANCE __hPrevInstance, LPSTR _lpCmdLine, int nShowCmd)
{
	keyboard = std::make_unique<Keyboard>();

	// Init Window
	window = std::make_unique<CE_Window>();
	window->Init(_hInstance, nShowCmd, 50, width, 50, height, L"Custom Grafic Engine");
	
	// Init Renderer
	renderer = std::make_unique<CE_Renderer>();
	renderer->Init(window->GetWindowHandler(), width, height, true);

	// Init Timer
	timer = std::make_unique<CE_Timer>();
	timer->Init();

	// Init Main Camera
	mainCamera = std::make_shared<CE_Camera>();
	mainCamera->Init(width, height);
	mainCamera->Transform->SetPosition(0, 0, -4);

	// Init ObjectPool
	objectPool = std::make_shared<CE_ObjectPool>();


	testScene = std::make_unique<CE_TestScene>();
	testScene->Init();

	return 0;
}

void CE_Core::Run()
{
	isRunning = true;
	while (isRunning) {
		if (!window->Run())
			break;

		timer->Update();

		Update();
		Render();
	}
}

void CE_Core::Finish()
{
	renderer->DeInit();
	
}

void CE_Core::Update()
{
	mainCamera->Update();

	objectPool->Update();
}

void CE_Core::Render()
{
	renderer->BeginScene(0, 0, 0);

	m_step = m_step + timer->DeltaTime();

	if (m_step > XM_2PI) {
		m_step = 0;
	}

	testScene->SetlightDirection(cos(m_step),0, sin(m_step));
	objectPool->Render(testScene->GetSceneLight());

	renderer->EndScene();
}
