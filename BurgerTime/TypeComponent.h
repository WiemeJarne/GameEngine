#pragma once
#include "Component.h"
#include "Font.h"

class TypeComponent : public Component
{
public:
	TypeComponent(dae::GameObject* pOwner, std::shared_ptr<dae::Font> font);
	
	void Update() {}
	void Render() const {}
	void RenderImGui() {}
};