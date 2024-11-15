#include "bump_filter.hpp"

/*=====================< BumpFilterAction implementation >====================*/

sys_plugin::BumpFilterAction::BumpFilterAction()
{
    canvas_ = static_cast<ps::Canvas*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kCanvasWindowId)));
}

bool sys_plugin::BumpFilterAction::operator()(const ps::IRenderWindow* render_window, const ps::Event &event)
{
    if (is_active_ && canvas_)
    {
        ps::vec2i  offset = canvas_->getTempLayerOffset();
        ps::Layer* layer  = static_cast<ps::Layer*>(canvas_->getTempLayer());

        ps::Layer temp_layer(canvas_->getSize());

        for (size_t i = 0; i < (canvas_->getSize().x - 1); ++i)
        {
            for (size_t j = 0; j < (canvas_->getSize().y - 1); ++j)
            {
                psapi::sfm::Color prev_color1 = layer->getPixel(ps::vec2i{i, j} + offset);
                psapi::sfm::Color prev_color2 = layer->getPixel(ps::vec2i{i+1, j+1} + offset);

                psapi::sfm::Color new_color = {};

                new_color.r = (prev_color1.r + (255 - prev_color2.r)) / 2;
                new_color.g = (prev_color1.g + (255 - prev_color2.g)) / 2;
                new_color.b = (prev_color1.b + (255 - prev_color2.b)) / 2;
                new_color.a = (prev_color1.r + prev_color2.a) / 2;

                temp_layer.setPixel(ps::vec2i{i, j}, new_color);
            }
        }

        for (size_t i = 0; i < (canvas_->getSize().x - 1); ++i)
        {
            for (size_t j = 0; j < (canvas_->getSize().y - 1); ++j)
            {
                layer->setPixel(offset + ps::vec2i{i, j}, temp_layer.getPixel(ps::vec2i{i, j}));
            }
        }

        is_active_ = false;
        return true;
    }

    return false;
}

void sys_plugin::BumpFilterAction::activate()
{
    is_active_ = true;
}

/*============================================================================*/

/*=====================< BumpFilterButton implementation >====================*/

sys_plugin::BumpFilterButton::BumpFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, std::unique_ptr<BumpFilterAction> action )
:
    ps::ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<sys_plugin::BumpFilterButton> sys_plugin::BumpFilterButton::create()
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(sys_plugin::BUMP_FILTER_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<sys_plugin::BumpFilterAction> action = std::make_unique<sys_plugin::BumpFilterAction>();

    return std::make_unique<sys_plugin::BumpFilterButton>(std::move(sprite), std::move(action));
}

bool sys_plugin::BumpFilterButton::update(const ps::IRenderWindow* render_window, const ps::Event& event)
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
        tool_bar->addWindow(std::move(static_cast<std::unique_ptr<ps::AWindow>>(std::move(sys_plugin::BumpFilterButton::create()))));

        return true;
    }

    void unloadPlugin()
    {
        return;
    }
}

/*============================================================================*/