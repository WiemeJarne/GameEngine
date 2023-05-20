#pragma once
#include <string>
#include <glm/vec2.hpp>
#include "Component.h"

namespace dae
{
	class GameObject;
}

class PlayerPrefab final
{
public:
	PlayerPrefab(const std::string& textureFilePath, int amountOfLives, const glm::vec2& pos, bool useKeyboard = false, float moveSpeed = 100.f);

	~PlayerPrefab() = default;
	PlayerPrefab(const PlayerPrefab&) = delete;
	PlayerPrefab(PlayerPrefab&&) = delete;
	PlayerPrefab& operator=(const PlayerPrefab&) = delete;
	PlayerPrefab& operator=(PlayerPrefab&&) = delete;

	std::unique_ptr<dae::GameObject> GetGameObject() { return std::move(m_go); }

private:
	std::unique_ptr<dae::GameObject> m_go;
};