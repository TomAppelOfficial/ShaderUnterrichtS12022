#include "CE_PMSphere.h"

void CE_PMSphere::InitBuffer()
{
	int stackCount = 24;
	int sliceCount = 24;
	float radius = 1.0f;
	float x, y, z, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	float u, v;

	float sectorStep = XM_2PI / sliceCount;
	float stackStep = XM_PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = XM_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sliceCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)

			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			// vertex tex coord (u, v) range between [0, 1]
			u = (float)j / sliceCount;
			v = (float)i / stackCount;
			vertices.push_back({ XMFLOAT3(x, y, z),
							   XMFLOAT3(nx, ny, nz),
							   XMFLOAT2(u, v),
							   Color });
		}
	}

	// generate CCW index list of sphere triangles
	// k1--k1+1
	// |  / |
	// | /  |
	// k2--k2+1
	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sliceCount + 1);     // beginning of current stack
		k2 = k1 + sliceCount + 1;      // beginning of next stack

		for (int j = 0; j < sliceCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indicies.push_back(k1);
				indicies.push_back(k2);
				indicies.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indicies.push_back(k1 + 1);
				indicies.push_back(k2);
				indicies.push_back(k2 + 1);
			}
		}
	}
}

void CE_PMSphere::CalculateModelVectors()
{
	int faceCount, i, index, indiciesCount;
	TempVertexType vertex1, vertex2, vertex3;
	XMFLOAT3 tangent, binormal, normal;

	// Calculate the number of faces in the model.
	faceCount = vertices.size() / 3;
	short index1, index2, index3;
	// Initialize the index to the model data.
	index = 0;
	indiciesCount = indicies.size();
	for (i = 0; i < indiciesCount; i)
	{
		index1 = indicies[i++];
		index2 = indicies[i++];
		index3 = indicies[i++];

		// Get the three vertices for this face from the model.
		vertex1.x = vertices[index1].position.x;
		vertex1.y = vertices[index1].position.y;
		vertex1.z = vertices[index1].position.z;
		vertex1.tu = vertices[index1].uv.x;
		vertex1.tv = vertices[index1].uv.y;
		vertex1.nx = vertices[index1].normal.x;
		vertex1.ny = vertices[index1].normal.y;
		vertex1.nz = vertices[index1].normal.z;

		vertex2.x = vertices[index2].position.x;
		vertex2.y = vertices[index2].position.y;
		vertex2.z = vertices[index2].position.z;
		vertex2.tu = vertices[index2].uv.x;
		vertex2.tv = vertices[index2].uv.y;
		vertex2.nx = vertices[index2].normal.x;
		vertex2.ny = vertices[index2].normal.y;
		vertex2.nz = vertices[index2].normal.z;

		vertex3.x = vertices[index2].position.x;
		vertex3.y = vertices[index2].position.y;
		vertex3.z = vertices[index2].position.z;
		vertex3.tu = vertices[index2].uv.x;
		vertex3.tv = vertices[index2].uv.y;
		vertex3.nx = vertices[index2].normal.x;
		vertex3.ny = vertices[index2].normal.y;
		vertex3.nz = vertices[index2].normal.z;

		// Calculate the tangent and binormal of that face.
		CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);

		// Calculate the new normal using the tangent and binormal.
		CalculateNormal(tangent, binormal, normal);

		// Store the normal, tangent, and binormal for this face back in the model structure.
		vertices[index1].normal.x = normal.x;
		vertices[index1].normal.y = normal.y;
		vertices[index1].normal.z = normal.z;
		vertices[index1].tangent.x = tangent.x;
		vertices[index1].tangent.y = tangent.y;
		vertices[index1].tangent.z = tangent.z;
		vertices[index1].biNormal.x = binormal.x;
		vertices[index1].biNormal.y = binormal.y;
		vertices[index1].biNormal.z = binormal.z;

		vertices[index2].normal.x = normal.x;
		vertices[index2].normal.y = normal.y;
		vertices[index2].normal.z = normal.z;
		vertices[index2].tangent.x = tangent.x;
		vertices[index2].tangent.y = tangent.y;
		vertices[index2].tangent.z = tangent.z;
		vertices[index2].biNormal.x = binormal.x;
		vertices[index2].biNormal.y = binormal.y;
		vertices[index2].biNormal.z = binormal.z;

		vertices[index3].normal.x = normal.x;
		vertices[index3].normal.y = normal.y;
		vertices[index3].normal.z = normal.z;
		vertices[index3].tangent.x = tangent.x;
		vertices[index3].tangent.y = tangent.y;
		vertices[index3].tangent.z = tangent.z;
		vertices[index3].biNormal.x = binormal.x;
		vertices[index3].biNormal.y = binormal.y;
		vertices[index3].biNormal.z = binormal.z;
	}
}

void CE_PMSphere::CalculateTangentBinormal(TempVertexType vertex1, TempVertexType vertex2, TempVertexType vertex3, XMFLOAT3& tangent, XMFLOAT3& binormal)
{
	float vector1[3], vector2[3];
	float tuVector[2], tvVector[2];
	float den;
	float length;

	// Calculate the two vectors for this face.
	vector1[0] = vertex2.x - vertex1.x;
	vector1[1] = vertex2.y - vertex1.y;
	vector1[2] = vertex2.z - vertex1.z;

	vector2[0] = vertex3.x - vertex1.x;
	vector2[1] = vertex3.y - vertex1.y;
	vector2[2] = vertex3.z - vertex1.z;

	// Calculate the tu and tv texture space vectors.
	tuVector[0] = vertex2.tu - vertex1.tu;
	tvVector[0] = vertex2.tv - vertex1.tv;

	tuVector[1] = vertex3.tu - vertex1.tu;
	tvVector[1] = vertex3.tv - vertex1.tv;

	// Calculate the denominator of the tangent/binormal equation.
	den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

	// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
	tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
	tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
	tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

	binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
	binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
	binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

	// Calculate the length of this normal.
	length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));

	// Normalize the normal and then store it
	tangent.x = tangent.x / length;
	tangent.y = tangent.y / length;
	tangent.z = tangent.z / length;

	// Calculate the length of this normal.
	length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) + (binormal.z * binormal.z));

	// Normalize the normal and then store it
	binormal.x = binormal.x / length;
	binormal.y = binormal.y / length;
	binormal.z = binormal.z / length;
}

void CE_PMSphere::CalculateNormal(XMFLOAT3 tangent, XMFLOAT3 binormal, XMFLOAT3& normal)
{
	float length;


	// Calculate the cross product of the tangent and binormal which will give the normal vector.
	normal.x = (tangent.y * binormal.z) - (tangent.z * binormal.y);
	normal.y = (tangent.z * binormal.x) - (tangent.x * binormal.z);
	normal.z = (tangent.x * binormal.y) - (tangent.y * binormal.x);

	// Calculate the length of the normal.
	length = sqrt((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));

	// Normalize the normal.
	normal.x = normal.x / length;
	normal.y = normal.y / length;
	normal.z = normal.z / length;
}