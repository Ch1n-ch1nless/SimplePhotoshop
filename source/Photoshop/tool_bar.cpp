#include "tool_bar.hpp"

psapi::ToolBar::ToolBar()
:
    ABar(std::make_unique<sfm::Sprite>(),
         std::make_unique<sfm::Sprite>(),
         std::make_unique<sfm::Sprite>(),
         std::make_unique<sfm::Sprite>(),
         getToolbarIntRect().pos,
         getToolbarIntRect().size,
         {10, 10},
         {6, 6},
         {64, 64},
         2,
         kToolBarWindowId)
{
    static std::unique_ptr<sfm::ITexture> background        = sfm::Texture::create();
    static std::unique_ptr<sfm::ITexture> hovered_button    = sfm::Texture::create();
    static std::unique_ptr<sfm::ITexture> pressed_button    = sfm::Texture::create();
    static std::unique_ptr<sfm::ITexture> released_button   = sfm::Texture::create();

    background->loadFromFile("assets/tool_bar_background.png");
    hovered_button->loadFromFile("assets/hovered_skin.png");
    pressed_button->loadFromFile("assets/pressed_skin.png");
    released_button->loadFromFile("assets/released_skin.png");

    background_->setTexture(background.get());
    hovered_->setTexture(hovered_button.get());
    pressed_->setTexture(pressed_button.get());
    released_->setTexture(released_button.get());

    setSize(size_);
    setPos(pos_);
}

void psapi::ToolBar::finishButtonDraw(IRenderWindow* renderWindow, const IBarButton* button) const
{
    return;
}