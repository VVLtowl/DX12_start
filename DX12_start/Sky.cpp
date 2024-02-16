

#include "Main.h"
#include "RenderManager.h"
#include "Sky.h"





Sky::Sky()
{
	m_Model.Load("Asset\\sky.obj");

	m_Texture = RenderManager::GetInstance()->LoadTexture("Asset\\snow_field_sky_2k_EXR_BC6H_1.dds");
	m_TextureArm = RenderManager::GetInstance()->LoadTexture("Asset\\white 1.dds");

	m_Position = { 0.0f, 0.0f, 0.0f };
	m_Rotation = { 0.0f, 0.0f, 0.0f };
	m_Scale = { 500.0f, 500.0f, 500.0f };

}




void Sky::Update()
{

}





void Sky::Draw()
{
	RenderManager* renderManager = RenderManager::GetInstance();



	//マトリクス設定
	{
		XMMATRIX world = XMMatrixIdentity();
		world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.z, m_Rotation.x, m_Rotation.y);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		OBJECT_CONSTANT constant{};
		XMStoreFloat4x4(&constant.World, XMMatrixTranspose(world));

		renderManager->SetConstant(RenderManager::CONSTANT_TYPE::OBJECT, &constant, sizeof(constant));
	}


	//マテリアル設定
	{
		MATERIAL material{};
		material.BaseColor = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 1.0f };
		material.EmissionColor = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
		renderManager->SetConstant(RenderManager::CONSTANT_TYPE::SUBSET,
			&material, sizeof(material));
	}

	//テクスチャ設定
	renderManager->SetTexture(RenderManager::TEXTURE_TYPE::BASE_COLOR, m_Texture.get());
	renderManager->SetTexture(RenderManager::TEXTURE_TYPE::ARM, m_TextureArm.get());

	m_Model.Draw(false);

}
