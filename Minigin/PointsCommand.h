#pragma once
#include "Command.h"
#include "PointsComponent.h"

namespace commands
{
	class PointsCommmand : public Command
	{
	public:
		PointsCommmand(dae::GameObject* go, int amountOfPointsToAddPerExecution);

		virtual ~PointsCommmand() = default;
		PointsCommmand(const PointsCommmand&) = delete;
		PointsCommmand(PointsCommmand&&) = delete;
		PointsCommmand& operator=(const PointsCommmand&) = delete;
		PointsCommmand& operator=(PointsCommmand&&) = delete;

		void Execute() override;

	private:
		PointsComponent* m_PointsComponent;
		const int m_AmountOfPointsToAdd;
	};
}