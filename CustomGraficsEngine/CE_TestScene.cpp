#include "CE_TestScene.h"
#include "CE_Core.h"
#include "CE_MSimpleTexture.h"
#include "CE_PMSphere.h"
 

void CE_TestScene::Init()
{
	// Init Meshes
	std::shared_ptr<CE_PMCube> cube = std::make_shared<CE_PMCube>();
	std::shared_ptr<CE_PMSphere> sphereMesh = std::make_shared<CE_PMSphere>();
	cube->Init();
	sphereMesh->Init();

	//shalki
	// Init Materials
	std::shared_ptr<CE_MSimpleTexture> material = std::make_shared<CE_MSimpleTexture>();
	material->Init(L"TestVertexShader.hlsl", L"TestPixelShader.hlsl");
	material->SetSamplerState();
	material->SetTexture(L"brick.png", 0);
	material->SetTexture(L"grass.png", 1);
	material->SetTexture(L"alphaMap.png", 2);

	m_light = std::make_unique<CE_Light>();
	m_light->m_ambientColor = XMFLOAT4(0.1f, 0.1f, 0.1f, 1);
	m_light->m_diffuseColor = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_light->m_specularColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->m_LightDir = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_light->m_specularStrength = 32;

	//// Init Objects
	//std::shared_ptr<CE_Object> cubeObj1 = std::make_shared<CE_Object>();
	//cubeObj1->Init(cube, material);
	//cubeObj1->Transform->SetPosition(5, 0, 0);
	//CORE_OBJECTPOOL->AddObject(cubeObj1);

	// Init Objects
	std::shared_ptr<CE_Object> sphereObj1 = std::make_shared<CE_Object>();
	sphereObj1->Init(sphereMesh, material);
	sphereObj1->Transform->SetPosition(5, 0, 0);
	CORE_OBJECTPOOL->AddObject(sphereObj1);

	std::shared_ptr<CE_Object> cubeObj2 = std::make_shared<CE_Object>();
	cubeObj2->Init(cube, material);

	cubeObj2->Transform->SetPosition(-5, 0, 0);
	CORE_OBJECTPOOL->AddObject(cubeObj2);

	std::shared_ptr<CE_Object> cubeObj3 = std::make_shared<CE_Object>();
	cubeObj3->Init(cube, material);

	cubeObj3->Transform->SetPosition(0, 0, 5);
	CORE_OBJECTPOOL->AddObject(cubeObj3);

	std::shared_ptr<CE_Object> cubeObj4 = std::make_shared<CE_Object>();
	cubeObj4->Init(cube, material);

	cubeObj4->Transform->SetPosition(0, 0, -5);
	CORE_OBJECTPOOL->AddObject(cubeObj4);

	std::shared_ptr<CE_Object> cubeObj5 = std::make_shared<CE_Object>();
	cubeObj5->Init(cube, material);

	cubeObj5->Transform->SetPosition(0, 5, 0);
	CORE_OBJECTPOOL->AddObject(cubeObj5);

	std::shared_ptr<CE_Object> cubeObj6 = std::make_shared<CE_Object>();
	cubeObj6->Init(cube, material);

	cubeObj6->Transform->SetPosition(0, -5, 0);
	CORE_OBJECTPOOL->AddObject(cubeObj6);
}

CE_Light CE_TestScene::GetSceneLight()
{
	return *m_light;

}

void CE_TestScene::SetlightDirection(float x, float y, float z)
{
	m_light->m_LightDir = XMFLOAT3(x, y, z);
}
