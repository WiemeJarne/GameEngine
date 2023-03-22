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
	delete m_TextureComponent;
}

void RenderComponent::Render() const
{
	auto pos = m_Owner->GetWorldPos();

	if (m_TextureComponent)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_TextureComponent, pos.x, pos.y);
	}
}

void RenderComponent::SetTextureComponent(const std::string& filename)
{
	m_TextureComponent = new dae::TextureComponent(m_Owner, filename);
}

void RenderComponent::SetTextureComponent(dae::TextureComponent* textureComponent)
{
	delete m_TextureComponent;
	m_TextureComponent = textureComponent;
}