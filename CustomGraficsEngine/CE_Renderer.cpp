#include "CE_Renderer.h"

void CE_Renderer::Init(HWND _hwnd, INT _width, INT _height, bool _isWindowed)
{
	// https://docs.microsoft.com/de-de/windows/win32/api/dxgi/ns-dxgi-dxgi_swap_chain_desc
	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.OutputWindow = _hwnd;
	desc.BufferCount = 1;
	desc.BufferDesc.Width = _width;
	desc.BufferDesc.Height = _height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 1;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Windowed = _isWindowed;

	//Für Shaderlevel 4.0
	D3D_FEATURE_LEVEL supportedLevels[] = { D3D_FEATURE_LEVEL_10_0 };
	//Für Shaderlevel 5.0
	//D3D_FEATURE_LEVEL supportedLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, //graphic adapter
		D3D_DRIVER_TYPE_HARDWARE, //driver type, hardware or software rendering?
		nullptr, // reference to software module if driver type is software
		0, // optional flags
		supportedLevels, 1, // supported direct 3d versions
		D3D11_SDK_VERSION, // api version the application was build with
		&desc, &d3dSwapChain, &d3dDevice,
		nullptr, // optional chosen feature level
		&d3dDeviceContext
	);

	CheckFailed(hr, "CE_Renderer", __LINE__, "Fail to Create the Device and Swap Chand");

	ID3D11Texture2D* backBuffer = nullptr;
	hr = d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	CheckFailed(hr, "CE_Renderer", __LINE__, "Fail to create the Backbuffer");

	hr = d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
	CheckFailed(hr, "CE_Renderer", __LINE__, "Fail to create the TargetView");

	backBuffer->Release();
	backBuffer = nullptr;

	D3D11_TEXTURE2D_DESC depthStencilTXTDesc;
	depthStencilTXTDesc.Width = _width;
	depthStencilTXTDesc.Height = _height;
	depthStencilTXTDesc.MipLevels = 1;
	depthStencilTXTDesc.ArraySize = 1;
	depthStencilTXTDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTXTDesc.SampleDesc.Count = 1;
	depthStencilTXTDesc.SampleDesc.Quality = 0;
	depthStencilTXTDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilTXTDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilTXTDesc.CPUAccessFlags = 0;
	depthStencilTXTDesc.MiscFlags = 0;

	hr = d3dDevice->CreateTexture2D(&depthStencilTXTDesc, NULL, &depthStencilBuffer);
	CheckFailed(hr, "CE_Renderer", __LINE__, "Create Stencil Texture failed");

	hr = d3dDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
	CheckFailed(hr, "CE_Renderer", __LINE__, "Create Stencil View failed");

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	
	hr = d3dDevice->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	CheckFailed(hr, "CE_Renderer", __LINE__, "Create Depth Stencil State failed");

	d3dDeviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	D3D11_RASTERIZER_DESC rsDesc = {};
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_NONE;

	hr = d3dDevice->CreateRasterizerState(&rsDesc, &rasterizerState);
	CheckFailed(hr, "CE_Renderer", __LINE__, "Create Rasterizer State failed");

	d3dDeviceContext->RSSetState(rasterizerState);

	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = d3dDevice->CreateBlendState(&blendDesc, &blendState);
	CheckFailed(hr, "CE_Renderer", __LINE__, "Create Blend State failed");

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	d3dDeviceContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	viewPort.Width = _width;
	viewPort.Height = _height;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	d3dDeviceContext->RSSetViewports(1, &viewPort);
}

void CE_Renderer::BeginScene(FLOAT _red, FLOAT _green, FLOAT _blue)
{
	const FLOAT color[] = { _red, _green, _blue, 1.0f };
	d3dDeviceContext->ClearRenderTargetView(renderTargetView, color);

	d3dDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	d3dDeviceContext->OMSetDepthStencilState(depthStencilState, 0);
}

void CE_Renderer::EndScene()
{
	d3dSwapChain->Present(0, 0);
}

void CE_Renderer::DeInit()
{
	if (renderTargetView != nullptr) {
		renderTargetView->Release();
		renderTargetView = nullptr;
	}

	if (depthStencilState != nullptr) {
		depthStencilState->Release();
		depthStencilState = nullptr;
	}

	if (depthStencilView != nullptr) {
		depthStencilView->Release();
		depthStencilView = nullptr;
	}

	if (depthStencilBuffer != nullptr) {
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;
	}

	if (rasterizerState != nullptr) {
		rasterizerState->Release();
		rasterizerState = nullptr;
	}

	if (blendState != nullptr) {
		blendState->Release();
		blendState = nullptr;
	}

	if (d3dSwapChain != nullptr) {
		d3dSwapChain->Release();
		d3dSwapChain = nullptr;
	}

	if (d3dDeviceContext != nullptr) {
		d3dDeviceContext->Release();
		d3dDeviceContext = nullptr;
	}

	if (d3dDevice != nullptr) {
		d3dDevice->Release();
		d3dDevice = nullptr;
	}
}