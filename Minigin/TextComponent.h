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
		TextComponent(dae::GameObject* owner, const std::string& text, std::shared_ptr<Font> font, RenderComponent* renderComponent);
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() override {};

		void SetText(const std::string& text);

	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		RenderComponent* m_RenderComponent;

		void CreateTextTexture();
	};
}
