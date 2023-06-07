#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render() const;
		void RenderImGui();
		void RemoveScene(Scene* scene);
		//this is only called in the Minigin.cpp file calling this anywhere else will not have any effect ont the size of the scenes
		void SetScenesSize(float width, float height);
		float GetScenesWidth() const { return m_ScenesWidth; }
		float GetScenesHeight() const { return m_ScenesHeight; }
		Scene* GetSceneByIndex(int index) const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		float m_ScenesWidth{};
		float m_ScenesHeight{};
	};
}
