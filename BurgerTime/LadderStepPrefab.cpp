#include "LadderStepPrefab.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "LadderCollisionComponent.h"

LadderStepPrefab::LadderStepPrefab(glm::vec2 pos)
{
	m_go = std::make_unique<dae::GameObject>();

	m_go->SetLocalPosition(pos.x, pos.y);

	auto renderComponent{ std::make_unique<RenderComponent>(m_go.get(), "ladderStep.png") };
	m_go->AddComponent(std::move(renderComponent));

	auto ladderCollisionComponent{ std::make_unique<LadderCollisionComponent>(m_go.get()) };
	m_go->AddComponent(std::move(ladderCollisionComponent));
}