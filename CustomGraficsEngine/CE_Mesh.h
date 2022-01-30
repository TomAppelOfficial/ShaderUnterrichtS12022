#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

#include "CE_Error.h"
#include "CE_Vertex.h"

class CE_Mesh
{
public:
	void Init();
	void Render();
	void DeInit();

	XMFLOAT4 Color = XMFLOAT4(1, 0, 0, 1);
protected:
	virtual void InitBuffer();
	void CreateBuffer();
	
	std::vector<CE_Vertex> vertices;
	std::vector<WORD> indicies;
	
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	UINT vertexStride = 0;
};

