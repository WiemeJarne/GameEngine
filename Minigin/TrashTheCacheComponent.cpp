#include "TrashTheCacheComponent.h"
#include <chrono>
#include <algorithm>
#include <numeric>
#include "imgui.h"
#include <iostream>

TrashTheCache::TrashTheCache(dae::GameObject* owner)
    : Component(owner)
{
    for (int stepSize{1}; stepSize <= 1024; stepSize *= 2)
    {
        m_pXValues.push_back(static_cast<float>(stepSize));
    }

    ImU32 graphColor{ ImColor(217, 132, 69) };
    m_IntArrayConfig.values.color = graphColor;
    m_IntArrayConfig.values.count = static_cast<int>(m_pXValues.size());
    m_IntArrayConfig.scale.min = 0;
    m_IntArrayConfig.tooltip.show = true;
    m_IntArrayConfig.tooltip.format = "x%.2f, y%.2f";
    m_IntArrayConfig.grid_y.show = true;
    m_IntArrayConfig.grid_y.size = 5.f;
    m_IntArrayConfig.grid_y.subticks = 1;
    m_IntArrayConfig.line_thickness = 1.f;

    graphColor = ImColor(99, 186, 65);
    m_GameObject3DConfig.values.color = graphColor;
    m_GameObject3DConfig.values.count = m_AmountOfValuesInGraphArrays;
    m_GameObject3DConfig.scale.min = 0;
    m_GameObject3DConfig.tooltip.show = true;
    m_GameObject3DConfig.tooltip.format = "x%.2f, y%.2f";
    m_GameObject3DConfig.grid_y.show = true;
    m_GameObject3DConfig.grid_y.size = 5.f;
    m_GameObject3DConfig.grid_y.subticks = 1;
    m_GameObject3DConfig.line_thickness = 1.f;

    graphColor = ImColor(88, 161, 167);
    m_GameObject3DAltConfig.values.color = graphColor;
    m_GameObject3DAltConfig.values.count = m_AmountOfValuesInGraphArrays;
    m_GameObject3DAltConfig.scale.min = 0;
    m_GameObject3DAltConfig.tooltip.show = true;
    m_GameObject3DAltConfig.tooltip.format = "x%.2f, y%.2f";
    m_GameObject3DAltConfig.grid_y.show = true;
    m_GameObject3DAltConfig.grid_y.size = 5.f;
    m_GameObject3DAltConfig.grid_y.subticks = 1;
    m_GameObject3DAltConfig.line_thickness = 1.f;

    m_GameObject3DAndAltCombined.values.colors = m_CombinedGraphColors;
    m_GameObject3DAndAltCombined.values.xs = m_pXValues.data();
    m_GameObject3DAndAltCombined.values.count = m_AmountOfValuesInGraphArrays;
    m_GameObject3DAndAltCombined.values.ys_count = 2;
    m_GameObject3DAndAltCombined.scale.min = 0;
    m_GameObject3DAndAltCombined.tooltip.show = true;
    m_GameObject3DAndAltCombined.tooltip.format = "x%.2f, y=%.2f";
    m_GameObject3DAndAltCombined.grid_y.show = true;
    m_GameObject3DAndAltCombined.grid_y.size = 5.f;
    m_GameObject3DAndAltCombined.grid_y.subticks = 1;
    m_GameObject3DAndAltCombined.line_thickness = 1.f;
}

void TrashTheCache::Update()
{
    //make sure the sample size can not go below 3 because the highest and lowest times are discarded
    if (m_AmountOfSamplesEX01 < 3) m_AmountOfSamplesEX01 = 3;

    if (m_TrashTheCachePressed)
	{
        CalculateIntArray();
		m_TrashTheCachePressed = false;
	}

    //make sure the sample size can not go below 3 because the highest and lowest times are discarded
    if (m_AmountOfSamplesEX02 < 3) m_AmountOfSamplesEX02 = 3;

    if (m_TrashTheCacheGameObject3DPressed)
    {
        CalculateGameObject3DArray();
        m_GameObject3DCalculated = true;
        m_TrashTheCacheGameObject3DPressed = false;
    }

    if (m_TrashTheCacheGameObject3DAltPressed)
    {
        CalculateGameObject3DAltArray();
        m_GameObject3DAltCalculated = true;
        m_TrashTheCacheGameObject3DAltPressed = false;
    }

    if (m_GameObject3DCalculated && m_GameObject3DAltCalculated)
    {
        CalculateGameObject3DAndAltCombinedGraph();
    }
}

