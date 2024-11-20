#include "unsharp_mask_filter.hpp"

/*=================< UnsharpMaskFilterAction implementation >=================*/

sys_plugin::UnsharpMaskFilterAction::UnsharpMaskFilterAction(double sigma, int radius)
:
    sigma_  (sigma),
    radius_ (radius)
{
    canvas_ = static_cast<ps::Canvas*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kCanvasWindowId)));
    fillKernel();
}

void sys_plugin::UnsharpMaskFilterAction::fillKernel()
{
    int size = 2 * radius_ + 1;

    std::vector<std::vector<double>> source(size, std::vector<double>(size, 0.0));
    source[radius_][radius_] = 1.0;

    kernel_.assign(size, std::vector<double>(size, 0.0));
    double sum = 0.0;

    for (int y = -radius_; y <= radius_; y++)
    {
        for (int x = -radius_; x <= radius_; x++)
        {
            double pow = -static_cast<double>(x * x + y * y) / (2.0 * sigma_ * sigma_);
            kernel_[y+radius_][x+radius_] = exp(pow) / (2.0 * M_PI * sigma_ * sigma_);
            sum += kernel_[y+radius_][x+radius_];
        }
    }

    for (int y = -radius_; y <= radius_; y++)
    {
        for (int x = -radius_; x <= radius_; x++)
        {
            kernel_[y+radius_][x+radius_] /= sum;

        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            kernel_[i][j] = source[i][j] + 2.0 * (source[i][j] - kernel_[i][j]);
        }
    }
}

bool sys_plugin::UnsharpMaskFilterAction::operator()(const ps::IRenderWindow* render_window, const ps::Event &event)
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

                        double coefficient = kernel_[dy+radius_][dx+radius_];

                        new_red   += coefficient * (double)new_color.r;
                        new_green += coefficient * (double)new_color.g;
                        new_blue  += coefficient * (double)new_color.b;
                        new_alpha += coefficient * (double)new_color.a;
                    }
                }

                uint8_t sharpen_red     = static_cast<uint8_t>(std::min(std::max((int)new_red, 0), 255));
                uint8_t sharpen_green   = static_cast<uint8_t>(std::min(std::max((int)new_green, 0), 255));
                uint8_t sharpen_blue    = static_cast<uint8_t>(std::min(std::max((int)new_blue, 0), 255));
                uint8_t sharpen_alpha   = static_cast<uint8_t>(std::min(std::max((int)new_alpha, 0), 255));

                psapi::sfm::Color sharpen_color = {sharpen_red, sharpen_green, sharpen_blue, sharpen_alpha};

                new_layer->setPixel(ps::vec2i{x, y}, sharpen_color);
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

void sys_plugin::UnsharpMaskFilterAction::activate()
{
    is_active_ = true;
}

/*============================================================================*/

/*=================< UnsharpMaskFilterButton implementation >=================*/

sys_plugin::UnsharpMaskFilterButton::UnsharpMaskFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, std::unique_ptr<UnsharpMaskFilterAction> action )
:
    ps::ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<sys_plugin::UnsharpMaskFilterButton> sys_plugin::UnsharpMaskFilterButton::create()
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(sys_plugin::UNSHARP_MASK_FILTER_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<sys_plugin::UnsharpMaskFilterAction> action = std::make_unique<sys_plugin::UnsharpMaskFilterAction>(1.0, 2);

    return std::make_unique<sys_plugin::UnsharpMaskFilterButton>(std::move(sprite), std::move(action));
}

bool sys_plugin::UnsharpMaskFilterButton::update(const ps::IRenderWindow* render_window, const ps::Event& event)
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


/*============================================================================*/

extern "C"
{
    bool   loadPlugin()
    {
        ps::ABar* tool_bar = static_cast<ps::ABar*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId)));
        tool_bar->addWindow(std::move(static_cast<std::unique_ptr<ps::AWindow>>(std::move(sys_plugin::UnsharpMaskFilterButton::create()))));

        return true;
    }

    void unloadPlugin()
    {
        return;
    }
}