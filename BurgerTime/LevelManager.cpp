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
#include "BurgerPartsCollisionManagerComponent.h"

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

	//read the file until the end
	while (!inputFile.eof())
	{
		command = inputFile.get();

		if (command == '\n')
			continue;

		if (command == 'f')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
				platformPos.x += cellSidesLenght * currentCollIndex / 2;

			auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortPlatform.png", platformPos)};
			scene.Add(std::move(platform->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::shortFloor, currentRowIndex, currentCollIndex);
		}
		else if (command == 'u')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
				platformPos.x += cellSidesLenght * currentCollIndex / 2;

			auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortGoUp.png", platformPos)};
			scene.Add(std::move(platform->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::shortGoUp, currentRowIndex, currentCollIndex);
		}
		else if (command == 'd')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
				platformPos.x += cellSidesLenght * currentCollIndex / 2;

			auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortPlatform.png", platformPos) };
			scene.Add(std::move(platform->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::shortGoDown, currentRowIndex, currentCollIndex);
		}
		else if (command == 'b')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };
			
			if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
				platformPos.x += cellSidesLenght * currentCollIndex / 2;

			auto platform{ std::make_unique<TexturedGameObjectPrefab>("shortGoUp.png", platformPos) };
			scene.Add(std::move(platform->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::shortGoUpAndDown, currentRowIndex, currentCollIndex);
		}
		else if (command == 'F')
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
		else if (command == 'U')
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
		else if (command == 'D')
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
		else if (command == 'B')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				platformPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto ladder{ std::make_unique<TexturedGameObjectPrefab>("longGoUp.png", platformPos) };
			scene.Add(std::move(ladder->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::longGoUpAndDown, currentRowIndex, currentCollIndex);
		}
		else if (command == 'l')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
				platformPos.x += cellSidesLenght * currentCollIndex / 2;

			auto platform{ std::make_unique<TexturedGameObjectPrefab>("ladder.png", platformPos) };
			scene.Add(std::move(platform->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::ladder, currentRowIndex, currentCollIndex);
		}
		else if (command == 'L')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x + cellSidesLenght / 2.f, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				platformPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto ladder{ std::make_unique<TexturedGameObjectPrefab>("ladder.png", platformPos) };
			scene.Add(std::move(ladder->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::ladder, currentRowIndex, currentCollIndex);
		}
		else if (command == 'e')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
				platformPos.x += cellSidesLenght * currentCollIndex / 2;

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::shortEmpty, currentRowIndex, currentCollIndex);
		}
		else if (command == 'E')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				platformPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::longEmpty, currentRowIndex, currentCollIndex);
		}
		else if (command == 'p')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
				platformPos.x += cellSidesLenght * currentCollIndex / 2;

			if (currentCollIndex == 0)
			{
				auto platform{ std::make_unique<TexturedGameObjectPrefab>("plateEdgeLeft.png", platformPos) };
				scene.Add(std::move(platform->GetGameObject()));
			}
			else if (currentCollIndex == 8)
			{
				auto platform{ std::make_unique<TexturedGameObjectPrefab>("plateEdgeRight.png", platformPos) };
				scene.Add(std::move(platform->GetGameObject()));
			}
			else
			{
				auto platform{ std::make_unique<TexturedGameObjectPrefab>("plateEdgeLeftAndRight.png", platformPos) };
				scene.Add(std::move(platform->GetGameObject()));
			}
		}
		else if (command == 'P')
		{
			//calculate the pos
			glm::vec2 platformPos{ cellSidesLenght * currentCollIndex + levelTopLeftPos.x, cellSidesLenght * currentRowIndex + levelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				platformPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto ladder{ std::make_unique<TexturedGameObjectPrefab>("plateMiddle.png", platformPos) };
			scene.Add(std::move(ladder->GetGameObject()));

			//add cell to the grid
			LevelGrid::GetInstance().AddCell(platformPos, CellKind::plate, currentRowIndex, currentCollIndex);
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
	glm::vec2 playerPos{ cellSidesLenght * 6 + levelTopLeftPos.x, cellSidesLenght * 8 + levelTopLeftPos.y };
	playerPos.y += cellSidesLenght + 10.f;
	auto player{ std::make_unique<PlayerPrefab>("PeterPepperFrontFacing.png", 3, playerPos) };
	player1 = player->GetGameObject();

	//Get the move component of the player
	auto player1MoveComponent{ player1->GetComponent<MoveComponent>() };

	//read in the ingredients
	filePath = "../Data/level" + std::to_string(levelNr) + "Ingredients.txt";

	inputFile = std::ifstream(filePath);

	if (!inputFile.is_open())
	{
		assert("failed to open level ingredients file");
	}

	currentRowIndex = 0;
	currentCollIndex = 0;

	auto burgerPartCollisionManagerGo{ std::make_unique<dae::GameObject>() };
	auto burgerPartCollisionManagerComponent{ std::make_unique<BurgerPartsCollisionManagerComponent>(burgerPartCollisionManagerGo.get()) };

	while (!inputFile.eof())
	{
		command = inputFile.get();

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

			auto burgerPartComponent{ burgerPartGo->GetComponent<BurgerPartComponent>() };

			player1MoveComponent->AddObserver(burgerPartComponent);

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

			auto burgerPartComponent{ burgerPartGo->GetComponent<BurgerPartComponent>() };

			player1MoveComponent->AddObserver(burgerPartComponent);

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

			auto burgerPartComponent{ burgerPartGo->GetComponent<BurgerPartComponent>() };

			player1MoveComponent->AddObserver(burgerPartComponent);

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

			auto burgerPartComponent{ burgerPartGo->GetComponent<BurgerPartComponent>() };

			player1MoveComponent->AddObserver(burgerPartComponent);

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

			auto burgerPartComponent{ burgerPartGo->GetComponent<BurgerPartComponent>() };

			player1MoveComponent->AddObserver(burgerPartComponent);

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

			auto burgerPartComponent{ burgerPartGo->GetComponent<BurgerPartComponent>() };

			player1MoveComponent->AddObserver(burgerPartComponent);

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
	burgerPartCollisionManagerGo->AddComponent(std::move(burgerPartCollisionManagerComponent));
	scene.Add(std::move(burgerPartCollisionManagerGo));
}