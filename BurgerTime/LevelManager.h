#pragma once
#include <string>
#include "Singleton.h"
#include "Scene.h"
#include "EventListener.h"

enum class GameMode
{
	singlePlayer,
	coOp,
	versus
};

class LevelManager final : public dae::Singleton<LevelManager>, public dae::EventListener
{
public:
	void LoadLevel(int levelNr, dae::Scene& scene, GameMode gameMode);
	void OnNotify(std::any data, int eventId, bool isEngineEvent) override;

private:
	int m_AmountOfBurgerPartsInCurrentLevel{};
	int m_AmountOfBurgerParsReachedPlate{};
	bool m_HasBeenInitialized{};
	dae::Scene* m_CurrentScene{};
	int m_LevelNr{};
	GameMode m_GameMode{};
};

