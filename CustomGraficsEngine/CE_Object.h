#pragma once
#include "CE_Transform.h"
#include "CE_Material.h"
#include "CE_Mesh.h"

class CE_Object
{
public:
	void Init(std::shared_ptr<CE_Mesh> _mesh, std::shared_ptr<CE_Material> _material);

	virtual void Update();
	void Render(CE_Light& _light);

	void DeInit();
	
	std::unique_ptr<CE_Transform> Transform;
	std::shared_ptr<CE_Mesh> Mesh;
	std::shared_ptr<CE_Material> Material;
};

