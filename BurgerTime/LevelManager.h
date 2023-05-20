#pragma once
#include <string>
#include "Singleton.h"
#include "Scene.h"

enum class GameMode
{
	singlePlayer,
	coOp,
	versus
};

class LevelManager final : public dae::Singleton<LevelManager>
{
public:
	void LoadLevel(int levelNr, dae::Scene& scene, GameMode gameMode);
};

