#include "bar.hpp"

#include <cassert>

/*=======================< ABarButton implementation >========================*/

psapi::ABarButton::ABarButton(std::unique_ptr<sfm::Texture> init_texture, wid_t id)
:
    AWindow({0, 0}, {0, 0}, id),
    texture_    (std::move(init_texture)),
    sprite_     (std::make_unique<sfm::Sprite>())
{
    sprite_->setTexture(texture_.get());
}

psapi::wid_t psapi::ABarButton::getId() const
{
    return id_;
}

psapi::IWindow* psapi::ABarButton::getWindowById(psapi::wid_t id)
{
    return (id == id_) ? static_cast<AWindow*>(this) : nullptr;
}

const psapi::IWindow* psapi::ABarButton::getWindowById(psapi::wid_t id) const
{
    return (id == id_) ? static_cast<const AWindow*>(this) : nullptr;
}

psapi::vec2i psapi::ABarButton::getPos() const
{
    return pos_;
}

psapi::vec2u psapi::ABarButton::getSize() const
{
    return size_;
}

void psapi::ABarButton::setSize(const psapi::vec2u& size)
{
    size_ = size;
    sprite_->setTextureRect(sfm::IntRect{pos_, size_});
}

void psapi::ABarButton::setPos(const psapi::vec2i& pos)
{
    pos_ = pos;
    sprite_->setPosition(static_cast<float>(pos_.x),
                         static_cast<float>(pos_.y) );
}

void psapi::ABarButton::setParent(const psapi::IWindow* parent)
{
    parent_ = parent;
}

void psapi::ABarButton::forceActivate()
{
    is_active_ = true;
}

void psapi::ABarButton::forceDeactivate()
{
    is_active_ = false;
}

bool psapi::ABarButton::isActive() const
{
    return is_active_;
}

bool psapi::ABarButton::isWindowContainer() const
{
    return false;
}

void psapi::ABarButton::draw(psapi::IRenderWindow* renderWindow)
{
    if (is_active_)
    {
        renderWindow->draw(sprite_.get());
        const IBar* bar = dynamic_cast<const IBar*>(parent_);
        bar->finishButtonDraw(renderWindow, this);
    }
}

void psapi::ABarButton::setState(State state)
{
    state_ = state;
}

psapi::IBarButton::State psapi::ABarButton::getState() const
{
    return state_;
}

/*============================================================================*/

/*====================< ABarButtonAction implementation >=====================*/

psapi::ABarButtonAction::ABarButtonAction(ABarButton *button, const IRenderWindow *renderWindow, const Event &event)
:
    render_window_  (renderWindow),
    button_         (button),
    event_          (event)
{
}

bool psapi::ABarButtonAction::execute(const Key& key)
{
    vec2i mouse_pos = sfm::Mouse::getPosition(render_window_);
    vec2i button_pos = button_->getPos();

    vec2u size = button_->getSize();
    bool is_on_focus = button_pos.x <= mouse_pos.x && mouse_pos.x <= button_pos.x + size.x &&
                        button_pos.y <= mouse_pos.y && mouse_pos.y <= button_pos.y + size.y;
    if ( is_on_focus )
    {
        if ( event_.type == Event::MouseButtonPressed )
        {
            if ( button_->state_ != IBarButton::State::Press )
            {
                button_->state_ = IBarButton::State::Press;
            } 
            else
            {
                button_->state_ = IBarButton::State::Released;
                //static_cast<psapi::IOptionsBar *>(psapi::getRootWindow()->getWindowById(psapi::kOptionsBarWindowId))->removeAllOptions();
            }
        } 
        else if ( button_->state_ != IBarButton::State::Press )
        {
            button_->state_ = psapi::IBarButton::State::Hover;
        }
    } 
    else if ( button_->state_ == psapi::IBarButton::State::Hover || button_->state_ == psapi::IBarButton::State::Released )
    {
        button_->state_ = psapi::IBarButton::State::Normal;
    }

    return true;
}

bool psapi::ABarButtonAction::isUndoable(const Key &key)
{
    return false;
}

/*============================================================================*/

/*==========================< ABar implementation >===========================*/

psapi::ABar::ABar(  std::unique_ptr<psapi::sfm::Sprite> sprite,
                    std::unique_ptr<psapi::sfm::Sprite> hover_button_sprite,
                    std::unique_ptr<psapi::sfm::Sprite> pressed_button_sprite,
                    std::unique_ptr<psapi::sfm::Sprite> active_button_sprite,
                    psapi::vec2i toolbar_pos,
                    psapi::vec2u toolbar_size,
                    psapi::vec2u side_gap,
                    psapi::vec2u inbutton_gap,
                    psapi::vec2u button_size,
                    int n_buttons_in_row,
                    psapi::wid_t id                                             )
:
    AWindowContainer    (toolbar_pos, toolbar_size, id, nullptr, false),
    background_         (std::move(sprite)),
    hovered_            (std::move(hover_button_sprite)),
    pressed_            (std::move(pressed_button_sprite)),
    released_           (std::move(active_button_sprite)),
    side_gap_           (side_gap),
    inbutton_gap_       (inbutton_gap),
    button_size_        (button_size),
    n_buttons_in_row_   (n_buttons_in_row),
    n_buttons_          (0),
    cur_button_it       (0)
{

}

psapi::wid_t psapi::ABar::getId() const
{
    return id_;
}

