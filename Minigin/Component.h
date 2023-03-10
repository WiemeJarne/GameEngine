#pragma once
#include <memory>

namespace dae
{
	class GameObject;
}

class Component
{
public:
	Component(dae::GameObject* owner) : m_Owner{ owner } {};

	virtual ~Component() = default;
	//Component(const Component&) = delete;
	//Component(Component&&) = delete;
	//Component& operator=(const Component&) = delete;
	//Component& operator=(Component&&) = delete;

	virtual void Update() = 0;
	virtual void Render() const = 0;

protected:
	dae::GameObject* m_Owner;
};