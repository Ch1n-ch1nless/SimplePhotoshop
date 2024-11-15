#include "negative_filter.hpp"

/*======================< FilterAction implementation >=======================*/

sys_plugin::NegativeFilterAction::NegativeFilterAction()
{
    canvas_ = static_cast<ps::Canvas*>(static_cast<ps::AWindow*>(psapi::getRootWindow()->getWindowById(psapi::kCanvasWindowId)));
}

bool sys_plugin::NegativeFilterAction::operator()(const ps::IRenderWindow* render_window, const ps::Event &event)
{
    if (is_active_ && canvas_)
    {
        ps::vec2i offset = canvas_->getTempLayerOffset();

        ps::Layer* active_layer = static_cast<ps::Layer*>(canvas_->getTempLayer()); //TODO: In future fix to get real active layer!

        for (std::size_t i = 0; i < canvas_->getSize().x; i++)
        {
            for (std::size_t j = 0; j < canvas_->getSize().y; j++)
            {
                psapi::sfm::Color prev_color = active_layer->getPixel(ps::vec2i{i, j} + offset);
                psapi::sfm::Color new_color  = psapi::sfm::Color{255 - prev_color.r, 255 - prev_color.g, 255 - prev_color.b, prev_color.a};
                active_layer->setPixel(ps::vec2i{i, j} + offset, new_color);
            }
        }

        is_active_ = false;
        return true;
    }

    return false;
}

void sys_plugin::NegativeFilterAction::activate()
{
    is_active_ = true;
}

/*============================================================================*/

/*======================< FilterButton implementation >=======================*/

sys_plugin::NegativeFilterButton::NegativeFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, std::unique_ptr<NegativeFilterAction> action )
:
    ps::ABarButton(std::move(sprite), std::move(action), psapi::getRootWindow()->getWindowById(psapi::kToolBarWindowId))
{
}

std::unique_ptr<sys_plugin::NegativeFilterButton> sys_plugin::NegativeFilterButton::create()
{
    static std::unique_ptr<psapi::sfm::Texture> texture = std::make_unique<psapi::sfm::Texture>();

    texture->loadFromFile(sys_plugin::NEGATIVE_FILTER_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> sprite = std::make_unique<psapi::sfm::Sprite>();

    sprite->setTexture(texture.get());

    std::unique_ptr<sys_plugin::NegativeFilterAction> action = std::make_unique<sys_plugin::NegativeFilterAction>();

    return std::make_unique<sys_plugin::NegativeFilterButton>(std::move(sprite), std::move(action));
}

bool sys_plugin::NegativeFilterButton::update(const ps::IRenderWindow* render_window, const ps::Event& event)
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
        tool_bar->addWindow(std::move(static_cast<std::unique_ptr<ps::AWindow>>(std::move(sys_plugin::NegativeFilterButton::create()))));

        return true;
    }

    void unloadPlugin()
    {
        return;
    }
}

/*============================================================================*/