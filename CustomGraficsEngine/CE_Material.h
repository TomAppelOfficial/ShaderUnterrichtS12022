#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "CE_Error.h"
#include "WICTextureLoader.h"
#include "CE_Light.h"
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class CE_Object;
class CE_Material
{
public:
	virtual void Init(LPCWSTR _vertex, LPCWSTR _pixel);
	virtual void Render(CE_Object& _obj, CE_Light& _light);
	virtual void DeInit();

	void SetSamplerState();

	void SetTexture(LPCWSTR _name);


	//Variablen vom Material
	XMFLOAT3 Ambient = XMFLOAT3(1.0f, 1.0f, 1.0f);
	float AmbientStrength = 0.5f;

protected:
	void createVertexShader(LPCWSTR _name);
	void createPixelShader(LPCWSTR _name);
	void createInputLayout(ID3DBlob* _blob);

	// Create Constant Buffer
	//void createMatVBuffer();
	//void createMatPBuffer();
	 
	void CreateBuffer(UINT _size, ID3D11Buffer** _buffer);
	template<typename T>
	//T* SetVertexBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T* _bufferStruct);
	void SetVertexBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T &_bufferStruct, ID3D11DeviceContext* _context);
	template<typename T>
	//T* SetPixelBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T* _bufferStruct);
	void SetPixelBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T &_bufferStruct, ID3D11DeviceContext* _context);
	//void SetPixelBuffer(ID3D11Buffer* _buffer);

	// Set Constant Buffer
	//void setMatVBuffer(XMMATRIX _worldPosition);
	//void setMatPBuffer();

	//Input Layout
	ID3D11InputLayout* inputLayout;
	//Shader
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;

	//Texture Ressource
	ID3D11Resource* texture = nullptr;
	ID3D11ShaderResourceView* textureSRV = nullptr;

	//Samplers
	ID3D11SamplerState* samplerState;
};
#pragma region Implemention

//Funktion werden hier definiert das sie schon bekannt sind bevor die cpp kompeliert worden ist wegen dem template

template<typename T>
//T* CE_Material::SetVertexBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T* _bufferStruct)
inline void CE_Material::SetVertexBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T& _bufferStruct, ID3D11DeviceContext* _context)
{
	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = _context->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	CheckFailed(hr, "CE_Material", __LINE__, "Map Vertex Buffer Failed");

	_bufferStruct = reinterpret_cast<T>(data.pData);

	_context->Unmap(_buffer, 0);
	_context->VSSetConstantBuffers(_bufferSlot, 1, &_buffer);
	//return _bufferStruct;
}

template<typename T>
//T* CE_Material::SetPixelBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T* _bufferStruct)
inline void CE_Material::SetPixelBuffer(ID3D11Buffer* _buffer, UINT _bufferSlot, T& _bufferStruct, ID3D11DeviceContext* _context)
{
	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = _context->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	CheckFailed(hr, "CE_Material", __LINE__, "Map Pixel Buffer Failed");

	_bufferStruct = reinterpret_cast<T>(data.pData);

	_context->Unmap(_buffer, 0);
	_context->PSSetConstantBuffers(_bufferSlot, 1, &_buffer);
	//return _bufferStruct;
}

#pragma endregion