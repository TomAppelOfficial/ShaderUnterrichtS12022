#include "CE_PMCube.h"

void CE_PMCube::InitBuffer()
{
	vertices.push_back({ XMFLOAT3(-0.5f, -0.5f, -0.5f),	XMFLOAT3(0, 0, -1), XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(0.5f, -0.5f, -0.5f),	XMFLOAT3(0, 0, -1), XMFLOAT2(1, 1), Color });
	vertices.push_back({ XMFLOAT3(-0.5f,  0.5f, -0.5f),	XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(0.5f,  0.5f, -0.5f),	XMFLOAT3(0, 0, -1), XMFLOAT2(1, 0), Color });

	// rechts
	vertices.push_back({ XMFLOAT3(0.5f, -0.5f, -0.5f),	XMFLOAT3(1, 0, 0),	XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(0.5f, -0.5f,  0.5f),	XMFLOAT3(1, 0, 0),	XMFLOAT2(1, 1), Color });
	vertices.push_back({ XMFLOAT3(0.5f,  0.5f, -0.5f),	XMFLOAT3(1, 0, 0),	XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(0.5f,  0.5f,  0.5f),	XMFLOAT3(1, 0, 0),	XMFLOAT2(1, 0), Color });

	// hinten
	vertices.push_back({ XMFLOAT3(0.5f, -0.5f,  0.5f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(-0.5f, -0.5f,  0.5f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(1, 1), Color });
	vertices.push_back({ XMFLOAT3(0.5f,  0.5f,  0.5f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(-0.5f,  0.5f,  0.5f),	XMFLOAT3(0, 0, 1),	XMFLOAT2(1, 0), Color });

	// links
	vertices.push_back({ XMFLOAT3(-0.5f, -0.5f,  0.5f),	XMFLOAT3(-1, 0, 0), XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(-0.5f, -0.5f, -0.5f),	XMFLOAT3(-1, 0, 0), XMFLOAT2(1, 1), Color });
	vertices.push_back({ XMFLOAT3(-0.5f,  0.5f,  0.5f),	XMFLOAT3(-1, 0, 0), XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(-0.5f,  0.5f, -0.5f),	XMFLOAT3(-1, 0, 0), XMFLOAT2(1, 0), Color });

	// oben
	vertices.push_back({ XMFLOAT3(-0.5f, 0.5f, -0.5f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(0.5f, 0.5f, -0.5f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(1, 1), Color });
	vertices.push_back({ XMFLOAT3(-0.5f, 0.5f,  0.5f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(0.5f, 0.5f,  0.5f),	XMFLOAT3(0, 1, 0),	XMFLOAT2(1, 0), Color });

	// unten
	vertices.push_back({ XMFLOAT3(0.5f, -0.5f, -0.5f),	XMFLOAT3(0, -1, 0), XMFLOAT2(0, 1), Color });
	vertices.push_back({ XMFLOAT3(-0.5f, -0.5f, -0.5f),	XMFLOAT3(0, -1, 0), XMFLOAT2(1, 1), Color });
	vertices.push_back({ XMFLOAT3(0.5f, -0.5f,  0.5f),	XMFLOAT3(0, -1, 0), XMFLOAT2(0, 0), Color });
	vertices.push_back({ XMFLOAT3(-0.5f, -0.5f,  0.5f),	XMFLOAT3(0, -1, 0), XMFLOAT2(1, 0), Color });


	for (int i = 0; i < 6; i++)
	{
		indicies.push_back(0 + i * 4);
		indicies.push_back(2 + i * 4);
		indicies.push_back(3 + i * 4);

		indicies.push_back(3 + i * 4);
		indicies.push_back(1 + i * 4);
		indicies.push_back(0 + i * 4);
	}
}
