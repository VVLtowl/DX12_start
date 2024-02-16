#include "Main.h"
#include "RenderManager.h"
#include <memory>
#include "model.h"
#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	m_Model.Load("Asset\\Drill_01_4k.obj");

	m_Position = { 0,0,0 };
	m_Rotation = { 0,0,0 };
	m_Scale = { 1,1,1 };

	RenderManager* rm = RenderManager::GetInstance();
	m_TextureArm = rm->LoadTexture("Asset\\Drill_01_arm_4k.dds");
}

void Polygon3D::Update()
{
	m_Rotation.y += 0.5f*3.14f/180.0f;
}

void Polygon3D::Draw()
{
	RenderManager* rm = RenderManager::GetInstance();

	//set matrix
	{
		XMMATRIX world = XMMatrixIdentity();
		world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		OBJECT_CONSTANT constant{};
		XMStoreFloat4x4(&constant.World, XMMatrixTranspose(world));

		rm->SetConstant(RenderManager::CONSTANT_TYPE::OBJECT, &constant, sizeof(constant));
	}

	rm->SetTexture(RenderManager::TEXTURE_TYPE::ARM, m_TextureArm.get());

	//piprline setting
	//rm->SetPipelineState("Unlit");

	//draw
	m_Model.Draw();
}
