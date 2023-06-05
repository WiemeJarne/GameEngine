#include "TypeCommand.h"
#include "TextureComponent.h"

commands::TypeCommand::TypeCommand(char charToType, dae::TextComponent* textComponentToTypeTo)
	: m_CharToType{ charToType }
	, m_pTextComponentToTypeTo{ textComponentToTypeTo }
{
	m_pTextComponentOwner = m_pTextComponentToTypeTo->GetOwner();
}

void commands::TypeCommand::Execute()
{
	auto currentText{ m_pTextComponentToTypeTo->GetText() };

	auto textLenght{ currentText.length() };

	if (m_CharToType == '\b')
	{
		if (textLenght <= 1)
			return;

		m_pTextComponentToTypeTo->SetText(currentText.substr(0, textLenght - 2) + '_');
		RecenterAlongXAxis();
	}
	else
	{
		m_pTextComponentToTypeTo->SetText(currentText.substr(0, textLenght - 1) + m_CharToType + '_');
		RecenterAlongXAxis();
	}
}

void commands::TypeCommand::RecenterAlongXAxis()
{
	auto textureSize{ m_pTextComponentToTypeTo->GetTextureComponent()->GetSize() };
	auto& sceneManager{ dae::SceneManager::GetInstance() };
	m_pTextComponentOwner->SetLocalPosition(sceneManager.GetScenesWidth() / 2.f - textureSize.x / 2.f, m_pTextComponentOwner->GetLocalPos().y);
}