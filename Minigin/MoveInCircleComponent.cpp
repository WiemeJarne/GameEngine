#include "MoveInCircleComponent.h"
#include "Timer.h"
#include "GameObject.h"
#include <iostream>

MoveInCircleComponent::MoveInCircleComponent(std::weak_ptr<dae::GameObject> owner, float radius, float rotationSpeed, bool clockWise)
	: Component(owner),
	  m_Radius{ radius },
	  m_AngularSpeed{ rotationSpeed },
	  m_CurrentAngle{ 0.f },
	  m_ClockWise{ clockWise },
	  m_IsInitialised{ false }
{}

void MoveInCircleComponent::Update()
{
	if (!m_IsInitialised) //this is not done in the contructor because the local position of the owner cann change if it gets a parent
	{
		glm::vec3 moveDirection{ m_Radius, 0.f, 0.f };
	
		glm::vec3 newPos{};
	
		if (m_ClockWise)
		{
			newPos = m_Owner.lock()->GetLocalPos() - moveDirection;
			m_CurrentAngle += m_AngularSpeed * Timer::GetInstance().GetElapsedSec();
		}
			
		else
		{
			newPos = m_Owner.lock()->GetLocalPos() + moveDirection;
			m_CurrentAngle -= m_AngularSpeed * Timer::GetInstance().GetElapsedSec();
		}

		m_Owner.lock()->SetLocalPosition(newPos.x, newPos.y);
		m_IsInitialised = true;
	}
	else
	{
		if (m_ClockWise)
			m_CurrentAngle += m_AngularSpeed * Timer::GetInstance().GetElapsedSec();
		else
			m_CurrentAngle -= m_AngularSpeed * Timer::GetInstance().GetElapsedSec();

		glm::vec3 moveDirection{ std::sin(m_CurrentAngle), -std::cos(m_CurrentAngle), 0.f };
		moveDirection = glm::normalize(moveDirection);
		const float radiusSquared{ std::powf(m_Radius, 2) };
		moveDirection *= glm::sqrt(2 * radiusSquared - 2 * radiusSquared * cos(m_AngularSpeed * Timer::GetInstance().GetElapsedSec()));

		glm::vec3 newPos{};

		newPos = m_Owner.lock()->GetLocalPos() + moveDirection;

		m_Owner.lock()->SetLocalPosition(newPos.x, newPos.y);
	}
}