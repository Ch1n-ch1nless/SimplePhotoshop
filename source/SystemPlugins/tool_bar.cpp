#include "tool_bar.hpp"

#include <iostream>

/*======================< ToolBarButton implementation >======================*/



/*============================================================================*/

/*=========================< ToolBar implementation >=========================*/

sys_plugin::ToolBar::ToolBar(const psapi::vec2i& pos, const psapi::vec2i& size, const std::string& background) :
    psapi::ABar(pos, size, psapi::kToolBarWindowId),
    texture_    (),
    sprite_     ()
{
    if (!texture_.loadFromFile(background))
    {
        std::cerr << "ERROR!!! ToolBar can not load the background texture!\n";
        texture_.create(size.x, size.y);
        sprite_.setTexture(&texture_);
        sprite_.setColor({255, 0, 0, 255});
        return;
    }

    sprite_.setTexture(&texture_);
}

sys_plugin::ToolBar::~ToolBar()
{
}

void sys_plugin::ToolBar::draw(psapi::IRenderWindow* renderWindow)
{
    renderWindow->draw(&sprite_);

    drawChildren(renderWindow);
}

bool sys_plugin::ToolBar::update(const psapi::IRenderWindow* renderWindow, const psapi::Event& event)
{
    return updateChildren(renderWindow, event);
}

psapi::ChildInfo sys_plugin::ToolBar::getNextChildInfo() const
{
    return psapi::ChildInfo{pos_, size_};
}

/*============================================================================*/