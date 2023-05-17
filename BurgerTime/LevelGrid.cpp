#include "LevelGrid.h"
#include <iostream>

void LevelGrid::AddCell(const glm::vec2& topLeftPos, CellKind cellKind, int rowNr, int collNr)
{
	//calculate the middle
	glm::vec2 middlePos{ topLeftPos.x + m_CellSideLenght / 2.f, topLeftPos.y + m_CellSideLenght / 2.f };

	if (cellKind == CellKind::longEmpty || cellKind == CellKind::longFloor || cellKind == CellKind::longGoDown
		|| cellKind == CellKind::longGoUp || cellKind == CellKind::longGoUpAndDown || cellKind == CellKind::plate)
		middlePos.x += m_CellSideLenght / 2.f;

	m_Cells.push_back(std::make_unique<Cell>(middlePos, cellKind, rowNr, collNr));

	RecalculateGrid();
}

void LevelGrid::RecalculateGrid()
{
	for (auto& pCell : m_Cells)
	{
		for (auto& pOtherCell : m_Cells)
		{
			//make sure the same cell doesn't check himself
			if (pCell == pOtherCell)
				continue;

			float spaceBetweenCellCentersX{ m_CellSideLenght };

			if (pCell->cellKind == CellKind::longEmpty || pCell->cellKind == CellKind::longFloor || pCell->cellKind == CellKind::longGoDown || pCell->cellKind == CellKind::longGoUp || pCell->cellKind == CellKind::longGoUpAndDown || pCell->cellKind == CellKind::plate
				|| pOtherCell->cellKind == CellKind::longEmpty || pOtherCell->cellKind == CellKind::longFloor || pOtherCell->cellKind == CellKind::longGoDown || pOtherCell->cellKind == CellKind::longGoUp || pOtherCell->cellKind == CellKind::longGoUpAndDown || pOtherCell->cellKind == CellKind::plate)
			{
				spaceBetweenCellCentersX = 1.5f * m_CellSideLenght;
			}

			//check if pOtherCell is a top of pCell
			if (CheckForTopNeighbor(pCell.get(), pOtherCell.get()))
			{
				pCell->pTopNeighbor = pOtherCell.get();
				pOtherCell->pBottomNeighbor = pCell.get();
				continue;
			}

			//check if pOtherCell is a rightNeighbor of pCell
			if (CheckForRightNeighbor(pCell.get(), pOtherCell.get(), spaceBetweenCellCentersX))
			{
				pCell->pRightNeighbor = pOtherCell.get();
				pOtherCell->pLeftNeighbor = pCell.get();
			}
		}
	}
}

Cell* LevelGrid::GetCell(const glm::vec2& pos)
{
	//loop over all the cells and check in which one the pos is in
	for (const auto& cell : m_Cells)
	{
		if (pos.y <= cell->middlePos.y + m_CellSideLenght / 2.f
			&& pos.y >= cell->middlePos.y - m_CellSideLenght / 2.f)
		{
			if (cell->cellKind == CellKind::longEmpty || cell->cellKind == CellKind::longFloor || cell->cellKind == CellKind::longGoDown || cell->cellKind == CellKind::longGoUp || cell->cellKind == CellKind::longGoUpAndDown || cell->cellKind == CellKind::plate)
			{
				if (pos.x <= cell->middlePos.x + m_CellSideLenght
					&& pos.x >= cell->middlePos.x - m_CellSideLenght)
					return cell.get();
			}
			else if (pos.x <= cell->middlePos.x + m_CellSideLenght / 2.f
					&& pos.x >= cell->middlePos.x - m_CellSideLenght / 2.f)
				return cell.get();
		}
	}

	return nullptr;
}

bool LevelGrid::CheckForTopNeighbor(Cell* pCell, Cell* pOtherCell)
{
	if (abs(pCell->middlePos.x - pOtherCell->middlePos.x) < m_Epsilon
		&& abs(pCell->middlePos.y - pOtherCell->middlePos.y - m_CellSideLenght) < m_Epsilon)
	{
		return true;
	}

	return false;
}

bool LevelGrid::CheckForRightNeighbor(Cell* pCell, Cell* pOtherCell, float distanceBetweenCellCentersX)
{
	if (abs(pCell->middlePos.x - pOtherCell->middlePos.x + distanceBetweenCellCentersX) < m_Epsilon
		&& abs(pCell->middlePos.y - pOtherCell->middlePos.y) < m_Epsilon)
	{
		return true;
	}

	return false;
}