void TrashTheCache::RenderImGui()
{
	ImGui::Begin("Exercise 1"); //begin for window Exercise 1
	ImGui::InputInt("# samples", &m_AmountOfSamplesEX01, 1);
   
    if (ImGui::Button("Trash the cache"))
    {
        m_TrashTheCachePressed = true;
        ImGui::Text("Wait for it...");
    }

	ImGui::Plot("plot0", m_IntArrayConfig);

	ImGui::End(); //end for window Exercise 1

	ImGui::Begin("Exercise 2"); //begin for window Exercise 2
	ImGui::InputInt("# samples", &m_AmountOfSamplesEX02, 1);
    
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
        m_TrashTheCacheGameObject3DPressed = true;
        ImGui::Text("Wait for it...");
	}

    ImGui::Plot("plot1", m_GameObject3DConfig);

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
        m_TrashTheCacheGameObject3DAltPressed = true;
        ImGui::Text("Wait for it...");
	}

    ImGui::Plot("plot2", m_GameObject3DAltConfig);

    if (m_GameObject3DCalculated && m_GameObject3DAltCalculated)
    {
        ImGui::Text("Combined:");
        ImGui::Plot("plot3", m_GameObject3DAndAltCombined);
    }

	ImGui::End(); //emd for window Exercise 2
}

void TrashTheCache::CalculateIntArray()
{
    const int arraySize{ 25'000'000 };
    int* arr{ new int[arraySize] {} };

    std::vector<long long>times{};

    m_pYValuesIntArray.clear();
    for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
    {
        for (int sampleIndex{}; sampleIndex < m_AmountOfSamplesEX01; ++sampleIndex)
        {
            const auto start{ std::chrono::high_resolution_clock::now() };

            for (int index{}; index < arraySize; index += stepsize)
            {
                arr[index] *= 2;
            }

            const auto end{ std::chrono::high_resolution_clock::now() };
            times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }

        //remove hightest and lowest time
        times.erase(std::max_element(begin(times), end(times)));
        times.erase(std::min_element(begin(times), end(times)));

        //take the remaining times and take the average
        const auto averageTime{ std::accumulate(begin(times), end(times), 0.f) / static_cast<float>((m_AmountOfSamplesEX01 - 2)) };
        m_pYValuesIntArray.push_back(averageTime / 1000.f);

        //emty the vector
        times.clear();
    }

    delete[] arr;
    
    m_IntArrayConfig.values.xs = m_pXValues.data();
    m_IntArrayConfig.values.ys = m_pYValuesIntArray.data();
    //find highest number
    float highestNumber{};
    for (int index{}; index < m_AmountOfValuesInGraphArrays; ++index)
    {
        if (m_pYValuesIntArray[index] > highestNumber)
            highestNumber = m_pYValuesIntArray[index];
    }
    m_IntArrayConfig.scale.max = highestNumber;
    m_IntArrayConfig.frame_size = ImVec2(150, 75);
}

