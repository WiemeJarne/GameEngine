#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Component.h"

class RenderComponent;

namespace dae
{
	class Font;
	class TextureComponent;
	class TextComponent final : public Component
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<RenderComponent> renderComponent);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update() override;

		void SetText(const std::string& text);
		const std::shared_ptr<TextureComponent>& GetTexture() const { return m_textTexture; }

	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<TextureComponent> m_textTexture;
		std::shared_ptr<RenderComponent> m_RenderComponent;

		void CreateTextTexture();
	};
}
