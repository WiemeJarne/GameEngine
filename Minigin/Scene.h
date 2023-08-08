#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "ButtonComponent.h"

namespace dae
{
	class Scene final
	{
		friend Scene* SceneManager::CreateScene(const std::string& name, bool setAsActiveScene = true);
	public:
		void Add(std::shared_ptr<GameObject> object, bool isButton = false);
		void QueueForAdd(std::shared_ptr<GameObject> object, bool isButton = false);
		void Remove(std::shared_ptr<GameObject> object, bool isButton = false);
		void Remove(GameObject* object, bool isButton = false);
		void QueueForRemove(std::shared_ptr<GameObject> object, bool isButton = false);
		void QueueForRemove(GameObject* object, bool isButton = false);
		void RemoveAll();
		std::shared_ptr<GameObject> GetSharedPtr(GameObject* pGameObject) const;
		const std::string& GetName() const { return m_name; }
		std::vector<ButtonComponent*> GetButtons() const { return m_pButtons; }

		void Update();
		void Render() const;
		void RenderImGui();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		void AddButton(ButtonComponent* pButtonComponent);
		void RemoveButton(ButtonComponent* pButtonComponent);

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};
		std::vector <std::shared_ptr<GameObject>> m_ObjectsQueuedToAdd{};
		std::vector<GameObject*> m_ObjectsQueuedForRemove{};
		std::vector<ButtonComponent*> m_pButtons{};

		static unsigned int m_idCounter; 
	};
}