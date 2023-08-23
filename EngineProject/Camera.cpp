#include "Camera.h"
#include <iostream>

dae::Camera::Camera(float zoom, int startXPos, int startYPos, bool)
	: m_Zoom{ zoom }
	, m_XPos{ startXPos }
	, m_YPos{ startYPos }
{
}

void dae::Camera::Move(int x, int y)
{
	m_XPos += x;
	m_YPos += y;
}

void dae::Camera::MoveTo(int x, int y)
{
	m_XPos = x;
	m_YPos = y;
}

void dae::Camera::Zoom(float newZoom)
{
	if (newZoom > 0.f)
		m_Zoom = newZoom;

}