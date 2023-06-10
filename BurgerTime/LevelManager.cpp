#include "LevelManager.h"
#include <fstream>
#include <cassert>
#include "PlatePrefab.h"
#include "PlayerPrefab.h"
#include "LevelGrid.h"
#include "TexturedGameObjectPrefab.h"
#include "BurgerPartComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "BurgerPartPrefab.h"
#include "EnemyManager.h"
#include "PointsComponent.h"
#include "Events.h"
#include "EventQueue.h"
#include "InputManager.h"
#include "TypeComponent.h"
#include "ResourceManager.h"
#include "DamageComponent.h"
#include "SkipLevelCommand.h"
#include <algorithm>
#include <iostream>

LevelManager::~LevelManager()
{
	WriteHighScoreListToFile();
}

void LevelManager::LoadLevel(int levelNr, dae::Scene& scene, GameMode gameMode)
{
	assert(levelNr > 0 && "ERROR LoadLevel called with levelNr lower then 1");

	if (!m_HasBeenInitialized)
	{
		m_HasBeenInitialized = true;
		dae::EventQueue::GetInstance().AddListener(this);
	}

	dae::InputManager::GetInstance().RemoveAllButtons();
	dae::InputManager::GetInstance().RemoveAllCommandsAndControlers();

	m_LevelNr = levelNr;
	m_GameMode = gameMode;

	if (m_pPointsComponent)
	{
		m_AmountOfPoints = m_pPointsComponent->GetPoints();
		m_pPointsComponent = nullptr;
	}

	dae::SceneManager::GetInstance().RemoveScene(&scene);

	auto& levelScene = dae::SceneManager::GetInstance().CreateScene("levelScene");
	m_CurrentScene = &levelScene;

	bool couldLoadLevel{};

	if (m_LevelGrids.size() < levelNr)
	{
		couldLoadLevel = LoadLevelPlatforms(levelNr);
	}
	else
	{
		const auto levelGridCells{ std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetCells() };

		for (const auto& cell : levelGridCells)
		{
			AddLevelElementToCurrentScene(cell->cellKind, cell->collNr, cell->rowNr);
		}

		couldLoadLevel = true;
	}

	if (!couldLoadLevel)
	{
		ShowPointsScreen();
		return;
	}
	
	LoadLevelBurgerParts(levelNr);

	auto skipLevelCommand = std::make_unique<commands::SkipLevelCommand>();
	dae::InputManager::GetInstance().AddCommand(std::move(skipLevelCommand), dae::KeyState::down, dae::InputManager::KeyboardKey::F1);

	if (m_EnemiesSpawnLocations.empty())
	{
		const float cellSideLenght{ std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetCellSideLenght() };
		m_EnemiesSpawnLocations.push_back({ -cellSideLenght, m_LevelTopLeftPos.y + cellSideLenght });
		m_EnemiesSpawnLocations.push_back({ cellSideLenght * (std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetAmountOfRows() + 1), m_LevelTopLeftPos.y + cellSideLenght});
	}

	auto enemyManager{ std::make_unique<dae::GameObject>(m_CurrentScene) };
	enemyManager->AddComponent(std::make_unique<EnemyManagerComponent>(enemyManager.get(), m_CurrentScene, m_EnemiesSpawnLocations, 2, 2, 2));

	const float cellSidesLenght{ std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetCellSideLenght() };

	levelScene.Add(std::move(enemyManager));

	//create point screen
	auto pointScreen{ std::make_unique<dae::GameObject>(m_CurrentScene) };
	auto pointsComponent{ std::make_unique<PointsComponent>(pointScreen.get(), glm::vec2(dae::SceneManager::GetInstance().GetScenesWidth() / 2.f, 10.f)) };
	pointsComponent->AddPoints(m_AmountOfPoints);
	m_pPointsComponent = pointsComponent.get();
	pointScreen->AddComponent(std::move(pointsComponent));
	levelScene.Add(std::move(pointScreen));

	//create player 1
	glm::vec2 playerPos{ 1.5f * cellSidesLenght * std::get<1>(m_LevelGrids[m_LevelNr - 1]), cellSidesLenght * std::get<2>(m_LevelGrids[m_LevelNr - 1]) - 16.f };
	playerPos.y += cellSidesLenght + 10.f;
	auto player1{ std::make_unique<PlayerPrefab>(m_CurrentScene, "PeterPepperFrontFacing.png", playerPos, glm::vec2(0.f, 0.f), "PeterPepperHead.png")->GetGameObject()};
	levelScene.Add(std::move(player1));
	
	std::unique_ptr<dae::GameObject> player2{};

	switch (gameMode)
	{
	case GameMode::coOp:
		playerPos = { 1.5f * cellSidesLenght * std::get<1>(m_LevelGrids[m_LevelNr - 1]) + 16.f, cellSidesLenght * std::get<2>(m_LevelGrids[m_LevelNr - 1]) - 16.f };
		playerPos.y += cellSidesLenght + 10.f;
		player2 = std::make_unique<PlayerPrefab>(m_CurrentScene, "MrsSalt.png",playerPos, glm::vec2(dae::SceneManager::GetInstance().GetScenesWidth() - 60.f, 0.f), "PeterPepperHead.png", 3, false)->GetGameObject();
		levelScene.Add(std::move(player2));
		break;

	case GameMode::versus:

		//find the first cell that is not empty, a ladder or a plate. this is the cell where the second player will spawn
		Cell* cell{};

		int colNr{};
		int rowNr{};
		const int maxAmountOfCollumns{ std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetMaxAmountOfCollumns() };

		while (true)
		{
			cell = std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetCell(colNr, rowNr);

			if (cell && cell->cellKind != CellKind::shortEmpty && cell->cellKind != CellKind::longEmpty && cell->cellKind != CellKind::ladder && cell->cellKind != CellKind::plate)
				break;

			++colNr;

			if (colNr > maxAmountOfCollumns)
			{
				++rowNr;
				colNr = 0;
			}
		}

		playerPos = { 1.5f * cellSidesLenght * colNr + 16.f, cellSidesLenght * rowNr };
		playerPos.y += cellSidesLenght + 10.f;
		player2 = std::make_unique<PlayerPrefab>(m_CurrentScene, "MrHotDog.png", playerPos, glm::vec2(dae::SceneManager::GetInstance().GetScenesWidth() - 30.f, dae::SceneManager::GetInstance().GetScenesHeight() - 10.f), "PeterPepperHead.png", 3, false)->GetGameObject();
		player2->AddComponent(std::make_unique<DamageComponent>(player2.get(), 1));
		levelScene.Add(std::move(player2));
		break;
	}
	
}

