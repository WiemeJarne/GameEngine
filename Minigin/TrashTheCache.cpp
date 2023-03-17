#include "TrashTheCache.h"
#include <chrono>
#include <algorithm>
#include <numeric>
#include "imgui.h"
#include <iostream>

TrashTheCache::TrashTheCache()
{
	m_pXValues = new float[11];
	float stepSize{ 1 };
	for (int index{}; index < 11; ++index)
	{
		m_pXValues[index] = stepSize;
		stepSize *= 2;
	}

	m_pYValuesIntArray = new float[11];
	m_pYValusGameObject3D = new float[11];
	m_pYValusGameObject3DAlt = new float[11];
}

TrashTheCache::~TrashTheCache()
{
	delete m_pXValues;
	delete m_pYValuesIntArray;
	delete m_pYValusGameObject3D;
	delete m_pYValusGameObject3DAlt;
}

void TrashTheCache::Render()
{
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_AmountOfSamplesEX01, 1);
	if (m_AmountOfSamplesEX01 < 0) m_AmountOfSamplesEX01 = 0;

	if (m_TrashTheCachePressed)
	{
		ImGui::Text("Wait for it...");

		TrashTheCacheIntArray();

		ImU32 graphColor{ ImColor(217, 132, 69) };
		conf.values.color = graphColor;
		conf.values.xs = m_pXValues;
		conf.values.ys = m_pYValuesIntArray;
		conf.values.count = m_AmountOfValuesInGraphArrays;
		conf.scale.min = 0;
		//find highest number
		float highestNumber{};
		for (int index{}; index < m_AmountOfValuesInGraphArrays; ++index)
		{
			if (m_pYValuesIntArray[index] > highestNumber)
				highestNumber = m_pYValuesIntArray[index];
		}
		conf.scale.max = highestNumber;
		conf.tooltip.show = true;
		conf.tooltip.format = "x%.2f, y=%.2f";
		conf.grid_y.show = true;
		conf.grid_y.size = 5.f;
		conf.grid_y.subticks = 1;
		conf.frame_size = ImVec2(150, 75);
		conf.line_thickness = 1.f;

		m_TrashTheCachePressed = false;
	}

	else if (ImGui::Button("Trash the cache"))
	{
		m_TrashTheCachePressed = true;
	}

	ImGui::Plot("plot", conf);

	ImGui::End();

	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# samples", &m_AmountOfSamplesEX02, 1);
	if (m_AmountOfSamplesEX02 < 0) m_AmountOfSamplesEX02 = 0;


	if (ImGui::Button("Trash the cache with GameObject3D"))
	{

	}

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{

	}

	ImGui::Text("Combined:");

	ImGui::End();
}

void TrashTheCache::TrashTheCacheIntArray()
{
    const int arraySize{ 25'000'000 };
    int* arr{ new int[arraySize] {} };

    std::vector<long long>times{};

    int yValueNr{};
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
        m_pYValuesIntArray[yValueNr] = (averageTime / 1000.f);
        ++yValueNr;
		//std::cout << stepsize << "; " << averageTime / 1000.f << " ms\n";
        //emty the vector
        times.clear();
    }

	for (int index{}; index < 11; ++index)
	{
		std::cout << m_pXValues[index] << '\t' << m_pYValuesIntArray[index] << '\n';
	}

    delete[] arr;
}

void TrashTheCache::TrashTheCacheGameObject3DArray()
{

}

void TrashTheCache::TrashTheCacheGameObject3DAltArray()
{

}