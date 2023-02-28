#pragma once
#include <memory>
#include <string>
#include "Component.h"

namespace dae
{
	class GameObject;
	class TextureComponent;
}


class RenderComponent final : public Component
{
public:
	RenderComponent() = default;
	RenderComponent(const std::string& textureFilename);
	RenderComponent(std::shared_ptr<dae::TextureComponent> textureComponent);

	virtual ~RenderComponent();
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	virtual void Update() override;
	virtual void Render(const dae::GameObject& go) const override;

	void SetTextureComponent(const std::string& filename);
	void SetTextureComponent(std::shared_ptr<dae::TextureComponent> textureComponent);

private:
	std::shared_ptr<dae::TextureComponent> m_TextureComponent;
};

