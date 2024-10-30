#include "Graphics/Graphics.hpp"
#include "View/View.hpp"
#include "SystemPlugins/tool_bar.hpp"

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

    canvas->setPos({200, 150});

    root_window->addWindow(std::make_unique<sys_plugin::ToolBar>(vec2i{650, 0}, vec2u{150, 600}, vec2u{35, 35}, 4, "Pictures/tool_bar.png"));

    sys_plugin::ToolBar* tool_bar = static_cast<sys_plugin::ToolBar*>(root_window->getWindowById(kToolBarWindowId));

    tool_bar->setParent(root_window);

    while (render_window.isOpen())
    {
        Event event;

        while (render_window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
            {
                render_window.close();
            }

            root_window->update(&render_window, event);
        }

        render_window.display();
        render_window.clear();

        if (canvas->isPressed())
        {
            ILayer* temp_layer = canvas->getTempLayer();
            temp_layer->setPixel(canvas->getMousePosition(), {0, 0, 0, 255});
        }

        root_window->draw(&render_window);
    }

    return 0;
}