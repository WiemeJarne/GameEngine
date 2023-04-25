#pragma once
#include <string>
#include "Component.h"

namespace dae
{
	class GameObject;
}

class PlayerPrefab final
{
public:
	PlayerPrefab(const std::string& textureFilePath, int amountOfLives, bool useController = false, float moveSpeed = 100.f);

	virtual ~PlayerPrefab() = default;
	PlayerPrefab(const PlayerPrefab&) = delete;
	PlayerPrefab(PlayerPrefab&&) = delete;
	PlayerPrefab& operator=(const PlayerPrefab&) = delete;
	PlayerPrefab& operator=(PlayerPrefab&&) = delete;

	std::unique_ptr<dae::GameObject> GetGameObject() { return std::move(m_go); }

private:
	std::unique_ptr<dae::GameObject> m_go;
};