void LevelManager::LoadNextLevel()
{
	LoadLevel(m_LevelNr + 1, *m_CurrentScene, m_GameMode);
}

void LevelManager::OnNotify(std::any data, int eventId, bool isEngineEvent)
{
	if (isEngineEvent)
		return;

	Event event{ static_cast<Event>(eventId) };

	switch (event)
	{
	case Event::burgerPartReachedPlate:
		++m_AmountOfBurgerParsReachedPlate;
		if (m_AmountOfBurgerParsReachedPlate == m_AmountOfBurgerPartsInCurrentLevel)
		{
			++m_LevelNr;

			dae::InputManager::GetInstance().RemoveAllCommandsAndControlers();
			LoadLevel(m_LevelNr, *m_CurrentScene, m_GameMode);
		}
		break;

	case Event::playerDied:
		++m_AmountOfPlayersDead;

		switch (m_GameMode)
		{
		case GameMode::singlePlayer:
		case GameMode::versus:
			ShowPointsScreen();
			m_AmountOfPlayersDead = 0;
			break;

		case GameMode::coOp:
			if (m_AmountOfPlayersDead == 2)
			{
				ShowPointsScreen();
				m_AmountOfPlayersDead = 0;
			}
			break;
		}
	}
}

LevelGrid* LevelManager::GetActiveLevelGrid() const
{ 
	assert(m_LevelGrids.size() != 0 && "GetActiveLevelGrid being called when there arn't any level grids");

	return std::get<0>(m_LevelGrids[m_LevelNr - 1]).get();
}

