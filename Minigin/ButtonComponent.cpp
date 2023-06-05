#include "ButtonComponent.h"
#include "InputManager.h"

dae::ButtonComponent::ButtonComponent(dae::GameObject* pOwner, const glm::vec2& topLeftPos, float width, float height, std::function<void()> onClickFunction)
	: Component(pOwner)
	, m_TopLeftPos{ topLeftPos }
	, width{ width }
	, height{ height }
	, m_OnClickFunction{ onClickFunction }
{
	InputManager::GetInstance().AddButton(this);
	pOwner->SetLocalPosition(topLeftPos.x, topLeftPos.y);
}

void dae::ButtonComponent::OnMouseClick(const glm::vec2& mousePos)
{
	if (mousePos.x > m_TopLeftPos.x && mousePos.x < m_TopLeftPos.x + width
		&& mousePos.y > m_TopLeftPos.y && mousePos.y < m_TopLeftPos.y + height)
	{
		m_OnClickFunction();
	}
}