#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include "Singleton.h"

enum class CellKind
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
	plate,
	shortEmpty,
	longEmpty,
};

struct Cell
{
	Cell(const glm::vec2& _middlePos, CellKind _cellKind, int _rowNr, int _collNr)
		: middlePos{ _middlePos }
		, cellKind{ _cellKind }
		, rowNr{ _rowNr }
		, collNr{ _collNr }
	{}

	glm::vec2 middlePos{};

	CellKind cellKind{};

	Cell* pTopNeighbor{ nullptr };
	Cell* pRightNeighbor{ nullptr };
	Cell* pBottomNeighbor{ nullptr };
	Cell* pLeftNeighbor{ nullptr };

	int rowNr{};
	int collNr{};
};

class LevelGrid final : public dae::Singleton<LevelGrid>
{
public:
	void AddCell(const glm::vec2& topLeftPos, CellKind cellKind, int rowNr, int collNr);
	Cell* GetCell(const glm::vec2& pos); //returns the cell where the given pos is in
	float GetCellSideLenght() const { return m_CellSideLenght; }
	void Reset(); //removes all cells

private:
	std::vector<std::unique_ptr<Cell>> m_Cells;
	const float m_CellSideLenght{ 32.f };
	const float m_Epsilon{ 0.1f };

	void RecalculateGrid(); //loops over all the cells and check with each cell if they have a neighbor is so then the pointer in the cell is set to the neighbor
	bool CheckForTopNeighbor(Cell* pCell, Cell* pOtherCell);
	bool CheckForRightNeighbor(Cell* pCell, Cell* pOtherCell, float distanceBetweenCellCentersX);
};