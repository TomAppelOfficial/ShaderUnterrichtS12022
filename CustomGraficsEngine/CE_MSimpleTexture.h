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
	ID3D11Buffer* objBuffer = nullptr;
	struct ObjectBuffer {
		XMFLOAT4X4 worldMatrix;
		XMFLOAT4X4 viewProjectionMatrix;
		XMFLOAT4 worldPositon;
	};

	ID3D11Buffer* sceneBuffer = nullptr;
	struct SceneBuffer {
		XMFLOAT3 cameraPosition;
		float padding;
	};

	ID3D11Buffer* pixelBuffer = nullptr;
	struct MaterialPixelBuffer {
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT3 lightDir;
		float specularStrength;
	};
};

