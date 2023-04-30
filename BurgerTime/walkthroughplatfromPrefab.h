#pragma once
#include <string>
#include "Component.h"
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
}

class walkthroughplatfromPrefab final
{
public:
	walkthroughplatfromPrefab(glm::vec2 pos = { 0.f , 0.f });

	virtual ~walkthroughplatfromPrefab() = default;
	walkthroughplatfromPrefab(const walkthroughplatfromPrefab&) = delete;
	walkthroughplatfromPrefab(walkthroughplatfromPrefab&&) = delete;
	walkthroughplatfromPrefab& operator=(const walkthroughplatfromPrefab&) = delete;
	walkthroughplatfromPrefab& operator=(walkthroughplatfromPrefab&&) = delete;

	std::unique_ptr<dae::GameObject> GetGameObject() { return std::move(m_go); }

private:
	std::unique_ptr<dae::GameObject> m_go;
};