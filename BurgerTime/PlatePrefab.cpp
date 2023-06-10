#include "PlatePrefab.h"
#include "GameObject.h"
#include "RenderComponent.h"

PlatePrefab::PlatePrefab(dae::Scene* pScene, glm::vec2 pos)
{
	m_go = std::make_unique<dae::GameObject>(pScene);

	m_go->SetLocalPosition(pos.x, pos.y);

	auto renderComponent{ std::make_unique<dae::RenderComponent>(m_go.get(), "plate.png") };
	m_go->AddComponent(std::move(renderComponent));
}