#include "Graphics/Graphics.hpp"
#include "View/View.hpp"

#include <iostream>

using namespace psapi;
using namespace sfm;

int main()
{   
    RenderWindow render_window(800, 600, "RootWindow");

    IWindowContainer* root_window = getRootWindow();

    root_window->addWindow(std::make_unique<Canvas>(vec2u{400, 300}));

    Canvas* canvas = static_cast<Canvas*>(root_window->getWindowById(kCanvasWindowId));

    canvas->setParent(root_window);

    while (render_window.isOpen())
    {
        Event event;

        while (render_window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
            {
                render_window.close();
            }
        }

        render_window.display();
        render_window.clear();

        ILayer* temp_layer = canvas->getTempLayer();
        temp_layer->setPixel(canvas->getMousePosition(), {255, 255, 255, 255});

        root_window->draw(&render_window);

        root_window->update(&render_window, event);
    }

    return 0;
}