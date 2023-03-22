#pragma once
#include "Component.h"
#pragma warning( push )
#include "imgui_plot.h"
#pragma warning ( pop )
#include <vector>

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform{};
	int ID{};
};

class GameObject3DAlt
{
public:
	Transform* transform{};
	int ID{};
};

class TrashTheCache final : public Component
{
public:
	TrashTheCache(dae::GameObject* owner);
	~TrashTheCache() = default;
	TrashTheCache(const TrashTheCache& other) = delete;
	TrashTheCache(TrashTheCache&& other) = delete;
	TrashTheCache& operator=(const TrashTheCache& other) = delete;
	TrashTheCache& operator=(TrashTheCache&& other) = delete;

	void Update() override;
	void Render() const override {}
	void RenderImGui() override;

private:
	int m_AmountOfSamplesEX01{ 10 };
	int m_AmountOfSamplesEX02{ 100 };
	std::vector<float> m_pXValues{};
	std::vector<float> m_pYValuesIntArray{};
	std::vector<float> m_pYValusGameObject3D{};
	std::vector<float> m_pYValusGameObject3DAlt{};
	std::vector<const float*> m_pCobinedGraphYValues{};
	ImU32 m_CombinedGraphColors[2]{ ImColor(99, 186, 65), ImColor(88, 161, 167) };
	const int m_AmountOfValuesInGraphArrays{ 11 };
	
	ImGui::PlotConfig m_IntArrayConfig{};
	ImGui::PlotConfig m_GameObject3DConfig{};
	ImGui::PlotConfig m_GameObject3DAltConfig{};
	ImGui::PlotConfig m_GameObject3DAndAltCombined{};
	bool m_TrashTheCachePressed{};
	bool m_TrashTheCacheGameObject3DPressed{};
	bool m_TrashTheCacheGameObject3DAltPressed{};
	bool m_GameObject3DCalculated{};
	bool m_GameObject3DAltCalculated{};

	void CalculateIntArray();
	void CalculateGameObject3DArray();
	void CalculateGameObject3DAltArray();
	void CalculateGameObject3DAndAltCombinedGraph();
};