#include "BurgerPartPrefab.h"
#include "TexturedGameObjectPrefab.h"
#include "BurgerPartComponent.h"
#include "RenderComponent.h"
#include "LevelGrid.h"

BurgerPartPrefab::BurgerPartPrefab(const std::string& textureFilePath, const glm::vec2& cellTopLeftPos)
{
	glm::vec2 pos{ cellTopLeftPos };
	auto texturedGoPrefab{ std::make_unique<TexturedGameObjectPrefab>(textureFilePath, pos) };
	m_go = std::move(texturedGoPrefab->GetGameObject());

	//get the TextureComponent from the RenderComponent
	auto renderComponent{ m_go->GetComponent<RenderComponent>() };
	if (renderComponent)
	{
		pos.y += LevelGrid::GetInstance().GetCellSideLenght() - renderComponent->GetTextureComponent()->GetSize().y;
		m_go->SetLocalPosition(cellTopLeftPos.x, cellTopLeftPos.y);
	}

	m_go->SetLocalPosition(pos.x, pos.y);

	auto burgerPartComponent{ std::make_unique<BurgerPartComponent>(m_go.get(), 75.f) };

	m_go->AddComponent(std::move(burgerPartComponent));
}