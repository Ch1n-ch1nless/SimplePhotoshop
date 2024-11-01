#include "bar.hpp"

#include <iostream>

using namespace ps;

/*=======================< ABarButton implementation >========================*/

ABarButton::ABarButton( std::unique_ptr<psapi::sfm::Sprite> sprite, 
                        std::unique_ptr<ABarAction>         action,
                        const IWindow*                      bar_parent  )
:
    sprite_ (std::move(sprite)),
    action_ (std::move(action))
{
    id_         = psapi::kInvalidWindowId;
    parent_     = bar_parent;
    pos_        = {0, 0};
    size_       = {1, 1};
    is_active_  = true;
}

void ABarButton::draw(IRenderWindow* render_window)
{
    sprite_->setPosition(static_cast<float>(pos_.x), static_cast<float>(pos_.y));

    vec2u cur_size = sprite_->getSize();

    float new_scaleX = static_cast<float>(size_.x) / static_cast<float>(cur_size.x);
    float new_scaleY = static_cast<float>(size_.y) / static_cast<float>(cur_size.y);

    sprite_->setScale(new_scaleX, new_scaleY);

    sprite_->draw(render_window);

    const ABar* bar = static_cast<const ABar*>(static_cast<const AWindow*>(parent_));

    drawChildren(render_window);

    bar->finishButtonDraw(render_window, this);
}

bool ABarButton::update(const IRenderWindow* render_window, const Event& event)
{
    vec2i mouse_pos = psapi::sfm::Mouse::getPosition(render_window);

    mouse_pos -= pos_;

    if (0 <= mouse_pos.x && mouse_pos.x <= size_.x &&
        0 <= mouse_pos.y && mouse_pos.y <= size_.y      )
    {
        bool result = true;

        switch (event.type)
        {
        case Event::EventType::MouseButtonPressed :
            switch (event.mouseButton.button)
            {
            case psapi::sfm::Mouse::Button::Left :
                action_->operator()(render_window, event);
                break;
            
            case psapi::sfm::Mouse::Button::Right :
                activeChildren(render_window, event);
                break;

            default:
                break;
            }

            state_ = State::Press;
            break;

        case Event::EventType::MouseButtonReleased :
            state_ = State::Released;
            break;

        case Event::EventType::MouseMoved:
            state_ = State::Hover;
            break;
        
        default:
            result = false;
            break;
        }

        return result;
    }

    state_  = State::Normal;
    return false;
}


void ABarButton::addWindow(std::unique_ptr<IWindow> window)
{
    (static_cast<AWindowVector*>(this))->addWindow(std::move(window));
}

void ABarButton::removeWindow(wid_t id)
{
    (static_cast<AWindowVector*>(this))->removeWindow(id);
}

wid_t ABarButton::getId() const
{
    return id_;
}

psapi::IWindow* ABarButton::getWindowById(wid_t id)
{
    return (static_cast<AWindowVector*>(this))->getWindowById(id);
}

const psapi::IWindow* ABarButton::getWindowById(wid_t id) const
{
    return (static_cast<const AWindowVector*>(this))->getWindowById(id);
}

vec2i ABarButton::getPos() const
{
    return pos_;
}

vec2u ABarButton::getSize() const
{
    return size_;
}

void ABarButton::setParent(const IWindow* parent)
{
    parent_ = parent;
}

void ABarButton::forceActivate()
{
    is_active_ = true;
}

void ABarButton::forceDeactivate()
{
    is_active_ = false;
}

bool ABarButton::isActive() const
{
    return is_active_;
}

bool ABarButton::isWindowContainer() const
{
    return true;
}


void ABarButton::drawChildren(IRenderWindow* render_window)
{
    for (auto& window : windows_)
    {
        if (window->isActive())
        {
            window->draw(render_window);
        }
    }
}

bool ABarButton::updateChildren(const IRenderWindow* render_window, const Event& event)
{
    bool result = false;

    for (auto& window : windows_)
    {
        if (window->isActive())
        {
            result |= window->update(render_window, event);
        }
    }

    return result;
}

void ABarButton::activeChildren(const IRenderWindow* render_window, const Event& event)
{
    for (auto& window : windows_)
    {
        window->forceActivate();
    }
}

void ABarButton::setState(State state)
{
    state_ = state;
}

psapi::IBarButton::State ABarButton::getState() const
{
    return state_;
}

void ABarButton::setSize(const vec2u &size)
{
    size_ = size;
}

void ABarButton::setPos(const vec2i &position)
{
    pos_ = position;
}

/*============================================================================*/

/*==========================< ABar implementation >===========================*/

ABar::ABar( std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
            std::unique_ptr<psapi::sfm::Sprite> hover_button,
            std::unique_ptr<psapi::sfm::Sprite> press_button,
            std::unique_ptr<psapi::sfm::Sprite> release_button,
            const vec2i    &bar_position,
            const vec2u    &bar_size,
            const vec2u    &button_size, 
            const size_t   &number_buttons_in_row,
            const wid_t    &id                                     )
:
    background_     (std::move(background_sprite)),
    hover_button_   (std::move(hover_button)),
    press_button_   (std::move(press_button)),
    release_button_ (std::move(release_button)),
    button_size_    (button_size),
    n_row_buttons_  (number_buttons_in_row)
{
    pos_        = bar_position;
    size_       = bar_size;
    id_         = id;
    is_active_  = true;

    cur_button_index = 0;
}

