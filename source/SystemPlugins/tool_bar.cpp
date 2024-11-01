#include "tool_bar.hpp"

using namespace sys_plugin;
using namespace ps;
using namespace psapi;

/*=========================< ToolBar implementation >=========================*/

ToolBar::ToolBar(   std::unique_ptr<sfm::Sprite> background_sprite, 
                    std::unique_ptr<sfm::Sprite> hover_button,
                    std::unique_ptr<sfm::Sprite> press_button,
                    std::unique_ptr<sfm::Sprite> release_button,
                    const vec2i    &bar_position,
                    const vec2u    &bar_size,
                    const vec2u    &button_size, 
                    const size_t   &number_buttons_in_row,
                    const wid_t    &id                                     )
:
    ABar(   std::move(background_sprite), 
            std::move(hover_button), 
            std::move(press_button), 
            std::move(release_button), 
            bar_position, 
            bar_size, 
            button_size, 
            number_buttons_in_row, 
            id                      )
{
}

std::unique_ptr<ToolBar> ToolBar::create(const size_t width, const size_t height)
{
    static std::unique_ptr<sfm::Texture> back_ground_texture = std::make_unique<sfm::Texture>();
    back_ground_texture->loadFromFile(TOOL_BAR_BACKGROUND);

    std::unique_ptr<sfm::Sprite> background = std::make_unique<sfm::Sprite>();
    background->setTexture(back_ground_texture.get());

    static std::unique_ptr<sfm::Texture> hover_texture = std::make_unique<sfm::Texture>();
    hover_texture->loadFromFile(TOOL_BAR_BUTTON_HOVERED);

    std::unique_ptr<sfm::Sprite> hover = std::make_unique<sfm::Sprite>();
    hover->setTexture(hover_texture.get());

    static std::unique_ptr<sfm::Texture> press_texture = std::make_unique<sfm::Texture>();
    press_texture->loadFromFile(TOOL_BAR_BUTTON_PRESSED);

    std::unique_ptr<sfm::Sprite> press = std::make_unique<sfm::Sprite>();
    press->setTexture(press_texture.get());

    static std::unique_ptr<sfm::Texture> release_texture = std::make_unique<sfm::Texture>();
    release_texture->loadFromFile(TOOL_BAR_BUTTON_RELEASED);

    std::unique_ptr<sfm::Sprite> release = std::make_unique<sfm::Sprite>();
    release->setTexture(release_texture.get());

    vec2i new_position = {};
    new_position.x = ToolbarTopLeftPos.x * width; 
    new_position.y = ToolbarTopLeftPos.y * height;

    vec2u new_size = {};
    new_size.x = ToolbarSize.x * width;
    new_size.y = ToolbarSize.y * height;

    size_t number_buttons_in_row = 3;

    vec2u button_size = {};
    button_size.x = new_size.x / number_buttons_in_row;
    button_size.y = new_size.x / number_buttons_in_row;

    wid_t id = kToolBarWindowId;

    return std::make_unique<ToolBar>(std::move(background), std::move(hover), std::move(press), std::move(release), 
                                     new_position, new_size, button_size, number_buttons_in_row, id                 );
}

/*============================================================================*/
