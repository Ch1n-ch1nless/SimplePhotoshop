#include "pencil_action.hpp"

sys_plugin::PencilAction::PencilAction()
{
    canvas_ = static_cast<psapi::ICanvas*>(psapi::getRootWindow()->getWindowById(psapi::kCanvasWindowId));
}

psapi::vec2i sys_plugin::PencilAction::interpolatePoints(float t,
                                                         psapi::vec2i &point0, 
                                                         psapi::vec2i &point1,
                                                         psapi::vec2i &point2,
                                                         psapi::vec2i &point3   )
{
    psapi::vec2i medium0 = (point0 + point2) * 0.5;
    psapi::vec2i medium1 = (point1 + point3) * 0.5;

    float t2   = t*t,
          t3   = t2 * t,
          t3_2 = t3 * 2,
          t2_3 = t2 * 3;

    float hermite00 =  t3_2 - t2_3 + 1;
    float hermite10 =  t3   - t2*2 + t;
    float hermite01 = -t3_2 + t2_3;
    float hermite11 =  t3   - t2;

    return hermite00 * point1 + hermite10 * medium0 +
           hermite01 * point2 + hermite11 * medium1;
}

size_t calcStepNumber(psapi::vec2i &point1, psapi::vec2i &point2)
{
    double dist = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));

    return static_cast<size_t>(15 + std::max(dist, 50.0));
}

bool sys_plugin::PencilAction::operator()(const psapi::IRenderWindow* renderWindow, const psapi::Event& event)
{
    if (!canvas_ || !(canvas_->isPressed()))
    {
        mouse_points_.clear();
        return false;
    }

    mouse_points_.push_back(psapi::sfm::Mouse::getPosition(renderWindow));

    if (mouse_points_.size() < 4) return true;

    size_t step_number = calcStepNumber(mouse_points_[1], mouse_points_[2]);
    psapi::vec2i temp_point = {};

    for (size_t i = 0; i < step_number; i++)
    {
        temp_point = interpolatePoints((i + .0) / step_number, mouse_points_[0], mouse_points_[1], mouse_points_[2], mouse_points_[3]);
        canvas_->getTempLayer()->setPixel(temp_point, {0, 0, 0, 255});
    }

    mouse_points_.pop_front();
}