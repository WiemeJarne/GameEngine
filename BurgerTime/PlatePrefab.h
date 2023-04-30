#pragma once
#include <string>
#include "Component.h"
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
}

class PlatePrefab final
{
public:
	PlatePrefab(glm::vec2 pos = { 0.f , 0.f });

	virtual ~PlatePrefab() = default;
	PlatePrefab(const PlatePrefab&) = delete;
	PlatePrefab(PlatePrefab&&) = delete;
	PlatePrefab& operator=(const PlatePrefab&) = delete;
	PlatePrefab& operator=(PlatePrefab&&) = delete;

	std::unique_ptr<dae::GameObject> GetGameObject() { return std::move(m_go); }

private:
	std::unique_ptr<dae::GameObject> m_go;
};