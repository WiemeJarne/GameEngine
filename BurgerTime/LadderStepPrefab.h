#pragma once
#include <string>
#include "Component.h"
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
}

class LadderStepPrefab final
{
public:
	LadderStepPrefab(glm::vec2 pos = { 0.f , 0.f });

	virtual ~LadderStepPrefab() = default;
	LadderStepPrefab(const LadderStepPrefab&) = delete;
	LadderStepPrefab(LadderStepPrefab&&) = delete;
	LadderStepPrefab& operator=(const LadderStepPrefab&) = delete;
	LadderStepPrefab& operator=(LadderStepPrefab&&) = delete;

	std::unique_ptr<dae::GameObject> GetGameObject() { return std::move(m_go); }

private:
	std::unique_ptr<dae::GameObject> m_go;
};