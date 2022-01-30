#pragma once
#include <d3d11.h>

#include "CE_Error.h"

#pragma comment(lib, "d3d11.lib")

class CE_Renderer
{
public:
	void Init(HWND _hwnd, INT _width, INT _height, bool _isWindowed);

	void BeginScene(FLOAT _red, FLOAT _green, FLOAT _blue);
	void EndScene();
	void DeInit();

	/// <summary>
	/// Object for Creating direct 3d Objects
	/// </summary>
	/// <returns></returns>
	ID3D11Device* D3DDevice() { return d3dDevice; }
	/// <summary>
	/// Object for modify the Render Pipeline
	/// </summary>
	/// <returns></returns>
	ID3D11DeviceContext* D3DDeviceContext() { return d3dDeviceContext; }
private:
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dDeviceContext = nullptr;
	//Holds the reference to front & back buffer and for switching those
	IDXGISwapChain* d3dSwapChain = nullptr;

	//Tiefenbuffer stuff
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11DepthStencilState* depthStencilState;

	//Blending stuff
	ID3D11BlendState* blendState = nullptr;

	
	ID3D11RasterizerState* rasterizerState;

	ID3D11RenderTargetView* renderTargetView;
	D3D11_VIEWPORT viewPort = {};
};

