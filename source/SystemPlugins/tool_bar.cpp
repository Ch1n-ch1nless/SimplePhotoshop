#include "tool_bar.hpp"

#include <iostream>

/*======================< ToolBarButton implementation >======================*/

sys_plugin::ToolBarButton::ToolBarButton(const psapi::vec2i &pos, const psapi::vec2u &size, const psapi::wid_t& id) :
    ABarButton(pos, size, id) 
{
}

void sys_plugin::ToolBarButton::draw(psapi::IRenderWindow* renderWindow) const
{
    sprite_.draw(renderWindow);
}

bool sys_plugin::ToolBarButton::update(const psapi::IRenderWindow* renderWindow, const psapi::Event& event)
{
    psapi::vec2i mouse_pos = {}; 

    int texture_id = -1;

    switch (event.type)
    {
        case psapi::sfm::Event::EventType::MouseButtonPressed:
            mouse_pos.x = event.mouseButton.x;
            mouse_pos.y = event.mouseButton.y;
            texture_id  = 0;
            break;
        
        case psapi::sfm::Event::EventType::MouseButtonReleased:
            mouse_pos.x = event.mouseButton.x;
            mouse_pos.y = event.mouseButton.y;
            texture_id  = 1;
            break;

        case psapi::sfm::Event::EventType::MouseMoved:
            mouse_pos.x = event.mouseMove.x;
            mouse_pos.y = event.mouseMove.y;
            texture_id  = 2;
            break;
        
        default:
            texture_id = 3;
            break;
    }

    mouse_pos -= pos_;

    if (0 <= mouse_pos.x && mouse_pos.x <= size_.x &&
        0 <= mouse_pos.y && mouse_pos.y <= size_.y      )
    {
        if (texture_id != -1) sprite_.setTexture(texture_ + texture_id);
    }
}

bool sys_plugin::ToolBarButton::loadTextures(const char** texture_files)
{
    bool is_loaded = true;

    if (texture_files == nullptr) return false;

    for (int i = 0; i < 4; i++)
    {
        if (texture_files[i] == nullptr) return false;

        is_loaded = texture_[i].loadFromFile(texture_files[i]);
        if (is_loaded == false) return false;
    }

    return true;
}

/*============================================================================*/

/*=========================< ToolBar implementation >=========================*/



/*============================================================================*/
