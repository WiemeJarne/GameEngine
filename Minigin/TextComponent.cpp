#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<RenderComponent> renderComponent)
	: m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_textTexture(nullptr), m_RenderComponent(renderComponent)
{ 
	CreateTextTexture();
}

void dae::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		CreateTextTexture();
		m_needsUpdate = false;
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::CreateTextTexture()
{
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_textTexture = std::make_shared<TextureComponent>(texture);

	if (m_RenderComponent)
	{
		m_RenderComponent->SetTextureComponent(m_textTexture);
	}
}