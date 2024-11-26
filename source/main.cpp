#include "Graphics/Graphics.hpp"

#include <iostream>
#include <dlfcn.h>

int loadPlugins();

int main()
{
    psapi::sfm::RenderWindow render_window(1920, 1080, "MyPhotoshop v.0.1");

    while (render_window.isOpen())
    {
        psapi::sfm::Event event = {};

        while (render_window.pollEvent(event))
        {
            if (event.type == psapi::sfm::Event::EventType::Closed)
            {
                render_window.close();
                break;
            }
        }

        render_window.clear();
        render_window.display();
    }

    return 0;
}