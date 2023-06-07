#pragma once
#include <string>
#include <tuple>
#include "Singleton.h"
#include "Scene.h"
#include "EventListener.h"
#include "PointsComponent.h"
#include "LevelGrid.h"
#include "Font.h"

enum class GameMode
{
	singlePlayer,
	coOp,
	versus
};

class LevelManager final : public dae::Singleton<LevelManager>, public dae::EventListener
{
public:
	~LevelManager();

	void LoadLevel(int levelNr, dae::Scene& scene, GameMode gameMode);
	void LoadNextLevel();
	void OnNotify(std::any data, int eventId, bool isEngineEvent) override;
	LevelGrid* GetActiveLevelGrid();

private:
	int m_AmountOfBurgerPartsInCurrentLevel{};
	int m_AmountOfBurgerParsReachedPlate{};
	bool m_HasBeenInitialized{};
	dae::Scene* m_CurrentScene{};
	int m_LevelNr{};
	GameMode m_GameMode{};
	PointsComponent* m_pPointsComponent{};
	int m_AmountOfPoints{};
	std::vector<std::tuple<std::unique_ptr<LevelGrid>, int, int>> m_LevelGrids{};
	const glm::vec2 m_LevelTopLeftPos{ 0.f, 32.f };
	std::shared_ptr<dae::Font> m_Font;
	std::vector<std::pair<std::string, int>> m_HighScoreList;
	int m_AmountOfPlayersDead{};

	bool LoadLevelPlatforms(int levelNr); //return if it succeeded to open the file
	void LoadLevelBurgerParts(int levelNr);
	const glm::vec2 AddLevelElementToCurrentScene(CellKind cellKind, int colNr, int rowNr);
	void ShowPointsScreen();
	void SortHighScoreList();
	void WriteHighScoreListToFile();
};