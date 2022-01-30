#include "CE_Object.h"
//#include "CE_Core.h"
#include "CE_Light.h"

void CE_Object::Init(std::shared_ptr<CE_Mesh> _mesh, std::shared_ptr<CE_Material> _material)
{
	Transform = std::make_unique<CE_Transform>();
	Mesh = _mesh;
	Material = _material;
}

void CE_Object::Update()
{
	Transform->Update();
}

void CE_Object::Render(CE_Light& _light)
{
	Material->Render(*this, _light);

	Mesh->Render();
}

void CE_Object::DeInit()
{
	Material->DeInit();
	Mesh->DeInit();
}
