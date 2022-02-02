#pragma once
#include "CE_Mesh.h"

class CE_PMPlane : public CE_Mesh
{
protected:
	virtual void InitBuffer() override;
	virtual void CalculateModelVectors() override;
	virtual void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, XMFLOAT3&, XMFLOAT3&) override;
	virtual void CalculateNormal(XMFLOAT3, XMFLOAT3, XMFLOAT3&) override;
};

