#include "View/View.hpp"

#include <iostream>
#include <dlfcn.h>

const char* const PluginPathArray[] = 
{
    "./Plugins/libtool_bar.so",
    "./Plugins/libpencil_button.so",
    "./Plugins/libcat_button.so",
    "./Plugins/libbrush_button.so",
    "./Plugins/liberaser_button.so",
    "./Plugins/libnegative_filter.so",
    "./Plugins/libbump_filter.so",
    "./Plugins/libblur_filter.so"
};

int loadPlugins();

int main()
{
    psapi::sfm::RenderWindow render_window(1920, 1080, "MyPhotoshop v.0.1");

    psapi::IWindowContainer* root_window = psapi::getRootWindow();

    root_window->addWindow(static_cast<std::unique_ptr<ps::AWindow>>(std::make_unique<ps::Canvas>(1920, 1080)));

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

    return 0;
}