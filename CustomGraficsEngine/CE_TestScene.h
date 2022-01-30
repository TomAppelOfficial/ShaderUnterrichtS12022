#pragma once
#include "CE_Scence.h"
#include "CE_Light.h"

class CE_TestScene : public CE_Scence
{
public:
	virtual void Init() override;
	CE_Light GetSceneLight();
	void SetlightDirection(float x, float y, float z);

private:
	std::unique_ptr<CE_Light> m_light;
};

