#include "Scene.h"
#include "GameObject.h"
#include <iostream>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::QueueForAdd(std::shared_ptr<GameObject> object)
{
	m_ObjectsQueuedToAdd.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::Remove(GameObject* object)
{
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&object](std::shared_ptr<GameObject> otherObject) { return otherObject.get() == object; }), m_objects.end());
}

void Scene::QueueForRemove(std::shared_ptr<GameObject> object)
{
	m_ObjectsQueuedForRemove.push_back(object.get());
}

void Scene::QueueForRemove(GameObject* object)
{
	m_ObjectsQueuedForRemove.push_back(object);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

std::shared_ptr<GameObject> Scene::GetSharedPtr(GameObject* pGameObject) const
{
	for (const auto& object : m_objects)
	{
		if (object.get() == pGameObject)
			return object;
	}

	return nullptr;
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}

	for (auto& object : m_objects)
	{
		object->EraseComponentsMarkedForDelete();
	}

	//remove all objects queued for remove
	for(auto& object : m_ObjectsQueuedForRemove)
	{
		Remove(object);
	}

	//add objects queued for add
	for (auto& object : m_ObjectsQueuedToAdd)
	{
		Add(object);
	}

	m_ObjectsQueuedToAdd.clear();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::RenderImGui()
{
	for (const auto& object : m_objects)
	{
		object->RenderImGui();
	}
}