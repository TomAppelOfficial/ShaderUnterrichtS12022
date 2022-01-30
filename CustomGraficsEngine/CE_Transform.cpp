#include "CE_Transform.h"

//using namespace DirectX;

void CE_Transform::Init()
{
	translationMat = XMMatrixIdentity();
	rotationMat = XMMatrixIdentity();
	scaleMat = XMMatrixIdentity();

	UpdateWorldMatrix();
}

void CE_Transform::Update()
{
	if (dirty) {
		UpdateWorldMatrix();
		dirty = false;
	}
}

void CE_Transform::AddDirection(XMFLOAT3 _dir)
{
	position.x += _dir.x;
	position.y += _dir.y;
	position.z += _dir.z;
}

void CE_Transform::AddDirection(XMVECTOR _dir)
{
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, _dir);
	position.x += dir.x;
	position.y += dir.y;
	position.z += dir.z;
}

void CE_Transform::UpdateWorldMatrix()
{
	translationMat = XMMatrixTranslation(position.x, position.y, position.z);

	rotationMat = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(eulerAngle.x),
		XMConvertToRadians(eulerAngle.y),
		XMConvertToRadians(eulerAngle.z)
	);

	scaleMat = XMMatrixScaling(scale.x, scale.y, scale.z);

	worldMat = scaleMat * rotationMat * translationMat;
}
