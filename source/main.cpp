#include "Graphics/Graphics.hpp"
#include "Photoshop/Photoshop.hpp"

#include <cassert>
#include <iostream>
#include <dlfcn.h>

typedef bool (*LoadPluginFunc)();
typedef void (*UnloadPluginFunc)();

using namespace psapi;
using namespace sfm;

void loadPlugin(const char* plugin_path);
void loadPlugins(const char* const *plugins);

int main()
{
    RenderWindow render_window(getScreenSize(), "MyPhotoshop v.2.1.2");

    IRootWindow* root_window = getRootWindow();
    root_window->addWindow(std::make_unique<Canvas>(getCanvasIntRect().pos, getCanvasIntRect().size));
    root_window->getWindowById(kCanvasWindowId)->setParent(root_window);

    root_window->addWindow(static_cast<std::unique_ptr<AWindow>>(std::make_unique<ToolBar>()));
    root_window->getWindowById(kToolBarWindowId)->setParent(root_window);

    std::unique_ptr<OptionsBar> options_bar = std::make_unique<OptionsBar>();
    options_bar->setParent(root_window);
    options_bar->addWindow(ColorPalette::create());

    root_window->addWindow(static_cast<std::unique_ptr<AWindow>>(std::move(options_bar)));

    loadPlugins(plugin_pathes);

    while (render_window.isOpen())
    {
        Event event = {};

        while (render_window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
            {
                render_window.close();
                break;
            }
        }

        render_window.clear();
        getActionController()->execute(root_window->createAction(&render_window, event));
        root_window->draw(&render_window);
        render_window.display();
    }
}

void loadPlugins(const char* const *plugins)
{
    for (size_t i = 0; i < sizeof(plugin_pathes) / sizeof(const char*); ++i)
    {
        loadPlugin(plugins[i]);
    }
}

void loadPlugin(const char* plugin_path)
{
    void* pluginLib = dlopen(plugin_path, RTLD_LAZY);
    if (!pluginLib) {
        std::cerr << "Failed to load plugin dylib in main: " << dlerror() << "\n";
        assert(false && "loadPluginfromLib");
    }

    LoadPluginFunc loadPlugin = reinterpret_cast<LoadPluginFunc>(dlsym(pluginLib, "onLoadPlugin"));
    UnloadPluginFunc unloadPlugin = reinterpret_cast<UnloadPluginFunc>(dlsym(pluginLib, "onUnloadPlugin"));

    if (!loadPlugin || !unloadPlugin) {
        std::cerr << "Failed to locate functions in plugin dylib in main: " << dlerror() << "\n";
        dlclose(pluginLib);
        assert(false && "loadPluginfromLib");
    }

    if (!loadPlugin()) {
        std::cerr << "Failed to initialize plugin in main.\n";
        dlclose(pluginLib);
        assert(false && "loadPluginfromLib");
    }

    std::cout << "Plugin: \"" << plugin_path << "\" loaded successfully!\n";
}