#pragma once
#include "Component.h"
#pragma warning( push )
#include "imgui_plot.h"
#pragma warning ( pop )

class TrashTheCache final
{
public:
	TrashTheCache();
	~TrashTheCache();
	TrashTheCache(const TrashTheCache& other) = delete;
	TrashTheCache(TrashTheCache&& other) = delete;
	TrashTheCache& operator=(const TrashTheCache& other) = delete;
	TrashTheCache& operator=(TrashTheCache&& other) = delete;

	virtual void Render();

private:
	int m_AmountOfSamplesEX01{ 10 };
	int m_AmountOfSamplesEX02{ 100 };
	float* m_pXValues{};
	float* m_pYValuesIntArray{};
	float* m_pYValusGameObject3D{};
	float* m_pYValusGameObject3DAlt{};
	const int m_AmountOfValuesInGraphArrays{ 11 };
	
	ImGui::PlotConfig conf{};
	bool m_TrashTheCachePressed{};

	void TrashTheCacheIntArray();
	void TrashTheCacheGameObject3DArray();
	void TrashTheCacheGameObject3DAltArray();
};