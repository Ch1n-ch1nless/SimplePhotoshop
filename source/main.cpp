#include "Graphics/Graphics.hpp"

#include <iostream>

using namespace psapi;
using namespace sfm;

int main()
{
    RenderWindow main_window(800, 600, "LOL");

    Texture texture;
    texture.loadFromFile("Pictures/start_button.png");

    Sprite sprite;
    sprite.setTexture(&texture);

    while (main_window.isOpen())
    {
        Event event;

        while (main_window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
            {
                main_window.close();
            }
            else if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::Key::Escape)
            {
                main_window.close();
            }
            else if (event.type == Event::EventType::MouseButtonPressed && event.mouseButton.button == Mouse::Button::Left)
            {
                sprite.setPosition(vec2f{event.mouseButton.x, event.mouseButton.y});
            }
        }

        main_window.clear();
        main_window.draw(&sprite);
        main_window.display();
    }
    

    return 0;
}