psapi::IWindow* psapi::ABar::getWindowById(psapi::wid_t id)
{
    for (auto& window : children_)
    {
        IWindow* result = window->getWindowById(id);

        if (result != nullptr)
        {
            return result;
        }
    }

    return (id == id_) ? static_cast<AWindow*>(this) : nullptr;
}

const psapi::IWindow* psapi::ABar::getWindowById(psapi::wid_t id) const
{
    for (auto& window : children_)
    {
        const IWindow* result = window->getWindowById(id);

        if (result != nullptr)
        {
            return result;
        }
    }

    return (id == id_) ? static_cast<const AWindow*>(this) : nullptr;
}

psapi::vec2i psapi::ABar::getPos() const
{
    return pos_;
}

psapi::vec2u psapi::ABar::getSize() const
{
    return size_;
}

void psapi::ABar::setSize(const psapi::vec2u& size)
{
    vec2u cur_size = background_->getSize();

    float factor_x = static_cast<float>(size_.x) / static_cast<float>(cur_size.x);
    float factor_y = static_cast<float>(size_.y) / static_cast<float>(cur_size.y);

    background_->setScale(factor_x, factor_y);

    size_ = size;
}

void psapi::ABar::setPos(const psapi::vec2i& pos)
{
    background_->setPosition(static_cast<float>(pos.x),
                             static_cast<float>(pos.y) );

    pos_ = pos;
}

void psapi::ABar::setParent(const psapi::IWindow* parent)
{
    parent_ = parent;
}

void psapi::ABar::forceActivate()
{
    is_active_ = true;
}

void psapi::ABar::forceDeactivate()
{
    is_active_ = false;
}

bool psapi::ABar::isActive() const
{
    return is_active_;
}

bool psapi::ABar::isWindowContainer() const
{
    return true;
}

void psapi::ABar::addWindow(std::unique_ptr<IWindow> window)
{
    n_buttons_++;

    window->setPos(getNextChildPos());
    window->setSize(button_size_);
    window->setParent(static_cast<AWindow*>(this));

    children_.push_back(std::move(window));
}

void psapi::ABar::removeWindow(wid_t id)
{
    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        if (it->get()->getId() == id)
        {
            children_.erase(it);
            break;
        }
    }
}

void psapi::ABar::finishButtonDraw(IRenderWindow* renderWindow, const IBarButton* button) const
{
    vec2i cur_position = button->getPos();

    float pos_x = static_cast<float>(cur_position.x);
    float pos_y = static_cast<float>(cur_position.y);

    switch (button->getState())
    {
    case psapi::IBarButton::State::Normal:
        break;

    case psapi::IBarButton::State::Hover:
        hovered_->setPosition(pos_x, pos_y);
        renderWindow->draw(hovered_.get());
        break;

    case psapi::IBarButton::State::Press:
        pressed_->setPosition(pos_x, pos_y);
        renderWindow->draw(pressed_.get());
        break;

    case psapi::IBarButton::State::Released:
        released_->setPosition(pos_x, pos_y);
        renderWindow->draw(released_.get());
        break;
    
    default:
        assert(false);
        break;
    }
}

bool psapi::ABar::unPressAllButtons()
{
    for (auto& window : children_)
    {
        IBarButton* button = dynamic_cast<IBarButton*>(window.get());
        button->setState(IBarButton::State::Normal);
    }
}

void psapi::ABar::draw(psapi::IRenderWindow* renderWindow)
{
    renderWindow->draw(background_.get());
    drawChildren(renderWindow);
}

psapi::vec2i psapi::ABar::getNextChildPos()
{
    int row = cur_button_it / n_buttons_in_row_;
    int col = cur_button_it % n_buttons_in_row_;

    int x = side_gap_.x + col * (button_size_.x + inbutton_gap_.x) + pos_.x;
    int y = side_gap_.y + row * (button_size_.y + inbutton_gap_.y) + pos_.y;

    cur_button_it = (cur_button_it + 1) % n_buttons_;

    return vec2i{x, y};
}

std::unique_ptr<psapi::IAction> 
psapi::ABar::createAction(const IRenderWindow* renderWindow, const Event& event)
{
    return std::make_unique<ABarAction>(this, renderWindow, event);
}

/*============================================================================*/

/*=======================< ABarAction implementation >========================*/

psapi::ABarAction::ABarAction(ABar *bar, const IRenderWindow *renderWindow, const Event &event)
:
    render_window_  (renderWindow),
    bar_            (bar),
    event_          (event)
{
}

bool psapi::ABarAction::execute(const Key& key)
{
    for ( auto &window : bar_->children_ )
    {
        if ( !psapi::getActionController()->execute(window->createAction(render_window_, event_)) )
            return false;

        IBarButton* button = static_cast<IBarButton*>(window.get());

        if ( button->getState() == psapi::IBarButton::State::Press && button->getId() != bar_->last_pressed_id_ )
        {
            IWindow* prev_button = bar_->getWindowById( bar_->last_pressed_id_);
            if ( prev_button )
            {
                IBarButton *button_ptr =  static_cast<IBarButton *>( prev_button);
                if ( button_ptr->getState() == psapi::IBarButton::State::Press )
                {
                    button_ptr->setState( psapi::IBarButton::State::Normal);
                }
            }
            bar_->last_pressed_id_ = button->getId();
        }
    }
    return true;
}

bool psapi::ABarAction::isUndoable(const Key &key)
{
    return false;
}

/*============================================================================*/
