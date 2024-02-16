#include "Main.h"
#include "RenderManager.h"
#include "Camera.h"

Camera::Camera()
{
	m_Position = XMFLOAT3(0,0.3f,-0.5f);
	m_Target = XMFLOAT3(0, 0, 0.1f);
	m_Up = XMFLOAT3(0, 1, 0);
}

void Camera::Update()
{
	m_RotAng += 20.0f/60.0f*3.14f/180.0f;
	if (m_RotAng > 360.0f)
	{
		m_RotAng - 360.0f;
	}
	float radius = 0.3f;
	//m_Position.x = radius * cosf(m_RotAng);
	//m_Position.z = radius * sinf(m_RotAng);

	if (GetKeyState('W') & 0x80)
	{
		m_Target.y += 0.01f;
	}if (GetKeyState('S') & 0x80)
	{
		m_Target.y -= 0.01f;
	}

	if (GetKeyState('A') & 0x80)
	{
		m_Target.x -= 0.01f;
	}if (GetKeyState('D') & 0x80)
	{
		m_Target.x += 0.01f;
	}
}

void Camera::Set3DView()
{
	RenderManager* rm = RenderManager::GetInstance();

	ImGui::Begin("Camera Settings");

	ImGui::DragFloat3("Position", &m_Position.x);
	ImGui::DragFloat3("Target", &m_Target.x);

	ImGui::End();

	{
		XMMATRIX view = XMMatrixIdentity();
		view = XMMatrixLookAtLH(
			XMLoadFloat3(&m_Position),
			XMLoadFloat3(&m_Target),
			XMLoadFloat3(&m_Up));


		XMMATRIX projection;
		float aspect = (float)rm->GetBackBufferWidth() /
			(float)rm->GetBackBufferHeight();
		projection = XMMatrixPerspectiveFovLH(
			1.0f,
			aspect,
			0.1f,
			100.0f);

		CAMERA_CONSTANT constant{};
		XMStoreFloat4x4(&constant.View, XMMatrixTranspose(view));
		XMStoreFloat4x4(&constant.Projection, XMMatrixTranspose(projection)); 
		constant.Position = { m_Position.x,m_Position.y,m_Position.z,1.0f };

		rm->SetConstant(RenderManager::CONSTANT_TYPE::CAMERA, &constant, sizeof(constant));
	}
}

void Camera::Set2DView()
{
	RenderManager* rm = RenderManager::GetInstance();
	XMMATRIX view = XMMatrixIdentity();
	XMMATRIX projection;
	projection = XMMatrixOrthographicOffCenterLH
	(
		0,
		rm->GetBackBufferWidth(),
		rm->GetBackBufferHeight(), 0, 0, 1);

	CAMERA_CONSTANT constant{};
	XMStoreFloat4x4(&constant.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&constant.Projection, XMMatrixTranspose(projection));

	rm->SetConstant(RenderManager::CONSTANT_TYPE::CAMERA, &constant, sizeof(constant));
}
