#include "keyboard.hpp"

bool Graphics::KeyBoard::IsKeyPressed(Graphics::KeyBoard::Key the_key)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(the_key));
}

bool Graphics::KeyBoard::IsKeyPressed(Graphics::KeyBoard::ScanCode the_scan_code)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(the_scan_code));
}