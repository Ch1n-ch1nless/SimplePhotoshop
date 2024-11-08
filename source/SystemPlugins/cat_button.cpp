#include "cat_button.hpp"

#include <iostream>

using namespace sys_plugin;

bool CatButtonAction::operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event)
{
    if (!is_active_) return false;

    std::cout << "Meow!\n";
    is_active_ = false;

    return true;
}

void CatButtonAction::activate()
{
    is_active_ = true;
}

CatButton::CatButton(   std::unique_ptr<psapi::sfm::Sprite> sprite, 
                        std::unique_ptr<CatButtonAction>    action )
:
    ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<CatButton> CatButton::create()
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(CAT_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<CatButtonAction> action = std::make_unique<CatButtonAction>();

    return std::make_unique<CatButton>(std::move(sprite), std::move(action));
}

extern "C"
{
    bool   loadPlugin()
    {
        ps::ABar* tool_bar = static_cast<ps::ABar*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId)));
        tool_bar->addWindow(std::move(static_cast<std::unique_ptr<ps::AWindow>>(std::move(sys_plugin::CatButton::create()))));

        return true;
    }

    void unloadPlugin()
    {
        return;
    }
}