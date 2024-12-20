#include "../../api/api_sfm.hpp"
#include "render_window.hpp"

using namespace psapi;
using namespace sfm;

vec2i Mouse::getPosition() {
    sf::Vector2i pos = sf::Mouse::getPosition();
    return { pos.x, pos.y };
}

vec2i Mouse::getPosition(const IRenderWindow* window) {
    const RenderWindow* sfmWindow = static_cast<const RenderWindow*>(window);
    sf::Vector2i pos = sf::Mouse::getPosition(sfmWindow->window_);
    return { pos.x, pos.y };
}

bool Mouse::isButtonPressed(Mouse::Button button) {
    switch (button)
    {
        case Mouse::Button::Left:
            return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        case Mouse::Button::Right:
            return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    
        case Mouse::Button::Middle:
            return sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);

        default:
            break;
    }

    return false;
}

