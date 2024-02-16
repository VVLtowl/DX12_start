#include "Main.h"
#include "RenderManager.h"
#include <memory>
#include "Polygon2D.h"
Polygon2D::Polygon2D()
{
	RenderManager* rm = RenderManager::GetInstance();

	//read texture
	m_Texture = rm->LoadTexture("Asset\\field004.dds");

	m_VertexBuffer = rm->CreateVertexBuffer(sizeof(VERTEX_3D), 4);

	//write vertex info
	VERTEX_3D* buffer{};
	HRESULT hr = m_VertexBuffer->Resource->Map(0, nullptr, (void**)&buffer);
	assert(SUCCEEDED(hr));

	buffer[0].Position = { 0.0f,0.0f,0.0f };
	buffer[1].Position = { 200.0f,0.0f,0.0f };
	buffer[2].Position = { 0.0f,200.0f,0.0f };
	buffer[3].Position = { 200.0f,200.0f,0.0f };

	buffer[0].Color = { 1,1,1,1 };
	buffer[1].Color = { 1,1,1,1 };
	buffer[2].Color = { 1,1,1,1 };
	buffer[3].Color = { 1,1,1,1 };

	buffer[0].Normal = { 0,1,0 };
	buffer[1].Normal = { 0,1,0 };
	buffer[2].Normal = { 0,1,0 };
	buffer[3].Normal = { 0,1,0 };

	buffer[0].TexCoord = { 0,0};
	buffer[1].TexCoord = { 1,0};
	buffer[2].TexCoord = { 0,1};
	buffer[3].TexCoord = { 1,1};

	m_VertexBuffer->Resource->Unmap(0, nullptr);
}

void Polygon2D::Update()
{
}

void Polygon2D::Draw()
{
	RenderManager* rm = RenderManager::GetInstance();

	//set matrix
	{
		XMMATRIX world = XMMatrixIdentity();
		OBJECT_CONSTANT constant{};
		XMStoreFloat4x4(&constant.World, XMMatrixTranspose(world));

		rm->SetConstant(RenderManager::CONSTANT_TYPE::OBJECT, &constant, sizeof(constant));
	}

	//set texture
	rm->SetTexture(RenderManager::TEXTURE_TYPE::BASE_COLOR,m_Texture.get());

	//set vertex buffer
	rm->SetVertexBuffer(m_VertexBuffer.get());

	//piprline setting
	//rm->SetPipelineState("Unlit");

	//doboroji setting
	rm->GetGraphicsCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//draw
	rm->GetGraphicsCommandList()->DrawInstanced(4, 1, 0, 0);
}
