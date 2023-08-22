#include "MoveCameraCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

dae::MoveCameraCommand::MoveCameraCommand(const glm::vec2& direction, float moveSpeed)
	: m_Direction{ direction }
	, m_MoveSpeed{ moveSpeed }
{
}

void dae::MoveCameraCommand::Execute()
{
	//get a pointer to the camera by first getting the active scene
	auto pCam{ SceneManager::GetInstance().GetActiveScene()->GetCameraPtr() };

	//check if there is a camera
	if (pCam)
	{
		//if so move it
		pCam->Move(static_cast<int>(m_Direction.x * m_MoveSpeed), static_cast<int>(m_Direction.y * m_MoveSpeed));
	}
}