#include "render_window.hpp"

using namespace psapi;
using namespace sfm;

RenderWindow::RenderWindow(unsigned int width, unsigned int height, const std::string& window_title)
    : window_(sf::VideoMode(width, height), window_title), size_(width, height)
{
}

void RenderWindow::clear()
{
    window_.clear();
}

void RenderWindow::close()
{
    window_.close();
}

void RenderWindow::display()
{
    window_.display();
}

void RenderWindow::draw(Drawable* target)
{
    target->draw(this);
}

bool RenderWindow::isOpen()
{
    return window_.isOpen();
}

vec2u RenderWindow::getSize() const
{
    return size_;
}

std::unique_ptr<IRenderWindow> RenderWindow::create(unsigned int width, unsigned int height, const std::string& name)
{
   return std::make_unique<RenderWindow>(width, height, name);
}

bool RenderWindow::pollEvent(Event& event)
{
    sf::Event sfEvent;

    if (!window_.pollEvent(sfEvent))
    {
        return false;
    }

    switch (sfEvent.type)
    {
        case sf::Event::Closed:
            event.type = Event::Closed;
            break;

        case sf::Event::Resized:
            event.type = Event::Resized;
            event.size.width  = sfEvent.size.width;
            event.size.height = sfEvent.size.height;
            break;

        case sf::Event::LostFocus:
            event.type = Event::LostFocus;
            break;

        case sf::Event::GainedFocus:
            event.type = Event::GainedFocus;
            break;

        case sf::Event::TextEntered:
            event.type = Event::TextEntered;
            event.text.unicode = sfEvent.text.unicode;
            break;

        case sf::Event::KeyPressed:
            event.type = Event::KeyPressed;
            event.key.code = static_cast<Keyboard::Key>(sfEvent.key.code);
            event.key.alt     = sfEvent.key.alt;
            event.key.control = sfEvent.key.control;
            event.key.shift   = sfEvent.key.shift;
            event.key.system  = sfEvent.key.system;
            break;

        case sf::Event::KeyReleased:
            event.type = Event::KeyReleased;
            event.key.code = static_cast<Keyboard::Key>(sfEvent.key.code);
            event.key.alt     = sfEvent.key.alt;
            event.key.control = sfEvent.key.control;
            event.key.shift   = sfEvent.key.shift;
            event.key.system  = sfEvent.key.system;
            break;

        case sf::Event::MouseWheelScrolled:
            event.type = Event::MouseWheelScrolled;
            event.mouseWheel.delta = sfEvent.mouseWheelScroll.delta;
            event.mouseWheel.x     = sfEvent.mouseWheelScroll.x;
            event.mouseWheel.y     = sfEvent.mouseWheelScroll.y;
            break;

        case sf::Event::MouseButtonPressed:
            event.type = Event::MouseButtonPressed;
            event.mouseButton.button = static_cast<Mouse::Button>(sfEvent.mouseButton.button);
            event.mouseButton.x = sfEvent.mouseButton.x;
            event.mouseButton.y = sfEvent.mouseButton.y;
            break;

        case sf::Event::MouseButtonReleased:
            event.type = Event::MouseButtonReleased;
            event.mouseButton.button = static_cast<Mouse::Button>(sfEvent.mouseButton.button);
            event.mouseButton.x = sfEvent.mouseButton.x;
            event.mouseButton.y = sfEvent.mouseButton.y;
            break;

        case sf::Event::MouseMoved:
            event.type = Event::MouseMoved;
            event.mouseMove.x = sfEvent.mouseMove.x;
            event.mouseMove.y = sfEvent.mouseMove.y;
            break;

        case sf::Event::MouseEntered:
            event.type = Event::MouseEntered;
            break;

        case sf::Event::MouseLeft:
            event.type = Event::MouseLeft;
            break;

        case sf::Event::MouseWheelMoved: // deprecated
        case sf::Event::JoystickButtonPressed:
        case sf::Event::JoystickButtonReleased:
        case sf::Event::JoystickMoved:
        case sf::Event::JoystickConnected:
        case sf::Event::JoystickDisconnected:
        case sf::Event::TouchBegan:
        case sf::Event::TouchMoved:
        case sf::Event::TouchEnded:
        case sf::Event::SensorChanged:
        case sf::Event::Count:
        default:
            event.type = Event::Unknown;
            break;
    }

    return true;
}
