#pragma once
#include <memory>
#include <list>
#include "CE_Light.h"
#include "CE_Object.h"

class CE_ObjectPool
{
public:
	void Update();
	void Render(CE_Light& _light);

	void AddObject(std::shared_ptr<CE_Object> _object);
	void RemoveObject(std::shared_ptr<CE_Object> _object);

private:
	std::list<std::shared_ptr<CE_Object>> object;
	std::list<std::shared_ptr<CE_Object>> toRemove;
};

