#include "CE_PMPlane.h"

void CE_PMPlane::InitBuffer()
{
	vertices.push_back({ XMFLOAT3(-5.0f,	0.0f, -5.0f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(5.0f,	0.0f, -5.0f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(1, 1), Color });
	vertices.push_back({ XMFLOAT3(-5.0f,	0.0f,  5.0f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(5.0f,	0.0f,  5.0f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(1, 0), Color });

	indicies.push_back(0);
	indicies.push_back(2);
	indicies.push_back(3);
	
	indicies.push_back(3);
	indicies.push_back(1);
	indicies.push_back(0);
}
