#include "CE_Core.h"
#include "CE_Material.h"

void CE_Material::Init(LPCWSTR _vertex, LPCWSTR _pixel)
{
	createVertexShader(_vertex);
	createPixelShader(_pixel);

	//CreateBuffer(sizeof(ObjectBuffer), &objBuffer);
	//CreateBuffer(sizeof(MaterialPixelBuffer), &pixelBuffer);
	//createMatVBuffer();
	//createMatPBuffer();
}

void CE_Material::Render(CE_Object& _obj, CE_Light& _light)
{
	//Set Shader Stuff
	CORE_DEVICECONTEXT->IASetInputLayout(inputLayout);
	CORE_DEVICECONTEXT->VSSetShader(vertexShader, nullptr, 0);
	CORE_DEVICECONTEXT->PSSetShader(pixelShader, nullptr, 0);

	//ObjectBuffer* vertex = {};
	////vertex = SetVertexBuffer(objBuffer, 0, vertex);
	//SetVertexBuffer(objBuffer, 0, vertex);
	//XMStoreFloat4x4(&(vertex->worldPositon), XMMatrixTranspose(_worldPos));
	//XMStoreFloat4x4(&(vertex->wvp), XMMatrixTranspose(_worldPos * CORE_MAINCAM->GetViewProjectionMatrix()));
	//vertex->cameraPosition = CORE_MAINCAM->Transform->GetPositon();

	//MaterialPixelBuffer* pixel = {};
	//SetPixelBuffer(pixelBuffer, 0, pixel);
	//pixel->ambient = Ambient;
	//pixel->ambStrength = AmbientStrength;

	//setMatVBuffer(_worldPos);
	//setMatPBuffer();

	//Load Texture Stuff
	//CORE_DEVICECONTEXT->PSSetShaderResources(0, 1, &textureSRV);

	//CORE_DEVICECONTEXT->PSSetSamplers(0, 1, &samplerState);
}

void CE_Material::DeInit()
{
	//Release Shader Stuff
	if (vertexShader != nullptr) {
		vertexShader->Release();
		vertexShader = nullptr;
	}

	if (pixelShader != nullptr) {
		pixelShader->Release();
		pixelShader = nullptr;
	}

	if (inputLayout != nullptr) {
		inputLayout->Release();
		inputLayout = nullptr;
	}

	//Release Texture Stuff
	if (texture != nullptr) {
		texture->Release();
		texture = nullptr;
	}

	if (textureSRV != nullptr) {
		delete textureSRV;
	}

	//Release Samplerstate
	if (samplerState != nullptr) {
		samplerState->Release();
		samplerState = nullptr;
	}
}

void CE_Material::SetSamplerState()
{
	D3D11_SAMPLER_DESC sampdesc;
	ZeroMemory(&sampdesc, sizeof(sampdesc));
	sampdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	HRESULT hr = CORE_DEVICE->CreateSamplerState(&sampdesc, &samplerState);
	CheckFailed(hr, "CE_Material", __LINE__, "Create Sampler State Failed");
}

void CE_Material::SetTexture(LPCWSTR _name, int _index)
{
	HRESULT hr = CreateWICTextureFromFile(CORE_DEVICE, _name, &texture, &textureSRV[_index]);
	CheckFailed(hr, "CE_Material", __LINE__, "Create WIC Texture From File Failed");
}

void CE_Material::createVertexShader(LPCWSTR _name)
{
	int flags = 0;
#ifdef NDEBUG
#else
	flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* compiledCode = nullptr;
	HRESULT hr = D3DCompileFromFile(
		_name, // shader Filename
		nullptr, nullptr, // optional macros & includes
		"main", // entry point function
		"vs_4_0", // shader type & version
		flags, 0, //optional Flags
		&compiledCode, // compiled blob target
		nullptr // optional blob for all compile errors
	);
	CheckFailed(hr, "CE_Material", __LINE__, "Compile Vertex Shader Failed");
	
	hr = CORE_DEVICE->CreateVertexShader(compiledCode->GetBufferPointer(), compiledCode->GetBufferSize(), nullptr, &vertexShader);
	CheckFailed(hr, "CE_Material", __LINE__, "Create Vertex Shader Failed");

	createInputLayout(compiledCode);
	compiledCode->Release();
	compiledCode = nullptr;
}

