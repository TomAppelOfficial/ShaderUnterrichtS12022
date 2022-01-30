#pragma once
#include <memory>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Keyboard.h"

#include "CE_Error.h"
#include "CE_Transform.h"



class CE_Camera
{
public:
	void Init(INT _width, INT _height);
	void Update();
	void Movement();
	
	XMMATRIX GetViewMatrix() { return view; }
	XMMATRIX GetProjectionMatrix() { return projection; }
	XMMATRIX GetViewProjectionMatrix() { return viewPojection; }

	std::unique_ptr<CE_Transform> Transform;

private:

	XMMATRIX view = {};
	XMMATRIX projection = {};
	XMMATRIX viewPojection = {};

	INT width;
	INT height;

	float nearPlane = 0.3f;
	float farPlane = 1000.0f;

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;
	float moveUpDown = 0.0f;

	float yaw = 0.0f;
	float pitch = 0.0f;

	XMVECTOR camTarget = XMVectorSet(0,0,1,0);

	XMVECTOR dForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR dBackward = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	XMVECTOR dRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR dLeft = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR dUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMVECTOR localForward;
	XMVECTOR localLeft;
	XMVECTOR localRight;
	XMVECTOR localBackward;

	DirectX::Keyboard::KeyboardStateTracker keyboard;
};

