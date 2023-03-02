#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

class Component;

namespace dae
{
	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos);
		std::shared_ptr<GameObject> GetParent() const { return m_Parent; }
		size_t GetChildCount() const { return m_Children.size(); }
		std::weak_ptr<GameObject> GetChildAt(int index) const { return m_Children[index]; }
		void SetLocalPosition(float x, float y);
		void SetWorldPosition(float x, float y);
		const glm::vec3& GetLocalPos();
		const glm::vec3& GetWorldPos();
		
		void UpdateWorldPos();
		void AddComponent(std::shared_ptr<Component> pComponent);
		
		template<typename ComponentType>
		void RemoveComponent()
		{
			auto iterator = std::find_if(m_Components.begin(), m_Components.end(),
				[](const std::shared_ptr<Component>& component)
				{
					return dynamic_cast<ComponentType*>(component.get()) != nullptr;
				});

			m_ComponentToDeleteIterators.push_back(iterator);
		}

		template<typename ComponentType>
		bool HasComponent()
		{
			auto iterator = std::find_if(m_Components.begin(), m_Components.end(),
				[](const std::shared_ptr<Component>& component)
				{
					return dynamic_cast<ComponentType*>(component.get()) != nullptr;
				});

			if (iterator == m_Components.end())
				return false;

			return true;
		}

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent() const
		{
			for (const auto& component : m_Components)
			{
				if (std::shared_ptr<ComponentType> sharedPtr = std::dynamic_pointer_cast<ComponentType>(component))
					return sharedPtr;
			}

			return nullptr;
		}

		void EraseComponentsMarkedForDelete();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = default;
		GameObject& operator=(const GameObject& other) = delete;

	private:
		std::vector<std::shared_ptr<Component>> m_Components;
		std::vector<std::vector<std::shared_ptr<Component>>::iterator> m_ComponentToDeleteIterators;
		std::vector<std::shared_ptr<GameObject>> m_Children;
		std::shared_ptr<GameObject> m_Parent;
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};
		bool m_UpdateWorldPos{};

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	};
}