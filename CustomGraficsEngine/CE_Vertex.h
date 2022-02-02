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
	//XMFLOAT3 biNormal;


	CE_Vertex(float x, float y, float z,
		float nX, float nY, float nZ,
		float u, float v,
		float tX, float tY, float tZ,
		float bX, float bY, float bZ,
		float cR, float cG, float cB, float cA) :
		position(x, y, z),
		normal(nX, nY, nZ),
		uv(u, v),
		//tangent(tX, tY, tZ),
		//biNormal(bX, bY, bZ),
		color(cR, cG, cB, cA)
	 {}

	CE_Vertex(XMFLOAT3 _pos, XMFLOAT3 _normal, XMFLOAT2 _uv, XMFLOAT3 _tangent, XMFLOAT3 _binormal, XMFLOAT4 _color) :
		CE_Vertex(_pos.x, _pos.y, _pos.z,
				  _normal.x, _normal.y, _normal.z,
				  _uv.x, _uv.y,
				  _tangent.x, _tangent.y, _tangent.z,
				  _binormal.x, _binormal.y, _binormal.z,
				  _color.x, _color.y, _color.z, _color.w)
	{}

	CE_Vertex(XMFLOAT3 _pos, XMFLOAT3 _normal, XMFLOAT2 _uv, XMFLOAT4 _color) :
		position(_pos.x, _pos.y, _pos.z),
		normal(_normal.x, _normal.y, _normal.z),
		uv(_uv.x, _uv.y),
		//tangent(0.0f, 0.0f, 0.0f),
		//biNormal(0.0f, 0.0f, 0.0f),
		color(_color.x, _color.y, _color.z, _color.w)
	{}
};

struct TempVertexType {
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};