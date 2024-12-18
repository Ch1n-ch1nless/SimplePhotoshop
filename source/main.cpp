#include "Graphics/Graphics.hpp"
#include "Photoshop/Photoshop.hpp"

#include <iostream>
#include <dlfcn.h>

int loadPlugins();

int main()
{
    psapi::sfm::RenderWindow render_window(psapi::getScreenSize(), "MyPhotoshop v.2.0.1");

    psapi::IRootWindow* root_window = psapi::getRootWindow();
    root_window->addWindow(std::make_unique<psapi::Canvas>(psapi::getCanvasIntRect().pos, psapi::getCanvasIntRect().size));
    root_window->getWindowById(psapi::kCanvasWindowId)->setParent(root_window);

    root_window->addWindow(static_cast<std::unique_ptr<psapi::AWindow>>(std::make_unique<psapi::ToolBar>()));
    root_window->getWindowById(psapi::kToolBarWindowId)->setParent(root_window);

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