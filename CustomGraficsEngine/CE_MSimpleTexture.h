#pragma once
#include "CE_Material.h"

class CE_MSimpleTexture : public CE_Material
{
public:
	virtual void Init(LPCWSTR _vertex, LPCWSTR _pixel) override;
	virtual void Render(CE_Object& _obj, CE_Light& _light) override;
	virtual void DeInit() override;
protected:
	// Constant Buffer
	// https://docs.microsoft.com/de-de/windows/win32/direct3dhlsl/dx-graphics-hlsl-packing-rules?redirectedfrom=MSDN
	ID3D11Buffer* vertexBuffer = nullptr;
	struct MaterialVertexBuffer {

		XMFLOAT4X4 worldPositon;
		XMFLOAT4X4 wvp;
		XMFLOAT3 cameraPosition;
		float padding;
	};

	ID3D11Buffer* pixelBuffer = nullptr;
	struct MaterialPixelBuffer {
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT3 lightDir;
		float padding;
		//float ambStrength;
	};
};

