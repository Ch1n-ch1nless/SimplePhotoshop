#include "pencil_button.hpp"

#include <iostream>

using namespace sys_plugin;

PencilAction::PencilAction(psapi::ICanvas* canvas)
:
    canvas_(canvas)
{
}

void PencilAction::activate()
{
    is_active_ = true;
}

bool PencilAction::operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event)
{
    if (is_active_ && static_cast<ps::Canvas*>(canvas_)->isPressed())
    {
        psapi::vec2i mouse_pos = psapi::sfm::Mouse::getPosition(render_window);

        canvas_->getTempLayer()->setPixel(mouse_pos, psapi::sfm::Color{0, 0, 0, 255});

        return true;
    }

    return false;
}

PencilButton::PencilButton(std::unique_ptr<psapi::sfm::Sprite> sprite, std::unique_ptr<PencilAction> action )
:
    ps::ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<PencilButton> PencilButton::create(psapi::ICanvas* canvas)
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(PENCIL_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<PencilAction> action = std::make_unique<PencilAction>(canvas);

    return std::make_unique<PencilButton>(std::move(sprite), std::move(action));
}