#include "ZoomCameraCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

dae::ZoomCameraCommand::ZoomCameraCommand(float zoomSpeed)
	: m_ZoomSpeed{ zoomSpeed }
{
}

void dae::ZoomCameraCommand::Execute()
{
	//get a pointer to the camera by first getting the active scene
	auto pCam{ SceneManager::GetInstance().GetActiveScene()->GetCameraPtr() };

	//check if there is a camera
	if (pCam)
	{
		//if so zoom
		pCam->Zoom(pCam->GetZoom() + m_ZoomSpeed);
	}
}