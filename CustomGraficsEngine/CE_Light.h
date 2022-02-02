#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class CE_Light
{
public:
	CE_Light();
	XMFLOAT4 m_diffuseColor;
	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_specularColor;
	XMFLOAT3 m_LightDir;
	float m_specularStrength;
};