bool LevelManager::LoadLevelPlatforms(int levelNr)
{
	//open the input file
	std::string filePath{ "../Data/level" + std::to_string(levelNr) + ".txt" };
	std::ifstream inputFile{ filePath };

	if (!inputFile.is_open())
		return false;

	char command{};

	m_LevelGrids.push_back(std::make_tuple(std::make_unique<LevelGrid>(), 0, 0));

	const float cellSidesLenght{ std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetCellSideLenght() };

	int currentRowIndex{};
	int currentCollIndex{};

	//read the file until the end
	while (!inputFile.eof())
	{
		command = static_cast<char>(inputFile.get());

		if (command == '\n')
			continue;

		if (std::isupper(command))
		{
			std::get<1>(m_LevelGrids[m_LevelNr - 1]) = currentCollIndex;
			std::get<2>(m_LevelGrids[m_LevelNr - 1]) = currentRowIndex;
			command = static_cast<char>(std::tolower(command));
		}

		if (command == 'f')
		{
			if (currentCollIndex % 2 == 0)
			{
				glm::vec2 cellPos{ AddLevelElementToCurrentScene(CellKind::shortFloor, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::shortFloor, currentRowIndex, currentCollIndex);
			}
			else
			{
				glm::vec2 platformPos{ AddLevelElementToCurrentScene(CellKind::longFloor, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(platformPos, CellKind::longFloor, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'u')
		{
			if (currentCollIndex % 2 == 0)
			{
				glm::vec2 cellPos{ AddLevelElementToCurrentScene(CellKind::shortGoUp, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::shortGoUp, currentRowIndex, currentCollIndex);
			}
			else
			{
				glm::vec2 platformPos{ AddLevelElementToCurrentScene(CellKind::longGoUp, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(platformPos, CellKind::longGoUp, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'd')
		{
			if (currentCollIndex % 2 == 0)
			{
				glm::vec2 cellPos{ AddLevelElementToCurrentScene(CellKind::shortGoDown, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::shortGoDown, currentRowIndex, currentCollIndex);
			}
			else
			{
				glm::vec2 platformPos{ AddLevelElementToCurrentScene(CellKind::longGoDown, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(platformPos, CellKind::longGoDown, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'b')
		{
			if (currentCollIndex % 2 == 0)
			{
				glm::vec2 cellPos{ AddLevelElementToCurrentScene(CellKind::shortGoUpAndDown, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::shortGoUpAndDown, currentRowIndex, currentCollIndex);
			}
			else
			{
				glm::vec2 cellPos{ AddLevelElementToCurrentScene(CellKind::longGoUpAndDown, currentCollIndex, currentRowIndex) };

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::longGoUpAndDown, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'l')
		{
			glm::vec2 cellPos{ AddLevelElementToCurrentScene(CellKind::ladder, currentCollIndex, currentRowIndex) };

			//add cell to the grid
			std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::ladder, currentRowIndex, currentCollIndex);
		}
		else if (command == 'e')
		{
			if (currentCollIndex % 2 == 0)
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

				if (currentCollIndex % 2 == 0 && currentCollIndex != 0)
					cellPos.x += cellSidesLenght * currentCollIndex / 2;

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::shortEmpty, currentRowIndex, currentCollIndex);
			}
			else
			{
				//calculate the pos
				glm::vec2 cellPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

				if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
					cellPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

				//add cell to the grid
				std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::longEmpty, currentRowIndex, currentCollIndex);
			}
		}
		else if (command == 'p')
		{
			glm::vec2 cellPos{ AddLevelElementToCurrentScene(CellKind::plate, currentCollIndex, currentRowIndex) };

			//add cell to the grid
			std::get<0>(m_LevelGrids[m_LevelNr - 1])->AddCell(cellPos, CellKind::plate, currentRowIndex, currentCollIndex);
		}

		++currentCollIndex;
		if (currentCollIndex == 9)
		{
			currentCollIndex = 0;
			++currentRowIndex;
		}
	}

	inputFile.close();

	return true;
}

void LevelManager::LoadLevelBurgerParts(int levelNr)
{
	std::string filePath{ "../Data/level" + std::to_string(levelNr) + "Ingredients.txt" };
	std::ifstream inputFile{ filePath };

	if (!inputFile.is_open())
	{
		assert("failed to open level ingredients file");
	}

	int currentRowIndex = 0;
	int currentCollIndex = 0;

	const float cellSidesLenght{ std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetCellSideLenght() };

	char command{};

	while (!inputFile.eof())
	{
		command = static_cast<char>(inputFile.get());

		if (command == '\n')
			continue;

		if (command == 'T')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>(m_CurrentScene, "bunTop.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			m_CurrentScene->Add(std::move(burgerPartGo));

			++m_AmountOfBurgerPartsInCurrentLevel;
		}
		if (command == 'l')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>(m_CurrentScene, "lettuce.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			m_CurrentScene->Add(std::move(burgerPartGo));

			++m_AmountOfBurgerPartsInCurrentLevel;
		}
		if (command == 't')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>(m_CurrentScene, "tomato.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			m_CurrentScene->Add(std::move(burgerPartGo));

			++m_AmountOfBurgerPartsInCurrentLevel;
		}
		if (command == 'c')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>(m_CurrentScene, "cheese.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			m_CurrentScene->Add(std::move(burgerPartGo));

			++m_AmountOfBurgerPartsInCurrentLevel;
		}
		if (command == 'p')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>(m_CurrentScene, "patty.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			m_CurrentScene->Add(std::move(burgerPartGo));

			++m_AmountOfBurgerPartsInCurrentLevel;
		}
		if (command == 'b')
		{
			//calculate the pos
			glm::vec2 cellTopLeftPos{ cellSidesLenght * currentCollIndex + m_LevelTopLeftPos.x, cellSidesLenght * currentRowIndex + m_LevelTopLeftPos.y };

			if (currentCollIndex % 2 == 1 && currentCollIndex != 1)
				cellTopLeftPos.x += cellSidesLenght * (currentCollIndex - 1) / 2;

			auto burgerPartPrefab{ std::make_unique<BurgerPartPrefab>(m_CurrentScene, "bunBottom.png", cellTopLeftPos) };
			auto burgerPartGo{ std::move(burgerPartPrefab->GetGameObject()) };

			m_CurrentScene->Add(std::move(burgerPartGo));

			++m_AmountOfBurgerPartsInCurrentLevel;
		}

		++currentCollIndex;
		if (currentCollIndex == 9)
		{
			currentCollIndex = 0;
			++currentRowIndex;
		}
	}
}

const glm::vec2 LevelManager::AddLevelElementToCurrentScene(CellKind cellKind, int colNr, int rowNr)
{
	const float cellSidesLenght{ std::get<0>(m_LevelGrids[m_LevelNr - 1])->GetCellSideLenght() };

	glm::vec2 cellPos{};

	switch (cellKind)
	{
	case CellKind::shortFloor:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 0 && colNr != 0)
			cellPos.x += cellSidesLenght * colNr / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "shortPlatform.png", cellPos)->GetGameObject());

		return cellPos;

	case CellKind::shortGoUp:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 0 && colNr != 0)
			cellPos.x += cellSidesLenght * colNr / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "shortGoUp.png", cellPos)->GetGameObject());
		
		return cellPos;

	case CellKind::shortGoDown:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 0 && colNr != 0)
			cellPos.x += cellSidesLenght * colNr / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "shortPlatform.png", cellPos)->GetGameObject());

		return cellPos;

	case CellKind::shortGoUpAndDown:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 0 && colNr != 0)
			cellPos.x += cellSidesLenght * colNr / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "shortGoUp.png", cellPos)->GetGameObject());

		return cellPos;

	case CellKind::longFloor:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 1 && colNr != 1)
			cellPos.x += cellSidesLenght * (colNr - 1) / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "longPlatform.png", cellPos)->GetGameObject());

		return cellPos;

	case CellKind::longGoUp:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 1 && colNr != 1)
			cellPos.x += cellSidesLenght * (colNr - 1) / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "longGoUp.png", cellPos)->GetGameObject());

		return cellPos;

	case CellKind::longGoDown:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 1 && colNr != 1)
			cellPos.x += cellSidesLenght * (colNr - 1) / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "longPlatform.png", cellPos)->GetGameObject());

		return cellPos;

	case CellKind::longGoUpAndDown:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 1 && colNr != 1)
			cellPos.x += cellSidesLenght * (colNr - 1) / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "longGoUp.png", cellPos)->GetGameObject());
		
		return cellPos;

	case CellKind::ladder:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		cellPos.x += cellSidesLenght * colNr / 2;

		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "ladder.png", cellPos)->GetGameObject());

		return cellPos;

	case CellKind::plate:
		cellPos = { cellSidesLenght * colNr + m_LevelTopLeftPos.x, cellSidesLenght * rowNr + m_LevelTopLeftPos.y };

		if (colNr % 2 == 1 && colNr != 1)
			cellPos.x += cellSidesLenght * (colNr - 1) / 2;

		//add the plate
		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "plateMiddle.png", cellPos)->GetGameObject());

		//add the leftPlateEdge
		glm::vec2 leftPlateEdgePos{ cellPos };
		leftPlateEdgePos.x -= cellSidesLenght / 2.f;
		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "plateEdgeLeft.png", leftPlateEdgePos)->GetGameObject());

		//add the rightPlateEdge
		glm::vec2 rightPlateEdgePos{ cellPos };
		rightPlateEdgePos.x += cellSidesLenght * 2.f;
		m_CurrentScene->Add(std::make_unique<TexturedGameObjectPrefab>(m_CurrentScene, "plateEdgeRight.png", rightPlateEdgePos)->GetGameObject());
		
		return cellPos;
	}

	return {};
}

