#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <iostream>

RenderComponent::RenderComponent(dae::GameObject* owner)
	: Component(owner)
{}

RenderComponent::RenderComponent(dae::GameObject* owner, const std::string& textureFilename)
	: Component(owner)
{
	SetTextureComponent(textureFilename);
}

RenderComponent::RenderComponent(dae::GameObject* owner, dae::TextureComponent* textureComponent)
	: Component(owner)
{
	SetTextureComponent(textureComponent);
}

RenderComponent::~RenderComponent()
{
	delete m_pTextureComponent;
}

void RenderComponent::Render() const
{
	auto pos = m_pOwner->GetWorldPos();

	if (m_pTextureComponent)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_pTextureComponent, pos.x, pos.y);
	}
}

void RenderComponent::SetTextureComponent(const std::string& filename)
{
	m_pTextureComponent = new dae::TextureComponent(m_pOwner, filename);
}

void RenderComponent::SetTextureComponent(dae::TextureComponent* textureComponent)
{
	delete m_pTextureComponent;
	m_pTextureComponent = textureComponent;
}