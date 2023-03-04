#include "MoveInCircleComponent.h"
#include "Timer.h"
#include "GameObject.h"

MoveInCircleComponent::MoveInCircleComponent(std::weak_ptr<dae::GameObject> owner, float radius, float rotationSpeed, bool clockWise)
	: Component(owner),
	  m_Radius{ radius },
	  m_AngularSpeed{ rotationSpeed },
	  m_CurrentAngle{ 0.f },
	  m_ClockWise{ clockWise }
{
	glm::vec3 moveDirection{ m_Radius, 0.f, 0.f };

	glm::vec3 newPos{};

	if(m_ClockWise)
		newPos = owner.lock()->GetLocalPos() - moveDirection;
	else
		newPos = owner.lock()->GetLocalPos() + moveDirection;
	
	m_Owner.lock()->SetLocalPosition(newPos.x, newPos.y);
}

void MoveInCircleComponent::Update()
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