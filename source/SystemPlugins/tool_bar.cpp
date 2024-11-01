#include "tool_bar.hpp"

#include <iostream>
/*
using namespace sys_plugin;
using namespace psapi;

void ToolBar::updateSprite(sfm::Sprite& sprite, ChildInfo& params)
{
    sprite.setPosition(params.pos.x, params.pos.y);

    vec2u cur_size = sprite.getSize();

    sprite.setScale((static_cast<float>(params.size.x) / static_cast<float>(cur_size.x)), (static_cast<float>(params.size.y) / static_cast<float>(cur_size.y)));
}

void ToolBar::updateSprite(sfm::Sprite& sprite, sfm::Texture& texture, const char* file, ChildInfo& params)
{
    if (!texture.loadFromFile(file))
    {
        std::cerr << "ERROR!!! File \'" << file << "\' can not be loaded!\n";
    }

    sprite.setTexture(&texture);

    updateSprite(sprite, params);
}

ToolBar::ToolBar()
:
    back_texture_(),
    background_(),
    hover_texture_(),
    button_is_hovered_(),
    pressed_texture(),
    button_is_pressed_(),
    released_texture(),
    button_is_released_()
{
    id_ = kToolBarWindowId;

    pos_    = getRootWindow()->getPos();
    size_   = getRootWindow()->getSize();

    pos_.x *= ToolbarTopLeftPos.x;
    pos_.y *= ToolbarTopLeftPos.y;

    size_.x *= ToolbarSize.x;
    size_.y *= ToolbarSize.y;

    ChildInfo params = {pos_, {size_.x, size_.y}};

    updateSprite(background_, back_texture_, TOOL_BAR_BACKGROUND, params);
    updateSprite(button_is_hovered_, hover_texture_, TOOL_BAR_BUTTON_HOVERED, params);
    updateSprite(button_is_pressed_, pressed_texture, TOOL_BAR_BUTTON_PRESSED, params);
    updateSprite(button_is_released_, released_texture, TOOL_BAR_BUTTON_RELEASED, params);

    button_offset.x = size_.x / n_row_buttons;
    button_offset.y = size_.x / n_row_buttons;
}

ChildInfo ToolBar::getNextChildInfo() const
{
    int row_index = cur_button_index / n_row_buttons;
    int col_index = cur_button_index % n_row_buttons;

    psapi::vec2i button_pos = pos_ + vec2i{col_index * button_offset.x, row_index * button_offset.y};

    cur_button_index++;

    return ChildInfo{button_pos, vec2i{button_scale.x * button_offset.x, button_scale.y * button_offset.y}};
}

void ToolBar::addWindow(std::unique_ptr<IWindow> window)
{
    if (is_active_ && !checkDuplicate(window->getId())) 
    {
        ps::ABarButton* new_button = static_cast<ps::ABarButton*>(static_cast<ps::AWindow*>(window.get()));

        ChildInfo new_params = getNextChildInfo();

        new_button->setPos(new_params.pos);

        vec2u size = {};

        size.x = new_params.size.x;
        size.y = new_params.size.y;

        new_button->setSize(size);

        window->setParent(static_cast<AWindow*>(this));

        windows_.push_back(std::move(window));
    }
}
*/