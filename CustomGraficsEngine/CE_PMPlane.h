#pragma once
#include "CE_Mesh.h"

class CE_PMPlane : public CE_Mesh
{
protected:
	virtual void InitBuffer() override;
	virtual void CalculateModelVectors() override;
};

