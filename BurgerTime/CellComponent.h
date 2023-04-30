#pragma once
#include "Component.h"
#include <glm/vec2.hpp>

class CellComponent final : public Component
{
public:
	enum class CellType
	{
		shortFloor,
		shortGoUp,
		shortGoDown,
		shortGoUpAndDown,
		longFloor,
		longGoUp,
		longGoDown,
		longGoUpAndDown,
		ladder,
		plateEdge,
		plate,
		empty
	};

	CellComponent(const glm::vec2& pos, int rowNr, int colNr, CellType tileType);

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	
	int GetHeight() const { return m_Height; }

private:
	int m_RowNr{};
	int m_ColNr{};

	CellType m_TileType{};

	float m_Height{};

	glm::vec2 pos{};
};