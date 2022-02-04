#include "CE_Core.h"
#include "CE_MSimpleTexture.h"

void CE_MSimpleTexture::Init(LPCWSTR _vertex, LPCWSTR _pixel)
{
	CE_Material::Init(_vertex, _pixel);

	CreateBuffer(sizeof(ObjectBuffer), &objBuffer);
	CreateBuffer(sizeof(MaterialPixelBuffer), &pixelBuffer);
	CreateBuffer(sizeof(SceneBuffer), &sceneBuffer);
}

void CE_MSimpleTexture::Render(CE_Object& _obj, CE_Light& _light)
{
	CE_Material::Render(_obj, _light);

	ObjectBuffer* obj = {};
	SetVertexBuffer(objBuffer, 0, obj, CORE_DEVICECONTEXT);
	XMFLOAT3 position = _obj.Transform->GetPositon();
	obj->worldPositon = XMFLOAT4(position.x, position.y, position.z, 1.0f);
	XMStoreFloat4x4(&(obj->worldMatrix), XMMatrixTranspose(_obj.Transform->GetWorldMatrix()));
	XMStoreFloat4x4(&(obj->viewProjectionMatrix), XMMatrixTranspose(CORE_MAINCAM->GetViewProjectionMatrix()));

	SceneBuffer* scene = {};
	SetVertexBuffer(sceneBuffer, 1, scene, CORE_DEVICECONTEXT);
	scene->cameraPosition = CORE_MAINCAM->Transform->GetPositon();
	
	MaterialPixelBuffer* pixel = {};
	SetPixelBuffer(pixelBuffer, 0, pixel, CORE_DEVICECONTEXT);
	pixel->ambient = _light.m_ambientColor;
	pixel->diffuse = _light.m_diffuseColor;
	pixel->specular = _light.m_specularColor;
	pixel->lightDir = _light.m_LightDir;
	pixel->specularStrength = _light.m_specularStrength;

	CORE_DEVICECONTEXT->PSSetShaderResources(0, 3, textureSRV);

	CORE_DEVICECONTEXT->PSSetSamplers(0, 1, &samplerState);
}

void CE_MSimpleTexture::DeInit()
{
	CE_Material::DeInit();
}
