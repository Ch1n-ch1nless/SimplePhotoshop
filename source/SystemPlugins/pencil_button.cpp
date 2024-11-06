#include "pencil_button.hpp"

#include <iostream>

using namespace sys_plugin;

PencilAction::PencilAction(psapi::ICanvas* canvas)
:
    canvas_(canvas)
{
}

void PencilAction::activate()
{
    is_active_ = true;
}

psapi::vec2i PencilAction::interpolateHermite(  float            t,
                                                psapi::vec2i    &point0,
                                                psapi::vec2i    &point1,
                                                psapi::vec2i    &point2,
                                                psapi::vec2i    &point3 )
{
    psapi::vec2f medium0 = {(point0.x + point2.x) / 2.f, (point0.y + point2.y) / 2.f};
    psapi::vec2f medium1 = {(point1.x + point3.x) / 2.f, (point1.y + point3.y) / 2.f};

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

    return psapi::vec2i{(int)std::round(x), (int)std::round(y)};
}

size_t PencilAction::calculateStepsNumber(psapi::vec2i &point1, psapi::vec2i &point2)
{
    float dist = (point2.x - point1.x) * (point2.x - point1.x) +
                 (point2.y - point1.y) * (point2.y - point1.y)  ;
    
    return 16 + static_cast<size_t>(std::max(sqrt(dist), 32.0));
}

void PencilAction::paintNewPoint()
{
    if (mouse_points_.size() < 4) return;

    psapi::vec2i &point0 = mouse_points_[0];
    psapi::vec2i &point1 = mouse_points_[1];
    psapi::vec2i &point2 = mouse_points_[2];
    psapi::vec2i &point3 = mouse_points_[3];

    size_t steps_number = calculateStepsNumber(point1, point2);

    for (float t = 0; t <= 1; t += 0.01f)
    {
        psapi::vec2i point = interpolateHermite(t, point0, point1, point2, point3);

        canvas_->getTempLayer()->setPixel(point, psapi::sfm::Color{0, 0, 0, 255});  //TODO: Fix the magic constant!
    }

    mouse_points_.pop_front();
}

bool PencilAction::operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event)
{
    if (is_active_ && canvas_->isPressed())
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

        paintNewPoint();

        return true;
    }

    mouse_points_.clear();

    return false;
}

PencilButton::PencilButton(std::unique_ptr<psapi::sfm::Sprite> sprite, std::unique_ptr<PencilAction> action )
:
    ps::ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<PencilButton> PencilButton::create(psapi::ICanvas* canvas)
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(PENCIL_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<PencilAction> action = std::make_unique<PencilAction>(canvas);

    return std::make_unique<PencilButton>(std::move(sprite), std::move(action));
}