void LevelManager::ShowPointsScreen()
{
	if (m_pPointsComponent)
	{
		m_AmountOfPoints = m_pPointsComponent->GetPoints();
		m_pPointsComponent = nullptr;
	}

	dae::SceneManager::GetInstance().RemoveScene(m_CurrentScene);

	auto& levelScene = dae::SceneManager::GetInstance().CreateScene("levelScene");
	m_CurrentScene = &levelScene;

	dae::InputManager::GetInstance().RemoveAllButtons();
	dae::InputManager::GetInstance().RemoveAllCommandsAndControlers();

	if (!m_Font)
		m_Font = dae::ResourceManager::GetInstance().LoadFont("PressStart2P-vaV7.ttf", 15u);

	auto& sceneManager{ dae::SceneManager::GetInstance() };
	const auto sceneWidth{ sceneManager.GetScenesWidth() };
	const auto sceneHeight{ sceneManager.GetScenesHeight() };

	if (m_HighScoreList.size() == 0)
	{
		//read in the highScoreList
		std::ifstream inputFile{ "../Data/highScoreList.txt" };

		std::string name{};
		std::string score{};

		while (!inputFile.eof() && m_HighScoreList.size() < 5)
		{
			std::getline(inputFile, name);

			if (name == "")
				break;

			std::getline(inputFile, score);
			m_HighScoreList.push_back({ name, std::stoi(score) });
		}

		SortHighScoreList();
	}

	bool isCurrentScoreHighScore{};
	for (int index{}; index < m_HighScoreList.size(); ++index)
	{
		auto scoreObject{ std::make_unique<dae::GameObject>(m_CurrentScene) };
		scoreObject->AddComponent(std::make_unique<dae::TextComponent>(scoreObject.get(), m_HighScoreList[index].first + ' ' + std::to_string(m_HighScoreList[index].second), m_Font));
		auto textureSize{ scoreObject->GetComponent<dae::RenderComponent>()->GetTextureComponent()->GetSize() };
		scoreObject->SetLocalPosition(sceneWidth / 2.f - textureSize.x / 2.f, 75.f + index * 50.f);
		m_CurrentScene->Add(std::move(scoreObject));

		if (m_HighScoreList[index].second < m_AmountOfPoints)
			isCurrentScoreHighScore = true;
	}

	if (m_HighScoreList.size() == 0)
		isCurrentScoreHighScore = true;

	dae::TextComponent* pTextComponent{};

	if (isCurrentScoreHighScore) //the player can only type in there name when their score is in the top 5
	{
		//add object so the player can type in his name
		auto typeObject{ std::make_unique<dae::GameObject>(m_CurrentScene) };
		typeObject->AddComponent(std::make_unique<TypeComponent>(typeObject.get(), m_Font));
		auto textureSize{ typeObject->GetComponent<dae::RenderComponent>()->GetTextureComponent()->GetSize() };
		typeObject->SetLocalPosition(sceneWidth / 2.f - textureSize.x / 2.f, sceneHeight - 75.f);
		pTextComponent = typeObject->GetComponent<dae::TextComponent>();
		m_CurrentScene->Add(std::move(typeObject));
	}

	//add a button to continue
	auto continueButton{ std::make_unique<dae::GameObject>(m_CurrentScene) };
	continueButton->AddComponent(std::make_unique<dae::TextComponent>(continueButton.get(), "Replay?", m_Font));
	auto onContinueButtonClick =
		[=]()
	{
		if (pTextComponent)
		{
			auto givenName{ pTextComponent->GetText() };
			givenName = givenName.substr(0, givenName.size() - 1); //remove the _ at the end

			if (givenName == "")
			{
				std::cout << "please enter a name\n";
				return;
			}

			bool scoreWasAsigned{};

			//check if the given name is the same as a name already in the highscore list
			for (auto& highScore : m_HighScoreList)
			{
				if (givenName == highScore.first)
				{
					highScore.second = m_AmountOfPoints;
					scoreWasAsigned = true;
					break;
				}
			}

			//if the name was not yet there check if there are already 5 scores in the list
			//if not add the new score to the list and sort it
			if (m_HighScoreList.size() < 5 && !scoreWasAsigned)
			{
				m_HighScoreList.push_back({ givenName, m_AmountOfPoints });
				SortHighScoreList();
			}
			else if (m_HighScoreList[4].second < m_AmountOfPoints && !scoreWasAsigned) //if so check if the current score is higher then the lowest one in the list if so replace the one in the list with the current one else do nothing
			{
				m_HighScoreList[4].first = givenName;
				m_HighScoreList[4].second = m_AmountOfPoints;
			}
		}

		dae::InputManager::GetInstance().RemoveAllButtons();
		dae::InputManager::GetInstance().RemoveAllCommandsAndControlers();
		m_AmountOfPoints = 0;
		LoadLevel(1, *m_CurrentScene, m_GameMode);
	};
	const auto buttonSize{ continueButton->GetComponent<dae::RenderComponent>()->GetTextureComponent()->GetSize() };
	const glm::vec2 buttonPos{ sceneWidth / 2.f - buttonSize.x / 2.f, sceneHeight - 25.f };
	continueButton->AddComponent(std::make_unique<dae::ButtonComponent>(continueButton.get(), buttonPos, static_cast<float>(buttonSize.x), static_cast<float>(buttonSize.y), onContinueButtonClick));
	m_CurrentScene->Add(std::move(continueButton));

	//add object to show the current score
	auto currentScoreObject{ std::make_unique<dae::GameObject>(m_CurrentScene) };
	currentScoreObject->AddComponent(std::make_unique<dae::TextComponent>(currentScoreObject.get(), "your current score: " + std::to_string(m_AmountOfPoints), m_Font));
	auto textureSize{ currentScoreObject->GetComponent<dae::RenderComponent>()->GetTextureComponent()->GetSize() };
	currentScoreObject->SetLocalPosition(sceneWidth / 2.f - textureSize.x / 2.f, sceneHeight - 125.f);
	m_CurrentScene->Add(std::move(currentScoreObject));
}

void LevelManager::SortHighScoreList()
{
	std::sort(m_HighScoreList.begin(), m_HighScoreList.end(),
		[](const auto& highScore1, const auto& highScore2) { return highScore1.second > highScore2.second; });
}

void LevelManager::WriteHighScoreListToFile()
{
	std::ofstream outputFile{ "../Data/highScoreList.txt" };

	assert(outputFile.is_open() == true && "highScoreList.txt failed to open");

	for (auto& highScore : m_HighScoreList)
	{
		outputFile << highScore.first << '\n' << highScore.second << '\n';
	}
}