#include "Graphics/Graphics.hpp"

using namespace psapi;
using namespace sfm;

int main()
{
    RenderWindow main_window(800, 600, "LOL");

    while (main_window.isOpen())
    {
        Event event;

        while (main_window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
            {
                main_window.close();
            }
        }

        main_window.clear();
        main_window.display();
    }
    

    return 0;
}