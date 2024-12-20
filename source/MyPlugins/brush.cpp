#include "brush.hpp"

#include <iostream>

using namespace psapi;

PaintAction::PaintAction()
:
    mouse_points_()
{
    canvas_     = dynamic_cast<psapi::Canvas*>(psapi::getRootWindow()->getWindowById(psapi::kCanvasWindowId));
    is_active_  = false;
}

bool PaintAction::operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event)
{
    if (is_active_ && canvas_ && canvas_->isPressedLeftMouseButton())
    {
        psapi::vec2i cur_pos = canvas_->getMousePosition();

        if (mouse_points_.empty())
        {
            mouse_points_.push_back(cur_pos);
            return true;
        }

        psapi::vec2i last_mouse_pos_ = mouse_points_.back();

        if (((cur_pos.x - last_mouse_pos_.x) * (cur_pos.x - last_mouse_pos_.x) + 
             (cur_pos.y - last_mouse_pos_.y) * (cur_pos.y - last_mouse_pos_.y)) < 5)
        {
            return true;
        }

        mouse_points_.push_back(cur_pos);

        paintNewCircle();

        return true;
    }

    mouse_points_.clear();

    return false;
}

void PaintAction::activate()
{
    is_active_ = true;
}

psapi::vec2i PaintAction::interpolateHermite(   float         t,
                                                psapi::vec2i &point0,
                                                psapi::vec2i &point1,
                                                psapi::vec2i &point2,
                                                psapi::vec2i &point3 )
{
    psapi::vec2f medium0 = {(point2.x - point0.x) / 2.f, (point2.y - point0.y) / 2.f};
    psapi::vec2f medium1 = {(point3.x - point1.x) / 2.f, (point3.y - point1.y) / 2.f};

    float t2   = t*t,
          t3   = t2 * t,
          t3_2 = t3 * 2,
          t2_3 = t2 * 3;

    float hermite00 =  t3_2 - t2_3 + 1;
    float hermite10 =  t3   - t2*2 + t;
    float hermite01 = -t3_2 + t2_3;
    float hermite11 =  t3   - t2;

    float x = hermite00 * point1.x + hermite10 * medium0.x +
              hermite01 * point2.x + hermite11 * medium1.x;

    float y = hermite00 * point1.y + hermite10 * medium0.y +
              hermite01 * point2.y + hermite11 * medium1.y;

    return psapi::vec2i{(int)round(x), (int)round(y)};
}

size_t PaintAction::calculateStepsNumber(psapi::vec2i &point1, psapi::vec2i &point2)
{
    float dist = (point2.x - point1.x) * (point2.x - point1.x) +
                 (point2.y - point1.y) * (point2.y - point1.y)  ;
    
    return static_cast<size_t>(std::max(sqrt(dist), 50.0));
}

void PaintAction::paintNewCircle()
{
    if (mouse_points_.size() < 4) 
    {
        return;
    }

    psapi::vec2i &point0 = mouse_points_[0];
    psapi::vec2i &point1 = mouse_points_[1];
    psapi::vec2i &point2 = mouse_points_[2];
    psapi::vec2i &point3 = mouse_points_[3];

    size_t steps_number = calculateStepsNumber(point1, point2);

    for (size_t i = 0; i <= steps_number; ++i)
    {
        float t = static_cast<float>(i) / static_cast<float>(steps_number);

        psapi::vec2i point = interpolateHermite(t, point0, point1, point2, point3);

        for (int offsetY = -4; offsetY <= 4; offsetY++)
        {
            for (int offsetX = -4; offsetX <= 4; offsetX++)
            {
                if ((offsetX * offsetX + offsetY * offsetY) <= 4 * 4)
                {   
                    canvas_->getTempLayer()->setPixel(point + psapi::vec2i{offsetX, offsetY}, psapi::sfm::Color{255, 0, 0, 255});
                }
            }
        }
    }

    mouse_points_.pop_front();
}

BrushButton::BrushButton()
:
    ABarButton(std::make_unique<sfm::Texture>(), 1)
{
    texture_->loadFromFile("assets/brush_button.png");
    sprite_->setTexture(texture_.get());
    sprite_->setTextureRect(sfm::IntRect{vec2i{0, 0}, vec2u{96, 96}});

    is_active_ = true;
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

bool psapi::BrushButton::update(const IRenderWindow* render_window, const Event& event)
{
    if (!is_active_) 
    {
        return false;
    }

    vec2i mouse_pos = psapi::sfm::Mouse::getPosition(render_window);

    mouse_pos -= pos_;

    bool is_in_window = (0 <= mouse_pos.x && mouse_pos.x <= size_.x &&
                         0 <= mouse_pos.y && mouse_pos.y <= size_.y    );

    if (state_ == psapi::IBarButton::State::Released)
    {
        action_.operator()(render_window, event);
        return true;
    }

    if (is_in_window)
    {
        switch (event.type)
        {
        case psapi::sfm::Event::EventType::MouseButtonPressed:
            state_ = psapi::IBarButton::State::Press;
            action_.activate();
            break;

        case psapi::sfm::Event::EventType::MouseButtonReleased:
            std::cout << "I am released!\n";
            state_ = psapi::IBarButton::State::Released;
            break;

        case psapi::sfm::Event::EventType::MouseMoved:
            state_ = psapi::IBarButton::State::Hover;
            break;
        
        default:
            break;
        }

        if (state_ == psapi::IBarButton::State::Normal)
        {
            state_ = psapi::IBarButton::State::Hover;
        }

        return true;
    }

    switch (state_)
    {
    case psapi::IBarButton::State::Released:
        break;
    
    default:
        state_ = psapi::IBarButton::State::Normal;
        break;
    }

    return false;
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
    return button_->update(render_window_, event_);
}

bool BrushAction::isUndoable(const Key& key)
{
    return false;
}