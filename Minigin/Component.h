#pragma once
namespace dae
{
	class GameObject;
}

class Component
{
public:
	Component() = default;

	Component(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&&) = delete;

	virtual void Update() = 0;
	virtual void Render(const dae::GameObject&) const {};
};