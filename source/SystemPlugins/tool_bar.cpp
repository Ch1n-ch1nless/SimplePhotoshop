#include "tool_bar.hpp"

#include <iostream>
#include <cassert>

/*======================< ToolBarButton implementation >======================*/

sys_plugin::ToolBarButton::ToolBarButton(   const psapi::IBar *parent, 
                                            std::unique_ptr<psapi::AButtonAction> action, 
                                            const char **texture_files, 
                                            const psapi::vec2i &pos, 
                                            const psapi::vec2u &size, 
                                            const psapi::wid_t &id                          )
:
    ABarButton  (parent, std::move(action), pos, size, id),
    texture_    (),
    sprite_     ()
{
    if (texture_files == nullptr)
    {
        assert(false && "ERROR!!! Button can not load textures!\n");
    }

    for (int i = 0; i < 4; i++)
    {
        if (texture_files[i] == nullptr)
        {
            assert(false && "ERROR!!! Invalid texture_files!\n");
        }

        if (texture_[i].loadFromFile(texture_files[i]) == false)
        {
            std::cerr << "ERROR!!! Texture can not load the file!\n";
        }
    }
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

sys_plugin::ToolBar::ToolBar(   const psapi::vec2i &pos, 
                                const psapi::vec2u &size, 
                                const psapi::vec2u &the_button_size, 
                                const size_t &rows_number, 
                                const std::string &background       )
:
    ABar    (pos, size, the_button_size, rows_number, psapi::kToolBarWindowId),
    texture_(),
    sprite_ ()
{
    if (!texture_.loadFromFile(background))
    {
        std::cerr << "ERROR!!! ToolBar can not load the background texture!\n";
        
        psapi::sfm::Color* pixels = new psapi::sfm::Color[size.x * size.y];

        for (unsigned int y = 0; y < size.y; y++)
        {
            for (unsigned int x = 0; x < size.x; x++)
            {
                pixels[x + y * size.x] = psapi::sfm::Color{92, 17, 2, 255}; // TODO: Magic constant!!!
            }
        }

        texture_.create(size.x, size.y);
        texture_.update(pixels);

        sprite_.setTexture(&texture_);
        return;
    }
    sprite_.setTexture(&texture_);
}

void sys_plugin::ToolBar::draw(psapi::IRenderWindow *renderWindow)
{
    sprite_.setPosition(static_cast<float>(pos_.x), static_cast<float>(pos_.y));
    sprite_.draw(renderWindow);

    drawChildren(renderWindow);
}

bool sys_plugin::ToolBar::update(const psapi::IRenderWindow *renderWindow, const psapi::Event &event)
{
    return updateChildren(renderWindow, event);
}


/*============================================================================*/
