#pragma once
#include "Singleton.h"
#include <vector>
#include "glm/vec2.hpp"
#include "EventQueue.h"
#include "CollisionBoxComponent.h"

namespace dae
{
	struct CollidedGameObjects
	{
		CollidedGameObjects() = default;

		CollidedGameObjects(GameObject* _pTriggered, GameObject* _pOther)
			: pTriggered{ _pTriggered }
			, pOther{ _pOther }
		{}

		GameObject* pTriggered{ nullptr };
		GameObject* pOther{ nullptr };
	};

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void Update();
		void AddCollider(CollisionBoxComponent* pCollisionBoxComponent);
		void RemoveCollider(CollisionBoxComponent* pCollisionBoxComponent);

	private:
		std::vector<CollisionBoxComponent*> m_CollisionBoxComponents;
		EventQueue* m_pEventQueue;

		bool AreColliding(const glm::vec2& collider1TopLeft, float collider1With, float collider1Height, const glm::vec2& collider2TopLeft, float collider2Width, float collider2Height);
	};
}