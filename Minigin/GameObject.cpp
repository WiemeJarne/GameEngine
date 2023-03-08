#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto& component : m_Components)
	{
		component->Update();
	}

	if (m_UpdateWorldPos)
		UpdateWorldPos();
}

void dae::GameObject::Render() const
{
	for (const std::shared_ptr<Component>& component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(std::shared_ptr<Component> component)
{
	bool componentAlreadyOnThisObject{};

	//check if there already is a component of this type on this gameObject
	for (auto& existingComponent : m_Components)
	{
		if (typeid(*existingComponent) == typeid(*component))
		{
			componentAlreadyOnThisObject = true;
		}
	}

	//if the object is not on this gameObject add it else do nothing
	if (!componentAlreadyOnThisObject)
	{
		m_Components.emplace_back(std::move(component));
	}
}

void dae::GameObject::SetParent(std::shared_ptr<dae::GameObject> parent, bool keepWorldPos)
{
	//check if the passed trough parent isn't a direct child of this gameObject
	for (auto& child : m_Children)
	{
		if (parent == child)
			return;
	}

	//check if the gameObject isn't trying to assing himself as his own parent
	if (parent.get() == this)
		return;

	//if there is no parent the local position is equal to the world position
	if (!parent)
		SetLocalPosition(GetWorldPos().x, GetWorldPos().y);
	else
	{
		if (keepWorldPos) //Updates the local pos so the world pos is kept
		{
			auto newLocalPos{ GetLocalPos() - parent->GetWorldPos() };
			SetLocalPosition(newLocalPos.x, newLocalPos.y);
		}
		m_UpdateWorldPos = true;
	}

	//remove this gameObject as a child from the previous parent
	if (m_Parent.lock())
		m_Parent.lock()->RemoveChild(this);

	//assign the new parent
	m_Parent = parent;

	//add this gameObject as a child of the new parent
	if (m_Parent.lock())
		m_Parent.lock()->AddChild(this);
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_LocalTransform.SetPosition(x, y, 0.f);
	m_UpdateWorldPos = true;

	//todo zet de dirty flag van de children
}

void dae::GameObject::SetWorldPosition(float x, float y)
{
	m_WorldTransform.SetPosition(x, y, 0.f);
}

const glm::vec3& dae::GameObject::GetLocalPos()
{
	return m_LocalTransform.GetPosition();
}

const glm::vec3& dae::GameObject::GetWorldPos()
{ 
	if (m_UpdateWorldPos)
		UpdateWorldPos();

	return m_WorldTransform.GetPosition();
}

void dae::GameObject::UpdateWorldPos()
{
	if (!m_Parent.lock())
		m_WorldTransform.SetPosition(m_LocalTransform.GetPosition().x, m_LocalTransform.GetPosition().y, 0.f);
	else
	{
		auto newWorldPos{ m_Parent.lock()->GetWorldPos() + m_LocalTransform.GetPosition()};
		m_WorldTransform.SetPosition(newWorldPos.x, newWorldPos.y, newWorldPos.z);
	}

	m_UpdateWorldPos = false;
}

void dae::GameObject::EraseComponentsMarkedForDelete()
{
	for (auto iterator : m_ComponentToDeleteIterators)
	{
		if (iterator != m_Components.end())
		{
			m_Components.erase(iterator);
		}
	}

	m_ComponentToDeleteIterators.clear();
}

void dae::GameObject::AddChild(dae::GameObject* pChild)
{
	for (auto& child : m_Children)
	{
		if (child.get() == pChild)
			return;
	}

	m_Children.push_back(std::make_shared<GameObject>(*pChild));
}

void dae::GameObject::RemoveChild(dae::GameObject* pChild)
{
	auto iterator = std::find_if(m_Children.begin(), m_Children.end(),
		[pChild](const std::shared_ptr<GameObject>& child)
		{
			return child.get() == pChild;
		});

	if (iterator != m_Children.end())
	{
		m_Children.erase(iterator);
	}

	pChild->SetParent(std::make_shared<GameObject>(), false);
}