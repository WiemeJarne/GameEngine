#pragma once
#include "Command.h"

namespace dae
{
    class ZoomCameraCommand final : public Command
    {
    public:
        //example: when zoomSpeed is 1 and to current zoom is 1 -> when this command gets executed onces the current zoom will be 2
        ZoomCameraCommand(float zoomSpeed);

        void Execute() override;

    private:
        const float m_ZoomSpeed{};
    };
}