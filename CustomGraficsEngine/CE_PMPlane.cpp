#include "CE_PMPlane.h"

void CE_PMPlane::InitBuffer()
{
	vertices.push_back({ XMFLOAT3(-5.0f,5.0f,  0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(-5.0f,-5.0f, 0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(5.0f, -5.0f, 0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(1, 0), Color });
	vertices.push_back({ XMFLOAT3(5.0f,	5.0f,  0.0f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(1, 1), Color });

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

	XMFLOAT3 pos1 = vertices[0].position;
	XMFLOAT3 pos2 = vertices[1].position;
	XMFLOAT3 pos3 = vertices[2].position;

	XMFLOAT2 uv1 = vertices[0].uv;
	XMFLOAT2 uv2 = vertices[1].uv;
	XMFLOAT2 uv3 = vertices[2].uv;

	XMFLOAT3 normal = vertices[0].normal;

	XMFLOAT3 edge1 = XMFLOAT3(pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z);
	XMFLOAT3 edge2 = XMFLOAT3(pos3.x - pos1.x, pos3.y - pos1.y, pos3.z - pos1.z);

	XMFLOAT2 deltaUV1 = XMFLOAT2(uv2.x - uv1.x, uv2.y - uv1.y);
	XMFLOAT2 deltaUV2 = XMFLOAT2(uv3.x - uv1.x, uv3.y - uv1.y);

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	XMFLOAT3 tangent;
	XMFLOAT3 binormal;

	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	binormal.x = f * (deltaUV2.x * edge1.x - deltaUV1.x * edge2.x);
	binormal.y = f * (deltaUV2.x * edge1.y - deltaUV1.x * edge2.y);
	binormal.z = f * (deltaUV2.x * edge1.z - deltaUV1.x * edge2.z);

	vertices[0].tangent = tangent;
	vertices[1].tangent = tangent;
	vertices[2].tangent = tangent;

	vertices[0].biNormal = binormal;
	vertices[1].biNormal = binormal;
	vertices[2].biNormal = binormal;

	//Second Triangle
	pos1 = vertices[1].position;
	pos2 = vertices[2].position;
	pos3 = vertices[3].position;

	uv1 = vertices[1].uv;
	uv2 = vertices[2].uv;
	uv3 = vertices[3].uv;

	normal = vertices[0].normal;

	edge1 = XMFLOAT3(pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z);
	edge2 = XMFLOAT3(pos3.x - pos1.x, pos3.y - pos1.y, pos3.z - pos1.z);

	deltaUV1 = XMFLOAT2(uv2.x - uv1.x, uv2.y - uv1.y);
	deltaUV2 = XMFLOAT2(uv3.x - uv1.x, uv3.y - uv1.y);

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	binormal.x = f * (deltaUV2.x * edge1.x - deltaUV1.x * edge2.x);
	binormal.y = f * (deltaUV2.x * edge1.y - deltaUV1.x * edge2.y);
	binormal.z = f * (deltaUV2.x * edge1.z - deltaUV1.x * edge2.z);

	vertices[1].tangent = tangent;
	vertices[2].tangent = tangent;
	vertices[3].tangent = tangent;

	vertices[1].biNormal = binormal;
	vertices[2].biNormal = binormal;
	vertices[3].biNormal = binormal;
}



//void CE_PMPlane::CalculateModelVectors()
//{
//	int faceCount, i, index, indiciesCount;
//	TempVertexType vertex1, vertex2, vertex3;
//	XMFLOAT3 tangent, binormal, normal;
//
//	// Calculate the number of faces in the model.
//	faceCount = vertices.size() / 3;
//	short index1, index2, index3;
//	// Initialize the index to the model data.
//	index = 0;
//	indiciesCount = indicies.size();
//	for (i = 0; i < indiciesCount; i)
//	{
//		index1 = indicies[i++];
//		index2 = indicies[i++];
//		index3 = indicies[i++];
//
//		// Get the three vertices for this face from the model.
//		vertex1.x = vertices[index1].position.x;
//		vertex1.y = vertices[index1].position.y;
//		vertex1.z = vertices[index1].position.z;
//		vertex1.tu = vertices[index1].uv.x;
//		vertex1.tv = vertices[index1].uv.y;
//		vertex1.nx = vertices[index1].normal.x;
//		vertex1.ny = vertices[index1].normal.y;
//		vertex1.nz = vertices[index1].normal.z;
//
//		vertex2.x = vertices[index2].position.x;
//		vertex2.y = vertices[index2].position.y;
//		vertex2.z = vertices[index2].position.z;
//		vertex2.tu = vertices[index2].uv.x;
//		vertex2.tv = vertices[index2].uv.y;
//		vertex2.nx = vertices[index2].normal.x;
//		vertex2.ny = vertices[index2].normal.y;
//		vertex2.nz = vertices[index2].normal.z;
//
//		vertex3.x = vertices[index2].position.x;
//		vertex3.y = vertices[index2].position.y;
//		vertex3.z = vertices[index2].position.z;
//		vertex3.tu = vertices[index2].uv.x;
//		vertex3.tv = vertices[index2].uv.y;
//		vertex3.nx = vertices[index2].normal.x;
//		vertex3.ny = vertices[index2].normal.y;
//		vertex3.nz = vertices[index2].normal.z;
//
//		// Calculate the tangent and binormal of that face.
//		CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);
//
//		// Calculate the new normal using the tangent and binormal.
//		CalculateNormal(tangent, binormal, normal);
//
//		// Store the normal, tangent, and binormal for this face back in the model structure.
//		vertices[index1].normal.x = normal.x;
//		vertices[index1].normal.y = normal.y;
//		vertices[index1].normal.z = normal.z;
//		vertices[index1].tangent.x = tangent.x;
//		vertices[index1].tangent.y = tangent.y;
//		vertices[index1].tangent.z = tangent.z;
//		vertices[index1].biNormal.x = binormal.x;
//		vertices[index1].biNormal.y = binormal.y;
//		vertices[index1].biNormal.z = binormal.z;
//
//		vertices[index2].normal.x = normal.x;
//		vertices[index2].normal.y = normal.y;
//		vertices[index2].normal.z = normal.z;
//		vertices[index2].tangent.x = tangent.x;
//		vertices[index2].tangent.y = tangent.y;
//		vertices[index2].tangent.z = tangent.z;
//		vertices[index2].biNormal.x = binormal.x;
//		vertices[index2].biNormal.y = binormal.y;
//		vertices[index2].biNormal.z = binormal.z;
//
//		vertices[index3].normal.x = normal.x;
//		vertices[index3].normal.y = normal.y;
//		vertices[index3].normal.z = normal.z;
//		vertices[index3].tangent.x = tangent.x;
//		vertices[index3].tangent.y = tangent.y;
//		vertices[index3].tangent.z = tangent.z;
//		vertices[index3].biNormal.x = binormal.x;
//		vertices[index3].biNormal.y = binormal.y;
//		vertices[index3].biNormal.z = binormal.z;
//	}
//}
//
//void CE_PMPlane::CalculateTangentBinormal(TempVertexType vertex1, TempVertexType vertex2, TempVertexType vertex3, XMFLOAT3& tangent, XMFLOAT3& binormal)
//{
//	float vector1[3], vector2[3];
//	float tuVector[2], tvVector[2];
//	float den;
//	float length;
//
//	// Calculate the two vectors for this face.
//	vector1[0] = vertex2.x - vertex1.x;
//	vector1[1] = vertex2.y - vertex1.y;
//	vector1[2] = vertex2.z - vertex1.z;
//
//	vector2[0] = vertex3.x - vertex1.x;
//	vector2[1] = vertex3.y - vertex1.y;
//	vector2[2] = vertex3.z - vertex1.z;
//
//	// Calculate the tu and tv texture space vectors.
//	tuVector[0] = vertex2.tu - vertex1.tu;
//	tvVector[0] = vertex2.tv - vertex1.tv;
//
//	tuVector[1] = vertex3.tu - vertex1.tu;
//	tvVector[1] = vertex3.tv - vertex1.tv;
//
//	// Calculate the denominator of the tangent/binormal equation.
//	den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);
//
//	// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
//	tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
//	tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
//	tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;
//
//	binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
//	binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
//	binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;
//
//	// Calculate the length of this normal.
//	length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));
//
//	// Normalize the normal and then store it
//	tangent.x = tangent.x / length;
//	tangent.y = tangent.y / length;
//	tangent.z = tangent.z / length;
//
//	// Calculate the length of this normal.
//	length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) + (binormal.z * binormal.z));
//
//	// Normalize the normal and then store it
//	binormal.x = binormal.x / length;
//	binormal.y = binormal.y / length;
//	binormal.z = binormal.z / length;
//}
//
//void CE_PMPlane::CalculateNormal(XMFLOAT3 tangent, XMFLOAT3 binormal, XMFLOAT3& normal)
//{
//	float length;
//
//
//	// Calculate the cross product of the tangent and binormal which will give the normal vector.
//	normal.x = (tangent.y * binormal.z) - (tangent.z * binormal.y);
//	normal.y = (tangent.z * binormal.x) - (tangent.x * binormal.z);
//	normal.z = (tangent.x * binormal.y) - (tangent.y * binormal.x);
//
//	// Calculate the length of the normal.
//	length = sqrt((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));
//
//	// Normalize the normal.
//	normal.x = normal.x / length;
//	normal.y = normal.y / length;
//	normal.z = normal.z / length;
//}