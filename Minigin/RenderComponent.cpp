#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"

RenderComponent::RenderComponent(const std::string& textureFilename)
{
	SetTextureComponent(textureFilename);
}

RenderComponent::RenderComponent(std::shared_ptr<dae::TextureComponent> textureComponent)
{
	SetTextureComponent(textureComponent);
}

RenderComponent::~RenderComponent() = default;

void RenderComponent::Update() {}

void RenderComponent::Render(const dae::GameObject& go) const
{
	const auto& pos = go.GetTransform().GetPosition();

	if (m_TextureComponent)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_TextureComponent, pos.x, pos.y);
	}
}

void RenderComponent::SetTextureComponent(const std::string& filename)
{
	m_TextureComponent = std::make_shared<dae::TextureComponent>(filename);
}

void RenderComponent::SetTextureComponent(std::shared_ptr<dae::TextureComponent> textureComponent)
{
	m_TextureComponent = textureComponent;
}