#include "gauss_blur_filter.hpp"

#include <cmath>
#include <iostream>

/*==================< GaussBlurFilterAction implementation >==================*/

sys_plugin::GaussBlurFilterAction::GaussBlurFilterAction(double sigma, int radius)
:
gauss_matrix_(),
sigma_  (sigma),
radius_ (radius)
{
    canvas_ = static_cast<ps::Canvas*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kCanvasWindowId)));
    fillGaussMatrix();
}

void sys_plugin::GaussBlurFilterAction::fillGaussMatrix()
{
    size_t size = 2 * radius_ + 1;

    gauss_matrix_.assign(size, std::vector<double>(size, 0.0));
    double sum = 0.0;

    for (int y = -radius_; y <= radius_; y++)
    {
        for (int x = -radius_; x <= radius_; x++)
        {
            double pow = -static_cast<double>(x * x + y * y) / (2.0 * sigma_ * sigma_);
            gauss_matrix_[y+radius_][x+radius_] = exp(pow) / (2.0 * M_PI * sigma_ * sigma_);
            sum += gauss_matrix_[y+radius_][x+radius_];
        }
    }

    for (int y = -radius_; y <= radius_; y++)
    {
        for (int x = -radius_; x <= radius_; x++)
        {
            gauss_matrix_[y+radius_][x+radius_] /= sum;

        }
    }
}

bool sys_plugin::GaussBlurFilterAction::operator()(const ps::IRenderWindow* render_window, const ps::Event &event)
{
    if (is_active_ && canvas_)
    {
        canvas_->insertEmptyLayer(1);
        ps::Layer* new_layer = static_cast<ps::Layer*>(canvas_->getLayer(1));

        ps::vec2i offset = canvas_->getTempLayerOffset();
        ps::Layer* layer = static_cast<ps::Layer*>(canvas_->getTempLayer());

        size_t height = canvas_->getSize().y;
        size_t width  = canvas_->getSize().x;

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                double new_red   = 0.f;
                double new_green = 0.f;
                double new_blue  = 0.f;
                double new_alpha = 0.f;

                for (int dy = -radius_; dy <= radius_; dy++)
                {
                    for (int dx = -radius_; dx <= radius_; dx++)
                    {
                        int xIndex = std::min(std::max(dx + x, 0), (int)(width - 1));
                        int yIndex = std::min(std::max(dy + y, 0), (int)(height - 1));

                        psapi::sfm::Color new_color = layer->getPixel(offset + ps::vec2i{xIndex, yIndex});

                        new_red   += gauss_matrix_[dy+radius_][dx+radius_] * (double)new_color.r;
                        new_green += gauss_matrix_[dy+radius_][dx+radius_] * (double)new_color.g;
                        new_blue  += gauss_matrix_[dy+radius_][dx+radius_] * (double)new_color.b;
                        new_alpha += gauss_matrix_[dy+radius_][dx+radius_] * (double)new_color.a;
                    }
                }

                psapi::sfm::Color blur_color = {(uint8_t)new_red, (uint8_t)new_green, (uint8_t)new_blue, (uint8_t)new_alpha};

                new_layer->setPixel(ps::vec2i{x, y}, blur_color);
            }
        }

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                layer->setPixel(offset + ps::vec2i{x, y}, new_layer->getPixel(ps::vec2i{x, y}));
            }
        }

        canvas_->removeLayer(1);

        is_active_ = false;
        return true;
    }

    return false;
}

void sys_plugin::GaussBlurFilterAction::activate()
{
    is_active_ = true;
}

/*============================================================================*/

/*==================< GaussBlurFilterButton implementation >==================*/

sys_plugin::GaussBlurFilterButton::GaussBlurFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, std::unique_ptr<GaussBlurFilterAction> action )
:
    ps::ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<sys_plugin::GaussBlurFilterButton> sys_plugin::GaussBlurFilterButton::create()
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(sys_plugin::GAUSS_BLUR_FILTER_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<sys_plugin::GaussBlurFilterAction> action = std::make_unique<sys_plugin::GaussBlurFilterAction>(1.0, 3);

    return std::make_unique<sys_plugin::GaussBlurFilterButton>(std::move(sprite), std::move(action));
}

bool sys_plugin::GaussBlurFilterButton::update(const ps::IRenderWindow* render_window, const ps::Event& event)
{
    if (!is_active_) return false;

    ps::vec2i mouse_pos = psapi::sfm::Mouse::getPosition(render_window);

    mouse_pos -= pos_;

    bool is_in_window = (0 <= mouse_pos.x && mouse_pos.x <= size_.x &&
                         0 <= mouse_pos.y && mouse_pos.y <= size_.y    );

    if (is_in_window)
    {
        switch (event.type)
        {
        case psapi::sfm::Event::EventType::MouseButtonPressed:
            state_ = psapi::IBarButton::State::Press;
            action_->activate();
            action_->operator()(render_window, event);
            break;

        case psapi::sfm::Event::EventType::MouseButtonReleased:
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

extern "C"
{
    bool   loadPlugin()
    {
        ps::ABar* tool_bar = static_cast<ps::ABar*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId)));
        tool_bar->addWindow(std::move(static_cast<std::unique_ptr<ps::AWindow>>(std::move(sys_plugin::GaussBlurFilterButton::create()))));

        return true;
    }

    void unloadPlugin()
    {
        return;
    }
}

/*============================================================================*/