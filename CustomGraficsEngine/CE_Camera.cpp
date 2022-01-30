#include "CE_Camera.h"
#include "CE_Core.h"
#include "CE_Timer.h"

using namespace DirectX;

void CE_Camera::Init(INT _width, INT _height)
{
	Transform = std::make_unique<CE_Transform>();
	Transform->Init();
	width = _width;
	height = _height;
}

void CE_Camera::Update()
{
	Movement();


	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(Transform->GetEulerAngle().x, Transform->GetEulerAngle().y, Transform->GetEulerAngle().z);
	//camTarget = XMVector3TransformCoord(dForward, Transform->GetRotationMat());
	camTarget = XMVector3TransformCoord(dForward, rotationMatrix);
	camTarget += XMLoadFloat3(&Transform->GetPositon());

	//XMVECTOR upDir = XMVector3TransformCoord(dUp, Transform->GetRotationMat());
	XMVECTOR upDir = XMVector3TransformCoord(dUp, rotationMatrix);
	view = XMMatrixLookAtLH(XMLoadFloat3(&Transform->GetPositon()), camTarget, upDir);

	XMMATRIX rotateMatrix = XMMatrixRotationRollPitchYaw(Transform->GetEulerAngle().x, Transform->GetEulerAngle().y, 0.0f);
	localForward = XMVector3TransformCoord(dForward, rotateMatrix);
	localLeft = XMVector3TransformCoord(dLeft, rotateMatrix);
	localRight = XMVector3TransformCoord(dRight, rotateMatrix);
	localBackward = XMVector3TransformCoord(dBackward, rotateMatrix);

	projection = XMMatrixPerspectiveFovLH(
		XM_PI * 0.33333333f, // field of view
		static_cast<float>(width) / static_cast<float>(height), //aspect ratio
		nearPlane, farPlane // near & far clipping plane
	);

	viewPojection = view * projection;

	Transform->Update();
}

void CE_Camera::Movement()
{
	keyboard.Reset();
	auto key = Keyboard::Get().GetState();
	keyboard.Update(key);

	float speed = 10 * CORE_DELTA_TIME;

	if (key.W) {
		Transform->AddDirection(localForward * speed);
	}

	if (key.S) {
		Transform->AddDirection(localBackward * speed);
	}

	if (key.A) {
		Transform->AddDirection(localLeft * speed);
	}

	if (key.D) {
		Transform->AddDirection(localRight * speed);
	}

	XMFLOAT3 tempEuler = Transform->GetEulerAngle();
	speed *= 0.2f;
	if (key.Up) {
		tempEuler.x -= speed;
	}
	if (key.Down) {
		tempEuler.x += speed;
	}
	if (key.Left) {
		tempEuler.y -= speed;
	}
	if (key.Right) {
		tempEuler.y += speed;
	}
	Transform->SetEulerAngle(tempEuler);
}