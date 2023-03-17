#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "TextureComponent.h"

namespace dae
{
	class GameObject;
	class TextureComponent;
}

class RenderComponent final : public Component
{
public:
	RenderComponent(dae::GameObject* owner);
	RenderComponent(dae::GameObject* owner, const std::string& textureFilename);
	RenderComponent(dae::GameObject* owner, dae::TextureComponent* textureComponent);

	~RenderComponent();
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	virtual void Update() override {};
	virtual void Render() const override;

	void SetTextureComponent(const std::string& filename);
	void SetTextureComponent(dae::TextureComponent* textureComponent);

private:
	dae::TextureComponent* m_TextureComponent;
};