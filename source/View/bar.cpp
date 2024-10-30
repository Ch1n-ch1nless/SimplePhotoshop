#include "bar.hpp"

using namespace psapi;

/*=======================< ABarButton implementation >========================*/

ABarButton::ABarButton( const IBar* parent, 
                        std::unique_ptr<AButtonAction> action,
                        const psapi::vec2i &pos, 
                        const psapi::vec2u &size, 
                        const wid_t &id                         ) :
    parent_ (parent),
    pos_    (pos),
    size_   (size),
    id_     (id),
    action_ (std::move(action))
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

vec2u ABarButton::getSize() const
{
    return size_;
}

wid_t ABarButton::getId() const
{
    return id_;
}

void ABarButton::setSize(psapi::vec2u &new_size)
{
    size_ = new_size;
}

void ABarButton::setPos(psapi::vec2i &new_pos)
{
    pos_ = new_pos;
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

bool ABarButton::isActive() const
{
    return is_active_;
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

ABar::ABar(const psapi::vec2i &pos, const psapi::vec2u &size,  const psapi::vec2u &the_button_size, const size_t &rows_number, const wid_t &id) :
    pos_            (pos),
    size_           (size),
    id_             (id),
    button_size     (the_button_size),
    n_row_buttons   (rows_number)
{
}

void ABar::finishButtonDraw(IRenderWindow* renderWindow, const IBarButton* button) const
{
    return;
}

ChildInfo ABar::getNextChildInfo() const
{
    int row_index = cur_button_index / n_row_buttons;
    int col_index = cur_button_index % n_row_buttons;

    psapi::vec2i button_pos = pos_ + buttons_offset + vec2i{col_index * button_size.x, row_index * button_size.y};

    cur_button_index++;

    return ChildInfo{button_pos, vec2i{button_size.x, button_size.y}};
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
    if (is_active_ && !checkDuplicate(window->getId())) 
    {
        window->setParent(this);
        buttons_.push_back(std::move(window));
    }

    ABarButton* new_button = static_cast<ABarButton*>(window.get());

    ChildInfo new_params = getNextChildInfo();

    new_button->setPos(new_params.pos);

    vec2u size = {};

    size.x = new_params.size.x;
    size.y = new_params.size.y;

    new_button->setSize(size);
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

vec2u ABar::getSize() const
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

bool ABar::isActive() const
{
    return is_active_;
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