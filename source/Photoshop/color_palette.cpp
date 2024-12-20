#include "color_palette.hpp"

#include <array>
#include <iostream>

const std::array<psapi::sfm::Color, 8> PALETTE_COLORS =
{
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::Red),
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::Green),
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::Blue),
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::Yellow),
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::Cyan),
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::Magenta),
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::White),
    psapi::sfm::Color::getStandardColor(psapi::sfm::Color::Type::Black)
};

/*======================< ColorPalette implementation >=======================*/

psapi::ColorPalette::ColorPalette()
:
    ABarButton  (std::make_unique<sfm::Texture>(),
                 kColorPaletteId                  ),
    color_      (0, 0, 0, 0)
{
    cur_color = std::make_unique<sfm::RectangleShape>(48, 48);
    cur_color->setFillColor(sfm::Color::getStandardColor(psapi::sfm::Color::Type::Transparent));
    cur_color->setOutlineColor(sfm::Color::getStandardColor(psapi::sfm::Color::Type::Black));
    cur_color->setOutlineThickness(2.0);

    std::unique_ptr<sfm::RectangleShape> button = nullptr;
    for ( auto &color : PALETTE_COLORS )
    {
        button = std::make_unique<sfm::RectangleShape>(48, 48);
        button->setFillColor(color);
        colors_.push_back(std::move(button));
    }
}

std::unique_ptr<psapi::IAction> 
psapi::ColorPalette::createAction(const IRenderWindow* renderWindow, const Event& event)
{
    return std::make_unique<ColorPaletteAction>(this, renderWindow, event);
}

psapi::wid_t psapi::ColorPalette::getId() const
{
    return ABarButton::getId();
}

psapi::IWindow* psapi::ColorPalette::getWindowById(wid_t id)
{
    return ABarButton::getWindowById(id);
}

const psapi::IWindow* psapi::ColorPalette::getWindowById(wid_t id) const
{
    return getWindowById(id);
}

psapi::vec2i psapi::ColorPalette::getPos() const
{
    return ABarButton::getPos();
}

psapi::vec2u psapi::ColorPalette::getSize() const
{
    return ABarButton::getSize();
}

void psapi::ColorPalette::setSize(const vec2u& size)
{
    size_ = size;
    vec2u button_size = vec2u(size_.x / 2, size_.y / 5);
    cur_color->setSize(vec2u(size_.x, button_size.y));
    vec2i row_pos = vec2i(cur_color->getPosition().x, cur_color->getPosition().y);

    for ( int i = 0; i < 4; i++ )
    {
        row_pos += vec2i(0, button_size.y);
        vec2i button_pos = row_pos;
        for ( int j = 0; j < 2; j++ )
        {
            colors_[i * 2 + j]->setSize(button_size);
            colors_[i * 2 + j]->setPosition(button_pos);
            button_pos += vec2i(button_size.x, 0);
        }
    }
}

void psapi::ColorPalette::setPos(const vec2i& pos)
{
    vec2i diff = pos - pos_;
    pos_ = pos;
    for ( auto &color : colors_ )
    {
        color->setPosition(vec2i(color->getPosition().x, color->getPosition().y) + diff);
    }
    cur_color->setPosition(vec2i(cur_color->getPosition().x, cur_color->getPosition().y) + diff);
}

void psapi::ColorPalette::setParent(const IWindow* parent)
{
    ABarButton::setParent(parent);
}

void psapi::ColorPalette::forceActivate()
{
    ABarButton::forceActivate();
}

void psapi::ColorPalette::forceDeactivate()
{
    ABarButton::forceDeactivate();
}

bool psapi::ColorPalette::isActive() const
{
    return ABarButton::isActive();
}

bool psapi::ColorPalette::isWindowContainer() const
{
    return ABarButton::isWindowContainer();
}


void psapi::ColorPalette::draw(IRenderWindow* renderWindow)
{
    cur_color->draw(renderWindow);
    for ( auto &color : colors_ )
    {
        color->draw(renderWindow);
    }
}


void psapi::ColorPalette::setState(State state)
{
    ABarButton::setState(state);
}

psapi::IBarButton::State psapi::ColorPalette::getState() const
{
    return ABarButton::getState();
}


psapi::sfm::Color psapi::ColorPalette::getColor() const
{
    return color_;
}

void psapi::ColorPalette::setColor(const sfm::Color &color)
{
    color_ = color;
}


std::unique_ptr<psapi::IColorPalette> psapi::ColorPalette::create()
{
    static std::unique_ptr<ColorPalette> color_palette = std::make_unique<ColorPalette>();
    return std::move(color_palette);
}

/*============================================================================*/

/*===================< ColorPaletteAction implementation >====================*/

psapi::ColorPaletteAction::ColorPaletteAction(ColorPalette* palette, const IRenderWindow* renderWindow, const Event& event)
:
    render_window_  (renderWindow),
    palette_        (palette),
    event_          (event)
{
}

bool psapi::ColorPaletteAction::execute(const Key& key)
{
    psapi::vec2i mouse_position = sfm::Mouse::getPosition(render_window_);
    mouse_position -= palette_->pos_;

    bool is_in_palette = (0 <= mouse_position.x) && (mouse_position.x < palette_->size_.x) &&
                         (0 <= mouse_position.y) && (mouse_position.y < palette_->size_.y);

    if (is_in_palette)
    {
        mouse_position += palette_->pos_;

        for (auto& rectangle : palette_->colors_)
        {
            vec2i rect_pos  = vec2i{static_cast<int>(rectangle->getPosition().x),
                                    static_cast<int>(rectangle->getPosition().y) };

            vec2u rect_size = rectangle->getSize();

            if ((rect_pos.x <= mouse_position.x) && (mouse_position.x < (rect_pos.x + rect_size.x)) &&
                (rect_pos.y <= mouse_position.y) && (mouse_position.y < (rect_pos.y + rect_size.y))    )
            {
                if (event_.type == sfm::Event::MouseButtonPressed)
                {
                    palette_->color_ = rectangle->getFillColor();
                    palette_->cur_color->setFillColor(palette_->color_);

                    return true;
                }
                
                palette_->cur_color->setFillColor(rectangle->getFillColor());

                return false;
            }
        }

        return false;
    }

    palette_->cur_color->setFillColor(palette_->color_);

    return false;
}

bool psapi::ColorPaletteAction::isUndoable(const Key& key)
{
    return false;
}

/*============================================================================*/