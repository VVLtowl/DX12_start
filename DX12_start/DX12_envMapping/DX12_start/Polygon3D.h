#pragma once

#include "model.h"

class Polygon3D
{
private:
	XMFLOAT3 m_Position{ 0,0,0 };
	XMFLOAT3 m_Rotation{ 0,0,0 };
	XMFLOAT3 m_Scale{ 0,0,0 };

	Model m_Model;
	std::unique_ptr<TEXTURE> m_TextureArm;

public:
	Polygon3D();
	void Update();
	void Draw();
};

