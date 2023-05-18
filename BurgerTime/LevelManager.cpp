#include "LevelManager.h"
#include <fstream>
#include <cassert>
#include "PlatePrefab.h"
#include "PlayerPrefab.h"
#include "LevelGrid.h"
#include "TexturedGameObjectPrefab.h"
#include "MoveComponent.h"
#include "BurgerPartComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "BurgerPartPrefab.h"

void LevelManager::LoadLevel(int levelNr, dae::Scene& scene)
{
	//open the input file
	std::string filePath{ "../Data/level" + std::to_string(levelNr) + ".txt" };
	std::ifstream inputFile{ filePath };

	if (!inputFile.is_open())
	{
		assert("failed to open level file");
	}

	char command{};

	std::unique_ptr<dae::GameObject> player1{};
	const float cellSidesLenght{ LevelGrid::GetInstance().GetCellSideLenght() };

	int currentRowIndex{};
	int currentCollIndex{};
	const glm::vec2 levelTopLeftPos{ 0.f, 32.f };

	int playerStartRow{};
	int playerStartColumn{};

	//read the file until the end
	while (!inputFile.eof())
	{
		command = static_cast<char>(inputFile.get());

		if (command == '\n')
			continue;

		if (std::isupper(command))
		{
			playerStartRow = currentRowIndex;
			playerStartColumn = currentCollIndex;
			command = static_cast<char>(std::tolower(command));
		}

		if (command == 'f')
		{
			if (currentCollIndex % 2 == 0)
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
					cellPos.x += cellSidesLenght * currentCollIndex / 2;

				auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortPlatform.png", cellPos) };
				scene.Add(std::move(platform->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::shortFloor, currentRowIndex, currentCollIndex);
			}
			else
			{
				//calculate the pos
				glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
					platformPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

				auto ladder{ std::make_unique<TexturedGameObjectPrefab>("longPlatform.png", platformPos) };
				scene.Add(std::move(ladder->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(platformPos, CellKind::longFloor, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'u')
		{
			if (currentCollIndex % 2 == 0)
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
					cellPos.x += cellSidesLenght * currentCollIndex / 2;

				auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortGoUp.png", cellPos) };
				scene.Add(std::move(platform->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::shortGoUp, currentRowIndex, currentCollIndex);
			}
			else
			{
				//calculate the pos
				glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
					platformPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

				auto ladder{ std::make_unique<TexturedGameObjectPrefab>("longGoUp.png", platformPos) };
				scene.Add(std::move(ladder->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(platformPos, CellKind::longGoUp, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'd')
		{
			if (currentCollIndex % 2 == 0)
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
					cellPos.x += cellSidesLenght * currentCollIndex / 2;

				auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortPlatform.png", cellPos) };
				scene.Add(std::move(platform->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::shortGoDown, currentRowIndex, currentCollIndex);
			}
			else
			{
				//calculate the pos
				glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
					platformPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

				auto ladder{ std::make_unique<TexturedGameObjectPrefab>("longPlatform.png", platformPos) };
				scene.Add(std::move(ladder->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(platformPos, CellKind::longGoDown, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'b')
		{
			if (currentCollIndex % 2 == 0)
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
					cellPos.x += cellSidesLenght * currentCollIndex / 2;

				auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortGoUp.png", cellPos) };
				scene.Add(std::move(platform->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::shortGoUpAndDown, currentRowIndex, currentCollIndex);
			}
			else
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
					cellPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

				auto ladder{ std::make_unique<TexturedGameObjectPrefab>("longGoUp.png", cellPos) };
				scene.Add(std::move(ladder->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::longGoUpAndDown, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'l')
		{
			if (currentCollIndex % 2 == 0)
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
					cellPos.x += cellSidesLenght * currentCollIndex / 2;

				auto platform{ std::make_unique<TexturedGameObjectPrefab>("ladder.png", cellPos) };
				scene.Add(std::move(platform->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::ladder, currentRowIndex, currentCollIndex);
			}
			else
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x + cellSidesLenght / 2.f, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
					cellPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

				auto ladder{ std::make_unique<TexturedGameObjectPrefab>("ladder.png", cellPos) };
				scene.Add(std::move(ladder->GetGameObject()));

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::ladder, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'e')
		{
			if (currentCollIndex % 2 == 0)
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
					cellPos.x += cellSidesLenght * currentCollIndex / 2;

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::shortEmpty, currentRowIndex, currentCollIndex);
			}
			else
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

				if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
					cellPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

				//add cell to the grid
				LevelGrid::GetInstance().AddCell(cellPos, CellKind::longEmpty, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'p')
		{
			//calculate the pos
			glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto plate{ std::make_unique<TexturedGameObjectPrefab>("plateMiddle.png", cellPos) };
			scene.Add(std::move(plate->GetGameObject()));

			glm::vec2 leftPlateEdgePos{ cellPos };
			leftPlateEdgePos.x -= cellSidesLenght / 2.f;
			auto leftPlateEdge{ std::make_unique<TexturedGameObjectPrefab>("plateEdgeLeft.png", leftPlateEdgePos) };
			scene.Add(std::move(leftPlateEdge->GetGameObject()));

			glm::vec2 rightPlateEdgePos{ cellPos };
			rightPlateEdgePos.x += cellSidesLenght * 2.f;
			auto rightPlateEdge{ std::make_unique<TexturedGameObjectPrefab>("plateEdgeRight.png", rightPlateEdgePos) };
			scene.Add(std::move(rightPlateEdge->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(cellPos, CellKind::plate, currentRowIndex, currentCollIndex);
		}
		
		++currentCollIndex;
		if (currentCollIndex == 9)
		{
			currentCollIndex = 0;
			++currentRowIndex;
		}	
	}

	inputFile.close();

	//spawn player at row 8 collumn 5
	glm::vec2 playerPos{ 1.5 * cellSidesLenght * playerStartColumn + 8.f, cellSidesLenght * playerStartRow };
	playerPos.y += cellSidesLenght + 10.f;
	auto player{ std::make_unique<PlayerPrefab>("PeterPepperFrontFacing.png", 3, playerPos) };
	player1 = player->GetGameObject();

	//read in the ingredients
	filePath = "../Data/level" + std::to_string(levelNr) + "Ingredients.txt";

	inputFile = std::ifstream(filePath);

	if (!inputFile.is_open())
	{
		assert("failed to open level ingredients file");
	}

	currentRowIndex = 0;
	currentCollIndex = 0;

	while (!inputFile.eof())
	{
		command = static_cast<char>(inputFile.get());

		if (command == '\n')
			continue;

		if (command == 'T')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>("bunTop.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			scene.Add(std::move(burgerPartGo));
		}
		if (command == 'l')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>("lettuce.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			scene.Add(std::move(burgerPartGo));
		}
		if (command == 't')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>("tomato.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			scene.Add(std::move(burgerPartGo));
		}
		if (command == 'c')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>("cheese.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			scene.Add(std::move(burgerPartGo));
		}
		if (command == 'p')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>("patty.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			scene.Add(std::move(burgerPartGo));
		}
		if (command == 'b')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>("bunBottom.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			scene.Add(std::move(burgerPartGo));
		}

		++currentCollIndex;
		if (currentCollIndex == 9)
		{
			currentCollIndex = 0;
			++currentRowIndex;
		}
	}

	scene.Add(std::move(player1));
}