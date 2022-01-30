#include "CE_ObjectPool.h"
#include "CE_Core.h"

void CE_ObjectPool::Update()
{
	for (std::shared_ptr<CE_Object> obj : object) {
		obj->Update();
	}

	for (std::shared_ptr<CE_Object> obj : toRemove) {
		object.remove(obj);
	}
	toRemove.clear();
}

void CE_ObjectPool::Render(CE_Light& _light)
{
	for (std::shared_ptr<CE_Object> obj : object) {
		obj->Render(_light);
	}
}

void CE_ObjectPool::AddObject(std::shared_ptr<CE_Object> _object)
{
	if (_object == nullptr)
		return;

	object.push_back(_object);
}

void CE_ObjectPool::RemoveObject(std::shared_ptr<CE_Object> _object)
{
	if (_object == nullptr)
		return;

	toRemove.push_back(_object);
}
