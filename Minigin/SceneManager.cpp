#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderImGui()
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderImGui();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::RemoveScene(Scene* scene)
{
	m_scenes.erase(std::remove_if(m_scenes.begin(), m_scenes.end(), [&](std::shared_ptr<Scene> pScene) { return scene == pScene.get(); }));
}

void dae::SceneManager::SetScenesSize(float width, float height)
{
	m_ScenesWidth = width;
	m_ScenesHeight = height;
}

dae::Scene* dae::SceneManager::GetSceneByIndex(int index) const
{
	if (m_scenes.size() <= index)
		return nullptr;

	return m_scenes[index].get();
}