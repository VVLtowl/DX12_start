#pragma once


#include "RenderManager.h"
#include "Polygon2D.h"
#include "Polygon3D.h"
#include "Field.h"
#include "Camera.h"


class GameManager
{
private:

	static GameManager* m_Instance;

	RenderManager	m_RenderManger;
	Polygon2D m_Polygon2D;
	Polygon3D m_Polygon3D;
	Field m_Field;
	Camera m_Camera;



public:
	static GameManager* GetInstance() { return m_Instance; }

	GameManager();
	~GameManager();



	void Update();
	void Draw();


};