void ABar::drawChildren(IRenderWindow* render_window)
{
    for (auto &window : windows_)
    {
        window->draw(render_window);
    }
}

void ABar::handleDoubleAction()
{
    ssize_t last_active = last_active_button_;

    int n_active_buttons = 0;
    ssize_t new_active = -1;

    for (size_t i = 0; i < windows_.size(); i++)
    {
        ABarButton* ptr = static_cast<ABarButton*>(static_cast<AWindow*>(windows_[i].get()));

        if (ptr->getState() == psapi::IBarButton::State::Released)
        {
            n_active_buttons++; 
            new_active = static_cast<ssize_t>(i);
        }
    }

    if (n_active_buttons > 1) 
    {
        ABarButton* ptr = static_cast<ABarButton*>(static_cast<AWindow*>(windows_[(size_t)last_active].get()));
        ptr->setState(psapi::IBarButton::State::Normal);
    }
    else if (n_active_buttons == 1) 
    {
        last_active_button_ = new_active;
    }
}

bool ABar::updateChildren(const IRenderWindow* render_window, const Event& event)
{   
    bool result = false;

    for (auto &window : windows_)
    {
        result |= window->update(render_window, event);
    }

    handleDoubleAction();

    return result;
}

void ABar::draw(IRenderWindow* render_window)
{
    background_->setPosition(static_cast<float>(pos_.x), static_cast<float>(pos_.y));

    vec2u cur_size = background_->getSize();

    float new_scaleX = static_cast<float>(size_.x) / static_cast<float>(cur_size.x);
    float new_scaleY = static_cast<float>(size_.y) / static_cast<float>(cur_size.y);

    background_->setScale(new_scaleX, new_scaleY);

    background_->draw(render_window);

    drawChildren(render_window);
}

bool ABar::update(const IRenderWindow* render_window, const Event &event)
{   
    if (!is_active_)
    {
        return false;
    }

    return updateChildren(render_window, event);
}

void ABar::addWindow(std::unique_ptr<IWindow> window)
{
    if (is_active_)
    {
        psapi::ChildInfo info = getNextChildInfo();

        ABarButton* ptr = static_cast<ABarButton*>(static_cast<AWindow*>(window.get()));
        
        ptr->setPos(info.pos);
        ptr->setSize(vec2u{info.size.x, info.size.y});

        window->setParent(static_cast<AWindow*>(this));
        windows_.push_back(std::move(window));
    }
}

void ABar::removeWindow(wid_t id) 
{
    for (auto it = windows_.begin(); it != windows_.end(); it++)
    {
        if (it->get()->getId() == id)
        {
            windows_.erase(it);
            break;
        }
    }
}

psapi::ChildInfo ABar::getNextChildInfo() const
{
    int row_index = cur_button_index / n_row_buttons_;
    int col_index = cur_button_index % n_row_buttons_;

    psapi::vec2i button_pos = pos_ +  vec2i{col_index * button_size_.x, row_index * button_size_.y};

    cur_button_index++;

    return psapi::ChildInfo{button_pos, vec2i{button_size_.x, button_size_.y}};
}

void ABar::finishButtonDraw(IRenderWindow* renderWindow, const psapi::IBarButton* button) const
{
    float new_x = static_cast<float>(button->getPos().x);
    float new_y = static_cast<float>(button->getPos().y);

    float factor_x  = static_cast<float>(button_size_.x) / static_cast<float>(button->getSize().x);
    float factor_y  = static_cast<float>(button_size_.y) / static_cast<float>(button->getSize().y);

    switch (button->getState())
    {
    case psapi::IBarButton::State::Normal:
        
        break;

    case psapi::IBarButton::State::Hover:
        hover_button_->setPosition(new_x, new_y);
        hover_button_->setScale(factor_x, factor_y);
        hover_button_->draw(renderWindow);
        break;

    case psapi::IBarButton::State::Press:
        press_button_->setPosition(new_x, new_y);
        press_button_->setScale(factor_x, factor_y);
        press_button_->draw(renderWindow);
        break;

    case psapi::IBarButton::State::Released:
        release_button_->setPosition(new_x, new_y);
        release_button_->setScale(factor_x, factor_y);
        release_button_->draw(renderWindow);
        break;
    
    default:
        break;
    }
}

wid_t ABar::getId() const
{
    return id_;
}

psapi::IWindow* ABar::getWindowById(wid_t id)
{
    return (static_cast<AWindowVector*>(this))->getWindowById(id);
}

const psapi::IWindow* ABar::getWindowById(wid_t id) const
{
    return (static_cast<const AWindowVector*>(this))->getWindowById(id);
}

vec2i ABar::getPos() const
{
    return pos_;
}

vec2u ABar::getSize() const
{
    return size_;
}

void ABar::setParent(const IWindow* parent)
{
    parent_ = parent;
}

void ABar::forceActivate()
{
    is_active_ = true;
}

void ABar::forceDeactivate()
{
    is_active_ = false;
}

bool ABar::isActive() const
{
    return is_active_;
}

bool ABar::isWindowContainer() const
{
    return true;
}

/*=============================================================================*/