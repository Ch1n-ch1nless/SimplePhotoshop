#include "blur_filter.hpp"

/*=====================< BlurFilterAction implementation >====================*/

sys_plugin::BlurFilterAction::BlurFilterAction()
{
    canvas_ = static_cast<ps::Canvas*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kCanvasWindowId)));
}

void sys_plugin::BlurFilterAction::activate()
{
    is_active_ = true;
}

bool sys_plugin::BlurFilterAction::operator()(const ps::IRenderWindow* render_window, const ps::Event &event)
{
    if (is_active_ && canvas_)
    {
        float blur_matrix[3][3] = {
                                    {0.025f, 0.100f, 0.025f},
                                    {0.100f, 0.500f, 0.100f},
                                    {0.025f, 0.100f, 0.025f}
                                  };

        ps::Layer new_layer(canvas_->getSize());

        ps::vec2i offset = canvas_->getTempLayerOffset();
        ps::Layer* layer = static_cast<ps::Layer*>(canvas_->getTempLayer());

        for (int y = 1; y < (canvas_->getSize().y - 1); ++y)
        {
            for (int x = 1; x < (canvas_->getSize().x - 1); ++x)
            {
                float new_red   = 0.f;
                float new_green = 0.f;
                float new_blue  = 0.f;
                float new_alpha = 0.f;

                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        psapi::sfm::Color new_color = layer->getPixel(offset + ps::vec2i{x, y} +ps::vec2i{j-1,i-1});
                        new_red   += blur_matrix[i][j] * new_color.r;
                        new_green += blur_matrix[i][j] * new_color.g;
                        new_blue  += blur_matrix[i][j] * new_color.b;
                        new_alpha += blur_matrix[i][j] * new_color.a;
                    }
                }

                psapi::sfm::Color blur_color = {(uint8_t)new_red, (uint8_t)new_green, (uint8_t)new_blue, (uint8_t)new_alpha};

                new_layer.setPixel(ps::vec2i{x, y}, blur_color);
            }
        }

        for (int y = 1; y < (canvas_->getSize().y - 1); ++y)
        {
            for (int x = 1; x < (canvas_->getSize().x - 1); ++x)
            {
                layer->setPixel(offset + ps::vec2i{x, y}, new_layer.getPixel(ps::vec2i{x, y}));
            }
        }

        is_active_ = false;
        return true;
    }

    return false;
}

/*============================================================================*/

/*=====================< BlurFilterButton implementation >====================*/

sys_plugin::BlurFilterButton::BlurFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, std::unique_ptr<BlurFilterAction> action )
:
    ps::ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<sys_plugin::BlurFilterButton> sys_plugin::BlurFilterButton::create()
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(sys_plugin::BLUR_FILTER_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<sys_plugin::BlurFilterAction> action = std::make_unique<sys_plugin::BlurFilterAction>();

    return std::make_unique<sys_plugin::BlurFilterButton>(std::move(sprite), std::move(action));
}

bool sys_plugin::BlurFilterButton::update(const ps::IRenderWindow* render_window, const ps::Event& event)
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
        tool_bar->addWindow(std::move(static_cast<std::unique_ptr<ps::AWindow>>(std::move(sys_plugin::BlurFilterButton::create()))));

        return true;
    }

    void unloadPlugin()
    {
        return;
    }
}

/*============================================================================*/