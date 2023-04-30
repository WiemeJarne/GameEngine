#pragma once
#include <string>
#include "Component.h"
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
}

class PlatformPrefab final
{
public:
	PlatformPrefab(glm::vec2 pos = {0.f , 0.f});

	virtual ~PlatformPrefab() = default;
	PlatformPrefab(const PlatformPrefab&) = delete;
	PlatformPrefab(PlatformPrefab&&) = delete;
	PlatformPrefab& operator=(const PlatformPrefab&) = delete;
	PlatformPrefab& operator=(PlatformPrefab&&) = delete;

	std::unique_ptr<dae::GameObject> GetGameObject() { return std::move(m_go); }

private:
	std::unique_ptr<dae::GameObject> m_go;
};