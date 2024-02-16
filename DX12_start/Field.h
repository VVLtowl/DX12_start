#pragma once

#include <memory>

class Field
{
private:
	XMFLOAT3 m_Position{0,0,0};
	XMFLOAT3 m_Rotation{ 0,0,0 };
	XMFLOAT3 m_Scale{ 0,0,0 };

	std::unique_ptr<VERTEX_BUFFER> m_VertexBuffer;
	std::unique_ptr<TEXTURE> m_Texture;
	std::unique_ptr<TEXTURE> m_TextureArm;

public:
	Field();

	void Update();
	void Draw();
};

