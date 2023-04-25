// BurgerTime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "Timer.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "MoveInCircleComponent.h"
#include "Renderer.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "MoveCommand.h"
#include "HealthComponent.h"
#include "DamageCommand.h"
#include "PointsCommand.h"
#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "PlayerPrefab.h"
#include <iostream>
#include <vector>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto renderComponent = std::make_unique<RenderComponent>(go.get(), "background.tga");
	go->AddComponent(std::move(renderComponent));
	scene.Add(std::move(go));

	go = std::make_shared<dae::GameObject>();
	renderComponent = std::make_unique<RenderComponent>(go.get(), "logo.tga");
	go->AddComponent(std::move(renderComponent));
	go->SetWorldPosition(216, 180);
	scene.Add(std::move(go));

	/*go = std::make_shared<dae::GameObject>();
	go->SetWorldPosition(80, 20);
	renderComponent = std::make_unique<RenderComponent>(go.get());*/
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	/*auto to = std::make_unique<dae::TextComponent>(go.get(), "Programming 4 Assignment", font, renderComponent.get());
	go->AddComponent(std::move(renderComponent));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));*/

	auto player1{ std::make_unique<PlayerPrefab>("PeterPepperFrontFacing.png", 3) };
	go = player1->GetGameObject();
	go->SetLocalPosition(330.f, 300.f);

	auto p1LivesDisplay = std::make_shared<dae::GameObject>();
	p1LivesDisplay->SetWorldPosition(5, 350);
	renderComponent = std::make_unique<RenderComponent>(p1LivesDisplay.get());
	auto to = std::make_unique<dae::TextComponent>(p1LivesDisplay.get(), "lives", font, renderComponent.get(), SDL_Color{ 194, 195, 114 });
	auto livesDisplayComponent{ std::make_unique<LivesDisplayComponent>(p1LivesDisplay.get(), go->GetComponent<HealthComponent>(), to.get()) };
	p1LivesDisplay->AddComponent(std::move(renderComponent));
	p1LivesDisplay->AddComponent(std::move(to));
	p1LivesDisplay->AddComponent(std::move(livesDisplayComponent));
	scene.Add(std::move(p1LivesDisplay));

	auto p1PointsDisplay = std::make_shared<dae::GameObject>();
	p1PointsDisplay->SetWorldPosition(5, 365);
	renderComponent = std::make_unique<RenderComponent>(p1PointsDisplay.get());
	to = std::make_unique<dae::TextComponent>(p1PointsDisplay.get(), "points", font, renderComponent.get(), SDL_Color{ 194, 195, 114 });
	auto pointsDisplayComponent{ std::make_unique<PointsDisplayComponent>(go.get(), go->GetComponent<PointsComponent>(), to.get()) };
	p1PointsDisplay->AddComponent(std::move(renderComponent));
	p1PointsDisplay->AddComponent(std::move(to));
	p1PointsDisplay->AddComponent(std::move(pointsDisplayComponent));
	scene.Add(std::move(p1PointsDisplay));

	scene.Add(std::move(go));

	auto player2{ std::make_unique<PlayerPrefab>("MrHotDog.png", 3, true) };
	go = player2->GetGameObject();
	go->SetLocalPosition(310.f, 300.f);
	auto p2LivesDisplay = std::make_shared<dae::GameObject>();
	p2LivesDisplay->SetWorldPosition(5, 385);
	renderComponent = std::make_unique<RenderComponent>(p2LivesDisplay.get());
	to = std::make_unique<dae::TextComponent>(p2LivesDisplay.get(), "lives", font, renderComponent.get(), SDL_Color{ 59, 172, 57 });
	livesDisplayComponent = std::make_unique<LivesDisplayComponent>(p2LivesDisplay.get(), go->GetComponent<HealthComponent>(), to.get());
	p2LivesDisplay->AddComponent(std::move(renderComponent));
	p2LivesDisplay->AddComponent(std::move(to));
	p2LivesDisplay->AddComponent(std::move(livesDisplayComponent));
	scene.Add(std::move(p2LivesDisplay));

	auto p2PointsDisplay = std::make_shared<dae::GameObject>();
	p2PointsDisplay->SetWorldPosition(5, 400);
	renderComponent = std::make_unique<RenderComponent>(p2PointsDisplay.get());
	to = std::make_unique<dae::TextComponent>(p2PointsDisplay.get(), "points", font, renderComponent.get(), SDL_Color{ 59, 172, 57 });
	pointsDisplayComponent = std::make_unique<PointsDisplayComponent>(go.get(), go->GetComponent<PointsComponent>(), to.get());
	p2PointsDisplay->AddComponent(std::move(renderComponent));
	p2PointsDisplay->AddComponent(std::move(to));
	p2PointsDisplay->AddComponent(std::move(pointsDisplayComponent));
	scene.Add(std::move(p2PointsDisplay));

	scene.Add(std::move(go));

	std::cout << "controls: \n";
	std::cout << "\tMr. hotdog:\n";
	std::cout << "\t\t moving: dPad\n";
	std::cout << "\t\t take damamge: right bumper\n";
	std::cout << "\t\t gain a point: A\n";
	std::cout << "\tPeter Pepper:\n";
	std::cout << "\t\t moving: WASD\n";
	std::cout << "\t\t take damamge: spacebar\n";
	std::cout << "\t\t gain a point: p\n";
	std::cout << "green text is for Mr hotdog and yellow text is for Peter Pepper\n";
}

int main(int, char* []) {
	
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
