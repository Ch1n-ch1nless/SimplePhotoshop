#include "mouse.hpp"
#include "render_window.hpp"

bool Graphics::Mouse::IsMouseButtonPressed(MouseButton the_button)
{
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(the_button));
}

Graphics::WindowPoint Graphics::Mouse::GetPosition()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition();
    return WindowPoint(mouse_pos.x, mouse_pos.y);
}

Graphics::WindowPoint Graphics::Mouse::GetPosition(const RenderWindow &window)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window.window_);
    return WindowPoint(mouse_pos.x, mouse_pos.y);
}

void Graphics::Mouse::SetPosition(const WindowPoint &new_position)
{
    sf::Mouse::setPosition(sf::Vector2i(new_position.GetX(), new_position.GetY()));
}

void Graphics::Mouse::SetPosition(const WindowPoint &new_position, const RenderWindow& window)
{
    sf::Mouse::setPosition(sf::Vector2i(new_position.GetX(), new_position.GetY()), window.window_);
}
