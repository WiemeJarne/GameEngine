#pragma once
namespace dae
{
	class Camera final
	{
	public:
		//zoom: for example when this is 2 the textures/text will be 2 times as large, zoom can never be 0 or smaller when 0 or smaller is given to zoom will be set to 1
		Camera(float zoom, int startXPos = 0, int startYPos = 0, bool addMoveCommandsToActiveScene = true);

		Camera(const Camera& other) = delete;
		Camera& operator=(const Camera& other) = delete;
		Camera(Camera&& other) = delete;
		Camera& operator=(Camera&& other) = delete;

		//moves the camera with the given amount
		void Move(int x, int y);
		//this sets the position of the camera, the camera will move instantly to the given location (teleport)
		void MoveTo(int x, int y);
		void Zoom(float newZoom);
		float GetZoom() const { return m_Zoom; }
		int GetXPos() const { return m_XPos; }
		int GetYPos() const { return m_YPos; }

	private:
		float m_Zoom{};
		int m_XPos{};
		int m_YPos{};
	};
}