void CE_Material::createPixelShader(LPCWSTR _name)
{
	int flags = 0;
#ifdef NDEBUG
#else
	flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	ID3DBlob* compiledCode = nullptr;
	HRESULT hr = D3DCompileFromFile(
		_name,
		nullptr, nullptr,
		"main",
		"ps_4_0",
		flags, 0,
		&compiledCode,
		nullptr
	);
	CheckFailed(hr, "CE_Material", __LINE__, "Compile Pixel Shader Failed");

	hr = CORE_DEVICE->CreatePixelShader(compiledCode->GetBufferPointer(), compiledCode->GetBufferSize(), nullptr, &pixelShader);
	CheckFailed(hr, "CE_Material", __LINE__, "Create Pixel Shader Failed");
}

void CE_Material::createInputLayout(ID3DBlob* _blob)
{
	D3D11_INPUT_ELEMENT_DESC elements[5] = {};

	elements[0].SemanticName = "Position";
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	elements[1].SemanticName = "NORMAL";
	elements[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elements[2].SemanticName = "TEXCOORD";
	elements[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	elements[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elements[3].SemanticName = "TANGENT";
	elements[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elements[4].SemanticName = "BINORMAL";
	elements[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = CORE_DEVICE->CreateInputLayout(elements, 5, _blob->GetBufferPointer(), _blob->GetBufferSize(), &inputLayout);
	CheckFailed(hr, "CE_Material", __LINE__, "Create InputLayout Failed");
}

//void CE_Material::createMatVBuffer()
//{
//	D3D11_BUFFER_DESC desc = {};
//	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	desc.ByteWidth = sizeof(ObjectBuffer);
//	//desc.ByteWidth = static_cast<UINT>(sizeof(ObjectBuffer) + (16 - sizeof(ObjectBuffer) % 16));
//	desc.Usage = D3D11_USAGE_DYNAMIC;
//	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//
//	HRESULT hr = CORE_DEVICE->CreateBuffer(&desc, nullptr, &objBuffer);
//	CheckFailed(hr, "CE_Material", 146, "Create Vertex Buffer failed");
//}
//
//void CE_Material::createMatPBuffer()
//{
//	D3D11_BUFFER_DESC desc = {};
//	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	desc.ByteWidth = sizeof(MaterialPixelBuffer);
//	desc.Usage = D3D11_USAGE_DYNAMIC;
//	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//
//	HRESULT hr = CORE_DEVICE->CreateBuffer(&desc, nullptr, &pixelBuffer);
//	CheckFailed(hr, "CE_Material", 159, "Create Material Pixel Buffer failed")
//}

void CE_Material::CreateBuffer(UINT _size, ID3D11Buffer** _buffer)
{
	D3D11_BUFFER_DESC desc = {};
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = _size;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = CORE_DEVICE->CreateBuffer(&desc, nullptr, _buffer);
	CheckFailed(hr, "CE_Material", __LINE__, "Create Buffer failed")
}

//void CE_Material::setMatVBuffer(XMMATRIX _worldPosition)
//{
//	D3D11_MAPPED_SUBRESOURCE data = {};
//	HRESULT hr = CORE_DEVICECONTEXT->Map(objBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
//	CheckFailed(hr, "CE_Material", 166, "Map Material Vertex Buffer Failed");
//
//	ObjectBuffer* buffer = reinterpret_cast<ObjectBuffer*>(data.pData);
//	//TODO: Hier kommt Stuff rein
//	XMStoreFloat4x4(&(buffer->worldPositon), XMMatrixTranspose(_worldPosition));
//	XMStoreFloat4x4(&(buffer->wvp), XMMatrixTranspose(_worldPosition * CORE_MAINCAM->GetViewProjectionMatrix()));
//	buffer->cameraPosition = CORE_MAINCAM->Transform->GetPositon();
//
//	CORE_DEVICECONTEXT->Unmap(objBuffer, 0);
//	CORE_DEVICECONTEXT->VSSetConstantBuffers(0, 1, &objBuffer);
//}
//
//void CE_Material::setMatPBuffer()
//{
//	D3D11_MAPPED_SUBRESOURCE data = {};
//	HRESULT hr = CORE_DEVICECONTEXT->Map(pixelBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
//	CheckFailed(hr, "CE_Material", 179, "Map Material Pixel Buffer Failed");
//
//	MaterialPixelBuffer* buffer = reinterpret_cast<MaterialPixelBuffer*>(data.pData);
//	//TODO: Hier kommt Stuff rein
//	buffer->ambient = Ambient;
//	buffer->ambStrength = AmbientStrength;
//
//	CORE_DEVICECONTEXT->Unmap(pixelBuffer, 0);
//	CORE_DEVICECONTEXT->PSSetConstantBuffers(0, 1, &pixelBuffer);
//}