#include "CE_PMPlane.h"

void CE_PMPlane::InitBuffer()
{
	vertices.push_back({ XMFLOAT3(-5.0f, 5.0f, 0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(-5.0f,-5.0f, 0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(5.0f,-5.0f, 0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(1, 0), Color });
	vertices.push_back({ XMFLOAT3(5.0f, 5.0f, 0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(1, 1), Color });

	indicies.push_back(0);
	indicies.push_back(1);
	indicies.push_back(2);

	indicies.push_back(0);
	indicies.push_back(2);
	indicies.push_back(3);

	CalculateModelVectors();
}

void CE_PMPlane::CalculateModelVectors()
{
	XMFLOAT3 pos1;
	XMFLOAT3 pos2;
	XMFLOAT3 pos3;
	XMFLOAT3 edge1;
	XMFLOAT3 edge2;
	XMFLOAT2 deltaUV1;
	XMFLOAT2 deltaUV2;
	XMFLOAT3 tangent1;
	XMFLOAT3 biNormal1;
	float f;

	//First triangle
	pos1 = vertices[0].position;
	pos2 = vertices[1].position;
	pos3 = vertices[2].position;

	edge1 = XMFLOAT3(pos2.x - pos1.x,
					 pos2.y - pos1.y,
					 pos2.z - pos1.z);

	edge2 = XMFLOAT3(pos3.x - pos1.x,
					 pos3.y - pos1.y,
					 pos3.z - pos1.z);

	deltaUV1 = XMFLOAT2(vertices[1].uv.x-vertices[0].uv.x, vertices[1].uv.y - vertices[0].uv.y);
	deltaUV2 = XMFLOAT2(vertices[2].uv.x - vertices[0].uv.x, vertices[2].uv.y - vertices[0].uv.y);

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	biNormal1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	biNormal1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	biNormal1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	vertices[0].tangent = tangent1;
	vertices[1].tangent = tangent1;
	vertices[2].tangent = tangent1;
	vertices[0].biNormal = biNormal1;
	vertices[1].biNormal = biNormal1;
	vertices[2].biNormal = biNormal1;
	//Second Triangle
	pos1 = vertices[0].position;
	pos2 = vertices[2].position;
	pos3 = vertices[3].position;

	edge1 = XMFLOAT3(pos2.x - pos1.x,
					 pos2.y - pos1.y,
					 pos2.z - pos1.z);

	edge2 = XMFLOAT3(pos3.x - pos1.x,
					 pos3.y - pos1.y,
					 pos3.z - pos1.z);

	deltaUV1 = XMFLOAT2(vertices[2].uv.x - vertices[0].uv.x, vertices[2].uv.y - vertices[0].uv.y);
	deltaUV2 = XMFLOAT2(vertices[3].uv.x - vertices[0].uv.x, vertices[3].uv.y - vertices[0].uv.y);

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	biNormal1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	biNormal1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	biNormal1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	vertices[0].tangent = tangent1;
	vertices[2].tangent = tangent1;
	vertices[3].tangent = tangent1;
	vertices[0].biNormal = biNormal1;
	vertices[2].biNormal = biNormal1;
	vertices[3].biNormal = biNormal1;
}