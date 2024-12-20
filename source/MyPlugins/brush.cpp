#include "brush.hpp"

#include <iostream>

using namespace psapi;

BrushButton::BrushButton()
:
    ABarButton(std::make_unique<sfm::Texture>(), 1)
{
    texture_->loadFromFile("assets/brush_button.png");
    sprite_->setTexture(texture_.get());
    sprite_->setTextureRect(sfm::IntRect{vec2i{0, 0}, vec2u{96, 96}});
}

std::unique_ptr<IAction>
BrushButton::createAction(const IRenderWindow* renderWindow, const Event& event)
{
    return std::make_unique<BrushAction>(this, renderWindow, event);
}

psapi::wid_t psapi::BrushButton::getId() const
{
    return id_;
}

psapi::IWindow* psapi::BrushButton::getWindowById(psapi::wid_t id)
{
    return (id == id_) ? static_cast<AWindow*>(this) : nullptr;
}

const psapi::IWindow* psapi::BrushButton::getWindowById(psapi::wid_t id) const
{
    return (id == id_) ? static_cast<const AWindow*>(this) : nullptr;
}

psapi::vec2i psapi::BrushButton::getPos() const
{
    return pos_;
}

psapi::vec2u psapi::BrushButton::getSize() const
{
    return size_;
}

void psapi::BrushButton::setSize(const psapi::vec2u& size)
{
    size_ = size;
    //sprite_->setTextureRect(sfm::IntRect{{0, 0}, size_});
}

void psapi::BrushButton::setPos(const psapi::vec2i& pos)
{
    pos_ = pos;
    sprite_->setPosition(static_cast<float>(pos_.x),
                         static_cast<float>(pos_.y) );
}

void psapi::BrushButton::setParent(const psapi::IWindow* parent)
{
    parent_ = parent;
}

void psapi::BrushButton::forceActivate()
{
    is_active_ = true;
}

void psapi::BrushButton::forceDeactivate()
{
    is_active_ = false;
}

bool psapi::BrushButton::isActive() const
{
    return is_active_;
}

bool psapi::BrushButton::isWindowContainer() const
{
    return false;
}

void psapi::BrushButton::draw(psapi::IRenderWindow* renderWindow)
{
    renderWindow->draw(sprite_.get());
}

void psapi::BrushButton::setState(State state)
{
    state_ = state;
}

psapi::BrushButton::State psapi::BrushButton::getState() const
{
    return state_;
}


BrushAction::BrushAction(BrushButton *button, const IRenderWindow *renderWindow, const Event &event)
:
    button_         (button),
    render_window_  (renderWindow),
    event_          (event)
{
}

bool BrushAction::execute(const Key& key)
{
    return true;
}

bool BrushAction::isUndoable(const Key& key)
{
    return false;
}