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
#include "LivesDisplayComponent.h"
#include "PlayerPrefab.h"
#include <iostream>
#include <vector>
#include "PlatformPrefab.h"
#include "LevelManager.h"
#include "PlaySoundCommand.h"
#include "SDLSoundSystem.h"
#include "ButtonComponent.h"
#include "TexturedGameObjectPrefab.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	constexpr float windowWidth = 416.f;
	//constexpr float windowHeight = 480.f;

	//std::cout << "controls: \n";
	//std::cout << "\tMr. hotdog:\n";
	//std::cout << "\t\t moving: dPad\n";
	//std::cout << "\t\t take damamge: right bumper\n";
	//std::cout << "\t\t gain a point: A\n";
	//std::cout << "\tPeter Pepper:\n";
	//std::cout << "\t\t moving: WASD\n";
	//std::cout << "\t\t take damamge: spacebar\n";
	//std::cout << "\t\t gain a point: p\n";
	//std::cout << "green text is for Mr hotdog and yellow text is for Peter Pepper\n";

	std::cout << "press P to play a sound\n";

	auto pSDLSoundSystem{ new dae::SDLSoundSystem() };
	pSDLSoundSystem->AddSound("../Data/sound/LoseLife.wav");
	auto playSoundCommand = std::make_unique<commands::PlaySoundCommand>(pSDLSoundSystem);

	dae::InputManager::GetInstance().AddCommand(std::move(playSoundCommand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'P'));

	//auto testButton{ std::make_unique<TexturedGameObjectPrefab>("cheese.png")->GetGameObject() };
	//auto onclick = [&]() { std::cout << "button clicked!\n"; LevelManager::GetInstance().LoadLevel(1, scene); };
	//testButton->AddComponent(std::make_unique<dae::ButtonComponent>(testButton.get(), glm::vec2(0.f, 0.f), 64.f, 14.f, onclick));
	//scene.Add(std::move(testButton));

	//logo
	auto logo{ std::make_unique<TexturedGameObjectPrefab>("burgerTimeLogo.png")->GetGameObject() };
	auto logoSize{ logo->GetComponent<RenderComponent>()->GetTextureComponent()->GetSize() };
	logo->SetLocalPosition(windowWidth / 2.f - logoSize.x / 2.f, 0.f);
	scene.Add(std::move(logo));
	
	//create font to use for buttons
	auto font{ dae::ResourceManager::GetInstance().LoadFont("PressStart2P-vaV7.ttf", 24) };

	//Single player button
	auto button1{ std::make_unique<dae::GameObject>() };
	button1->AddComponent(std::make_unique<dae::TextComponent>(button1.get(), "Single player", font));
	auto onclickButton1 = [&]() { std::cout << "button1 clicked!\n"; LevelManager::GetInstance().LoadLevel(1, scene, GameMode::singlePlayer); };
	const auto button1Size{ button1->GetComponent<RenderComponent>()->GetTextureComponent()->GetSize() };
	glm::vec2 button1Pos{ windowWidth / 2.f - button1Size.x / 2.f, 150.f };
	button1->AddComponent(std::make_unique<dae::ButtonComponent>(button1.get(), button1Pos, static_cast<float>(button1Size.x), static_cast<float>(button1Size.y), onclickButton1));
	button1->SetLocalPosition(button1Pos.x, button1Pos.y);
	scene.Add(std::move(button1));

	//Co-op button
	auto button2{ std::make_unique<dae::GameObject>() };
	button2->AddComponent(std::make_unique<dae::TextComponent>(button2.get(), "Co-op", font));
	auto onclickButton2 = [&]() { std::cout << "button2 clicked!\n"; };
	const auto button2Size{ button2->GetComponent<RenderComponent>()->GetTextureComponent()->GetSize() };
	const glm::vec2 button2Pos{ windowWidth / 2.f - button2Size.x / 2.f, 250.f };
	button2->AddComponent(std::make_unique<dae::ButtonComponent>(button2.get(), button2Pos, static_cast<float>(button2Size.x), static_cast<float>(button2Size.y), onclickButton2));
	button2->SetLocalPosition(button2Pos.x, button2Pos.y);
	scene.Add(std::move(button2));

	//Versus button
	auto button3{ std::make_unique<dae::GameObject>() };
	button3->AddComponent(std::make_unique<dae::TextComponent>(button3.get(), "Versus", font));
	auto onclickButton3 = [&]() { std::cout << "button2 clicked!\n"; };
	const auto button3Size{ button3->GetComponent<RenderComponent>()->GetTextureComponent()->GetSize() };
	glm::vec2 button3Pos{ windowWidth / 2.f - button3Size.x / 2.f, 350.f };
	button3->AddComponent(std::make_unique<dae::ButtonComponent>(button3.get(), button3Pos, static_cast<float>(button3Size.x), static_cast<float>(button3Size.y), onclickButton3));
	button3->SetLocalPosition(button3Pos.x, button3Pos.y);
	scene.Add(std::move(button3));
}

int main(int, char* []) {
	
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
