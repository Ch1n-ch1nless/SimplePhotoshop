#include "Graphics/Graphics.hpp"
#include "Photoshop/Photoshop.hpp"

#include <iostream>
#include <dlfcn.h>

int loadPlugins();

int main()
{
    psapi::sfm::RenderWindow render_window(1920, 1080, "MyPhotoshop v.2.0.1");

    psapi::IRootWindow* root_window = psapi::getRootWindow();
    root_window->addWindow(std::make_unique<psapi::Canvas>(psapi::vec2i{400, 200}, psapi::vec2u{1080, 720}));
    root_window->getWindowById(psapi::kCanvasWindowId)->setParent(root_window);

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
        psapi::getActionController()->execute(root_window->createAction(&render_window, event));
        root_window->draw(&render_window);
        render_window.display();
    }

    return 0;
}