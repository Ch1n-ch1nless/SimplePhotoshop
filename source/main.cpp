#include "View/View.hpp"
#include "SystemPlugins/tool_bar.hpp"

#include <iostream>
#include <dlfcn.h>

const char* const PluginPathArray[] = 
{
    "./Plugins/libpencil_button.so"
};

int loadPlugins()
{
    for (const auto &path : PluginPathArray)
    {
        auto plugin = dlopen(path, RTLD_LAZY);

        if (!plugin)
        {
            std::cerr << dlerror() << '\n';
            return -1;
        }

        auto func = (bool (*)(void))dlsym(plugin, "loadPlugin");

        if (!func)
        {
            std::cerr << "ERROR!!! Program can not find function!\n";
            return -1;
        }

        func();
    }
}

int main()
{
    psapi::sfm::RenderWindow render_window(1920, 1080, "TEST!!!");

    psapi::IWindowContainer* root_window = psapi::getRootWindow();

    std::cerr << "In main: " << root_window << '\n';

    /*root_window->addWindow(static_cast<std::unique_ptr<ps::AWindow>>(sys_plugin::ToolBar::create(1920, 1080)));

    root_window->addWindow(static_cast<std::unique_ptr<ps::AWindow>>(std::make_unique<ps::Canvas>(1920, 1080)));

    sys_plugin::ToolBar* tool_bar = static_cast<sys_plugin::ToolBar*>(static_cast<ps::AWindow*>(root_window->getWindowById(psapi::kToolBarWindowId)));

    ps::Canvas* canvas = static_cast<ps::Canvas*>(static_cast<ps::AWindow*>(root_window->getWindowById(psapi::kCanvasWindowId)));*/

    //tool_bar->addWindow(static_cast<std::unique_ptr<ps::AWindow>>(sys_plugin::CatButton::create()));

    loadPlugins();

    while (render_window.isOpen())
    {
        psapi::Event event = {};

        while (render_window.pollEvent(event))
        {
            if (event.type == psapi::Event::EventType::Closed)
            {
                render_window.close();
                break;
            }

            root_window->update(&render_window, event);
        }

        render_window.clear();
        root_window->draw(&render_window);
        render_window.display();
    }

    return 0;
}