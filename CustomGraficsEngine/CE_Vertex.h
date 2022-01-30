#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct CE_Vertex
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
	XMFLOAT4 color;
	//XMFLOAT3 tangent;
	//XMFLOAT3 biTangent;

	CE_Vertex() :
		position(0.0f, 0.0f, 0.0f),
		color(0.0f, 0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f),
		uv(0.0f, 0.0f)
		//, tangent(0.0f, 0.0f, 0.0f)
		//, biTangent(0.0f, 0.0f, 0.0f)
	{}

	CE_Vertex(float x, float y, float z) :
		position(x, y, z),
		color(0.0f, 0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f),
		uv(0.0f, 0.0f)
		//, tangent(0.0f, 0.0f, 0.0f)
		//, biTangent(0.0f, 0.0f, 0.0f)
	{}

	CE_Vertex(float x, float y, float z, float r, float g, float b, float a) :
		position(x, y, z),
		color(r, g, b, a),
		normal(0.0f, 0.0f, 0.0f),
		uv(0.0f, 0.0f)
		//, tangent(0.0f, 0.0f, 0.0f)
		//, biTangent(0.0f, 0.0f, 0.0f)
	{}

	CE_Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v) :
		position(x, y, z),
		color(r, g, b, a),
		uv(u, v),
		normal(0.0f, 0.0f, 0.0f)
		//, tangent(0.0f, 0.0f, 0.0f)
		//, biTangent(0.0f, 0.0f, 0.0f)
	{}

	CE_Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v, float nx, float ny, float nz) :
		position(x, y, z),
		color(r, g, b, a),
		uv(u, v),
		normal(nx, ny, nz)
		//, tangent(0.0f, 0.0f, 0.0f)
		//, biTangent(0.0f, 0.0f, 0.0f)
	{}

	CE_Vertex(XMFLOAT3 _pos, XMFLOAT3 _normal, XMFLOAT2 _uv, XMFLOAT4 _color) :
		position(_pos),
		normal(_normal),
		uv(_uv),
		color(_color)
		//, tangent(0.0f, 0.0f, 0.0f)
		//, biTangent(0.0f, 0.0f, 0.0f)
	{}
};