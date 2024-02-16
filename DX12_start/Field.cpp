#include "Main.h"
#include "RenderManager.h"
#include <memory>
#include "Field.h"

Field::Field()
{
	RenderManager* rm = RenderManager::GetInstance();

	//read texture
	m_Texture = rm->LoadTexture("Asset\\rusty_metal_02_diff_4k.dds");
	m_TextureArm = rm->LoadTexture("Asset\\rusty_metal_02_arm_4k.dds");

	m_VertexBuffer = rm->CreateVertexBuffer(sizeof(VERTEX_3D), 4);

	//write vertex info
	VERTEX_3D* buffer{};
	HRESULT hr = m_VertexBuffer->Resource->Map(0, nullptr, (void**)&buffer);
	assert(SUCCEEDED(hr));

	buffer[0].Position = { -1.0f,0.0f,1.0f };
	buffer[1].Position = { 1.0f,0.0f,1.0f };
	buffer[2].Position = { -1.0f,0.0f,-1.0f };
	buffer[3].Position = { 1.0f,0.0f,-1.0f };

	//buffer[0].Position = { 0.0f,0.0f,0.0f };
	//buffer[1].Position = { 200.0f,0.0f,0.0f };
	//buffer[2].Position = { 0.0f,200.0f,0.0f };
	//buffer[3].Position = { 200.0f,200.0f,0.0f };

	buffer[0].Color = { 1,1,1,1 };
	buffer[1].Color = { 1,1,1,1 };
	buffer[2].Color = { 1,1,1,1 };
	buffer[3].Color = { 1,1,1,1 };

	buffer[0].Normal = { 0,1,0 };
	buffer[1].Normal = { 0,1,0 };
	buffer[2].Normal = { 0,1,0 };
	buffer[3].Normal = { 0,1,0 };

	buffer[0].TexCoord = { 0,0 };
	buffer[1].TexCoord = { 1,0 };
	buffer[2].TexCoord = { 0,1 };
	buffer[3].TexCoord = { 1,1 };

	m_VertexBuffer->Resource->Unmap(0, nullptr);
}

void Field::Update()
{
}

void Field::Draw()
{
	RenderManager* rm = RenderManager::GetInstance();

	//set light
	if(0)
	{
		ENV_CONSTANT constant{};
		constant.LightDirection.x = 1.0f;
		constant.LightDirection.y = 1.0f;
		constant.LightDirection.z = -1.0f;

		constant.LightColor.x = 3.0f;
		constant.LightColor.y = 3.0f;
		constant.LightColor.z = 3.0f;

		rm->SetConstant(
			RenderManager::CONSTANT_TYPE::ENV,
			&constant,
			sizeof(constant));
	}

	//set matrix
	{
		XMMATRIX world = XMMatrixIdentity();
		OBJECT_CONSTANT constant{};
		XMStoreFloat4x4(&constant.World, XMMatrixTranspose(world));

		rm->SetConstant(RenderManager::CONSTANT_TYPE::OBJECT, &constant, sizeof(constant));
	}

	//set material
	{
		MATERIAL material{};
		material.BaseColor = XMFLOAT4{1, 1, 1, 1};
		rm->SetConstant(RenderManager::CONSTANT_TYPE::SUBSET, &material, sizeof(material));
	}

	//set texture
	rm->SetTexture(RenderManager::TEXTURE_TYPE::BASE_COLOR, m_Texture.get());
	rm->SetTexture(RenderManager::TEXTURE_TYPE::ARM, m_TextureArm.get());

	//set vertex buffer
	rm->SetVertexBuffer(m_VertexBuffer.get());


	//pipeline setting
	//rm->SetPipelineState("Unlit");

	//doboroji setting
	rm->GetGraphicsCommandList()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//draw
	rm->GetGraphicsCommandList()->DrawInstanced(4, 1, 0, 0);
}
