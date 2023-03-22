#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class GameObject final
	{
	public:
		GameObject() = default;

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = default;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = default;

		virtual void Update();
		virtual void Render() const;
		virtual void RenderImGui();

		void SetParent(GameObject* parent, bool keepWorldPos);
		GameObject* GetParent() const { return m_Parent; }

		size_t GetChildCount() const { return m_Children.size(); }
		GameObject* GetChildAt(int index) const { return m_Children[index]; }

		void SetLocalPosition(float x, float y);
		const glm::vec3& GetLocalPos();

		void SetWorldPosition(float x, float y);
		const glm::vec3& GetWorldPos();
		void UpdateWorldPos();
		
		void AddComponent(std::unique_ptr<Component> component);
		
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
				[](const std::unique_ptr<Component>& component)
				{
					return dynamic_cast<ComponentType*>(component.get()) != nullptr;
				});

			if (iterator == m_Components.end())
				return false;

			return true;
		}

		template<typename ComponentType>
		std::unique_ptr<ComponentType> GetComponent() const
		{
			for (const auto& component : m_Components)
			{
				if (std::unique_ptr<ComponentType> sharedPtr = std::dynamic_pointer_cast<ComponentType>(component))
					return sharedPtr;
			}

			return nullptr;
		}

		void EraseComponentsMarkedForDelete();

	private:
		std::vector<std::unique_ptr<Component>> m_Components;
		std::vector<std::vector<std::unique_ptr<Component>>::iterator> m_ComponentToDeleteIterators;
		std::vector<GameObject*> m_Children;
		GameObject* m_Parent{ nullptr };
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};
		bool m_UpdateWorldPos{};
	
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
	};
}