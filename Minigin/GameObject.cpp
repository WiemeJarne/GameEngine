#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "RenderComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (std::shared_ptr<Component>& component : m_Components)
	{
		component.get()->Update();
	}
}

void dae::GameObject::Render() const
{
	this->GetComponent<RenderComponent>()->Render(*this);
}

void dae::GameObject::AddComponent(std::shared_ptr<Component> pComponent)
{
	m_Components.emplace_back(std::move(pComponent));
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