void TrashTheCache::CalculateGameObject3DArray()
{  
    const int arraySize{ 10'000'000 };
    GameObject3D* gameObject3DArr{ new GameObject3D[arraySize] {} };

    std::vector<long long>GameObject3DTimes{};

    m_pYValusGameObject3D.clear();
    for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
    {
        for (int measurementIndex{}; measurementIndex < m_AmountOfSamplesEX02; ++measurementIndex)
        {
            auto start{ std::chrono::high_resolution_clock::now() };

            for (int index{}; index < arraySize; index += stepsize)
            {
                gameObject3DArr[index].ID *= 2;
            }

            auto end{ std::chrono::high_resolution_clock::now() };
            GameObject3DTimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }

        //remove hightest and lowest time from both vectors
        GameObject3DTimes.erase(std::max_element(begin(GameObject3DTimes), end(GameObject3DTimes)));
        GameObject3DTimes.erase(std::min_element(begin(GameObject3DTimes), end(GameObject3DTimes)));

        //take the remaining times and take the average from both vectors
        auto averageTime{ std::accumulate(begin(GameObject3DTimes), end(GameObject3DTimes), 0.f) / static_cast<float>((m_AmountOfSamplesEX02 - 2)) };

        m_pYValusGameObject3D.push_back(averageTime / 1000.f);

        //emty the vectors
        GameObject3DTimes.clear();
    }

    delete[] gameObject3DArr;

    m_GameObject3DConfig.values.xs = m_pXValues.data();
    m_GameObject3DConfig.values.ys = m_pYValusGameObject3D.data();
    //find highest number
    float highestNumber{};
    for (int index{}; index < m_AmountOfValuesInGraphArrays; ++index)
    {
        if (m_pYValusGameObject3D[index] > highestNumber)
            highestNumber = m_pYValusGameObject3D[index];
    }
    m_GameObject3DConfig.scale.max = highestNumber;
    m_GameObject3DConfig.frame_size = ImVec2(150, 75);
}

void TrashTheCache::CalculateGameObject3DAltArray()
{
    const int arraySize{ 10'000'000 };
    GameObject3DAlt* gameObject3DAltArr{ new GameObject3DAlt[arraySize] {} };

    std::vector<long long>GameObject3DAltTimes{};

    m_pYValusGameObject3DAlt.clear();
    for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
    {
        for (int measurementIndex{}; measurementIndex < m_AmountOfSamplesEX02; ++measurementIndex)
        {
            auto start{ std::chrono::high_resolution_clock::now() };

            for (int index{}; index < arraySize; index += stepsize)
            {
                gameObject3DAltArr[index].ID *= 2;
            }

            auto end{ std::chrono::high_resolution_clock::now() };
            GameObject3DAltTimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }

        GameObject3DAltTimes.erase(std::max_element(begin(GameObject3DAltTimes), end(GameObject3DAltTimes)));
        GameObject3DAltTimes.erase(std::min_element(begin(GameObject3DAltTimes), end(GameObject3DAltTimes)));

        auto averageTime{ std::accumulate(begin(GameObject3DAltTimes), end(GameObject3DAltTimes), 0.f) / static_cast<float>((m_AmountOfSamplesEX02 - 2)) };

        m_pYValusGameObject3DAlt.push_back(averageTime / 1000.f);

        GameObject3DAltTimes.clear();
    }

    delete[] gameObject3DAltArr;

    m_GameObject3DAltConfig.values.xs = m_pXValues.data();
    m_GameObject3DAltConfig.values.ys = m_pYValusGameObject3DAlt.data();
    //find highest number
    float highestNumber{};
    for (int index{}; index < m_AmountOfValuesInGraphArrays; ++index)
    {
        if (m_pYValusGameObject3DAlt[index] > highestNumber)
            highestNumber = m_pYValusGameObject3DAlt[index];
    }
    m_GameObject3DAltConfig.scale.max = highestNumber;
    m_GameObject3DAltConfig.frame_size = ImVec2(150, 75);
}

void TrashTheCache::CalculateGameObject3DAndAltCombinedGraph()
{
    m_pCobinedGraphYValues.clear();
    m_pCobinedGraphYValues.push_back(m_pYValusGameObject3D.data());
    m_pCobinedGraphYValues.push_back(m_pYValusGameObject3DAlt.data());
    m_GameObject3DAndAltCombined.values.ys_list = m_pCobinedGraphYValues.data();
    //find highest number
    float highestNumber{};
    for (int index{}; index < m_AmountOfValuesInGraphArrays; ++index)
    {
        if (m_pYValusGameObject3D[index] > highestNumber)
            highestNumber = m_pYValusGameObject3D[index];

        if (m_pYValusGameObject3DAlt[index] > highestNumber)
            highestNumber = m_pYValusGameObject3DAlt[index];
    }
    m_GameObject3DAndAltCombined.scale.max = highestNumber;
    m_GameObject3DAndAltCombined.frame_size = ImVec2(150, 75);
}