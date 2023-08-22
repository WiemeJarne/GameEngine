#pragma once
#include "Command.h"
#include "glm/vec2.hpp"

namespace dae
{
    class MoveCameraCommand final : public Command
    {
    public:
        MoveCameraCommand(const glm::vec2& direction, float moveSpeed);

        void Execute() override;

    private:
        const glm::vec2 m_Direction{};
        const float m_MoveSpeed{};
    };
}