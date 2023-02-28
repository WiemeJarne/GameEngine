#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "TextureComponent.h"
#include "TextComponent.h"

class Component;

namespace dae
{
	//class TextureComponent;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetPosition(float x, float y);
		const Transform& GetTransform() const { return m_transform; }
		void AddComponent(std::shared_ptr<Component> pComponent);

		template<typename T>
		std::shared_ptr<T> GetComponent() const
		{
			for (const auto& component : m_Components)
			{
				if (std::shared_ptr<T> sharedPtr = std::dynamic_pointer_cast<T>(component))
					return sharedPtr;
			}

			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<Component>> m_Components;
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		
	};
}
