

#include "Main.h"
#include "GameManager.h"




GameManager* GameManager::m_Instance = nullptr;





GameManager::GameManager()
{
	m_Instance = this;


}




GameManager::~GameManager()
{
	m_RenderManger.WaitGPU();
}





void GameManager::Update()
{
	m_Polygon2D.Update(); 
	m_Field.Update();
	m_Polygon3D.Update();
	m_Sky.Update();
	m_Camera.Update();
}




void GameManager::Draw()
{
	m_RenderManger.DrawBegin();


	m_Camera.Set3DView();


	m_Field.Draw();
	

	m_Sky.Draw();
	m_Polygon3D.Draw();





	//m_Camera.Set2DView();
	//m_Polygon2D.Draw();

	m_RenderManger.DrawEnd();

}


