#include "bar.hpp"

using namespace psapi;

/*=======================< ABarButton implementation >========================*/

ABarButton::ABarButton(const wid_t& id, const vec2i& pos, const vec2i& size) :
    id_     (id),
    pos_    (pos),
    size_   (size)

{
}

IWindow* ABarButton::getWindowById(wid_t id)
{   
    return (id_ == id) ? this : nullptr;
}

const IWindow* ABarButton::getWindowById(wid_t id) const
{   
    return (id_ == id) ? this : nullptr;
}

vec2i ABarButton::getPos() const
{
    return pos_;
}

vec2i ABarButton::getSize() const
{
    return size_;
}

wid_t ABarButton::getId() const
{
    return id_;
}

void ABarButton::setParent(const IWindow* parent)
{
    parent_ = parent;
}

void ABarButton::forceDeactivate()
{
    is_active_ = false;
}

void ABarButton::forceActivate()
{
    is_active_ = true;
}

void ABarButton::setState(State state)
{
    state_ = state;
}

ABarButton::State ABarButton::getState() const
{
    return state_;
}

/*============================================================================*/

/*===========================< ABar implementation >==========================*/

ABar::ABar(const wid_t& id = kInvalidWindowId, const vec2i& pos, const vec2i& size) :
    id_     (id),
    pos_    (pos),
    size_   (size)
{
}

IWindow* ABar::getWindowById(wid_t id)
{
    for (auto& button : buttons_)
    {
        if (button->getId() == id)
        {
            return button.get();
        }
    }

    return (id_ == id) ? this : nullptr;
}

const IWindow* ABar::getWindowById(wid_t id) const
{
    for (const auto& button : buttons_)
    {
        if (button->getId() == id)
        {
            return button.get();
        }
    }

    return (id_ == id) ? this : nullptr;
}

void ABar::addWindow(std::unique_ptr<IWindow> window)
{
    if (is_active_ && !checkDuplicate(window->getId())) buttons_.push_back(std::move(window));
}

void ABar::removeWindow(wid_t id)
{
    if (is_active_)
    {
        for (auto it = buttons_.begin(); it != buttons_.end(); it++) {
            if ((*it)->getId() == id) {
                buttons_.erase(it);
                return;
            }
        }
    }
}

vec2i ABar::getPos()  const
{
    return pos_;
}

vec2i ABar::getSize() const
{
    return size_;
}

wid_t ABar::getId() const
{
    return id_;
}

void ABar::setParent(const IWindow* parent)
{
    if (is_active_) parent_ = parent;
}

void ABar::forceDeactivate()
{
    is_active_ = false;
}

void ABar::forceActivate()
{
    is_active_ = true;
}


bool ABar::checkDuplicate(const wid_t& id)
{
    for (auto& button : buttons_)
    {
        if (button->getId() == id)
        {
            return true;
        }
    }

    return false;
}

void ABar::drawChildren(IRenderWindow* renderWindow)
{
    for (auto& button : buttons_)
    {
        button->draw(renderWindow);
    }
}

bool ABar::updateChildren(const IRenderWindow* renderWindow, const Event& event)
{
    bool result = false;

    for (auto& button : buttons_)
    {
        result |= button->update(renderWindow, event);
    }

    return result;
}

/*============================================================================*/