#include "CE_Mesh.h"
#include "CE_Core.h"

void CE_Mesh::Init()
{
	InitBuffer();
	CreateBuffer();
}

void CE_Mesh::Render()
{
	static UINT offset = 0;

	CORE_DEVICECONTEXT->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &offset);
	CORE_DEVICECONTEXT->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CORE_DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CORE_DEVICECONTEXT->DrawIndexed(indicies.size(), 0, 0);
}

void CE_Mesh::DeInit()
{
	if (vertexBuffer != nullptr) {
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}

	if (indexBuffer != nullptr) {
		indexBuffer->Release();
		indexBuffer = nullptr;
	}
}

void CE_Mesh::InitBuffer()
{

}

void CE_Mesh::CreateBuffer()
{
	vertexStride = sizeof(CE_Vertex);
	{
		D3D11_BUFFER_DESC desc = {};
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = vertices.size() * vertexStride;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = vertices.data();


		HRESULT hr = CORE_DEVICE->CreateBuffer(&desc, &data, &vertexBuffer);
		CheckFailed(hr, "CE_Mesh", __LINE__, "Create Buffer failed");
	
	}
	{
		D3D11_BUFFER_DESC desc = {};
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = indicies.size() * sizeof(WORD);

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = indicies.data();

		HRESULT hr = CORE_DEVICE->CreateBuffer(&desc, &data, &indexBuffer);
		CheckFailed(hr, "CE_Mesh", __LINE__, "Create Index Buffer failed");
	}
}
