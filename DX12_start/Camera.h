#pragma once
class Camera
{
public:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Target;
	XMFLOAT3 m_Up;

	float m_RotAng;

public:
	Camera();
	void Update();
	void Set3DView();
	void Set2DView();
};

