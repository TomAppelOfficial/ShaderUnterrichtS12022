#include "CE_Core.h"
#include "CE_MSimpleTexture.h"

void CE_MSimpleTexture::Init(LPCWSTR _vertex, LPCWSTR _pixel)
{
	CE_Material::Init(_vertex, _pixel);

	CreateBuffer(sizeof(MaterialVertexBuffer), &vertexBuffer);
	CreateBuffer(sizeof(MaterialPixelBuffer), &pixelBuffer);
}

void CE_MSimpleTexture::Render(CE_Object& _obj, CE_Light& _light)
{
	CE_Material::Render(_obj, _light);

	MaterialVertexBuffer* vertex = {};
	//vertex = SetVertexBuffer(vertexBuffer, 0, vertex);
	SetVertexBuffer(vertexBuffer, 0, vertex, CORE_DEVICECONTEXT);
	XMStoreFloat4x4(&(vertex->worldPositon), XMMatrixTranspose(_obj.Transform->GetWorldMatrix()));
	XMStoreFloat4x4(&(vertex->wvp), XMMatrixTranspose(_obj.Transform->GetWorldMatrix() * CORE_MAINCAM->GetViewProjectionMatrix()));
	vertex->cameraPosition = CORE_MAINCAM->Transform->GetPositon();
	
	MaterialPixelBuffer* pixel = {};
	SetPixelBuffer(pixelBuffer, 0, pixel, CORE_DEVICECONTEXT);
	pixel->ambient = _light.m_ambientColor;
	pixel->diffuse = _light.m_diffuseColor;
	pixel->lightDir = _light.m_LightDir;
	//pixel->ambStrength = AmbientStrength;

	CORE_DEVICECONTEXT->PSSetShaderResources(0, 1, &textureSRV);

	CORE_DEVICECONTEXT->PSSetSamplers(0, 1, &samplerState);
}

void CE_MSimpleTexture::DeInit()
{
	CE_Material::DeInit();
}
