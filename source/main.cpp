#include "Graphics/Graphics.hpp"

#include <cassert>
#include <iostream>
#include <dlfcn.h>

typedef bool (*LoadPluginFunc)();
typedef void (*UnloadPluginFunc)();

using namespace psapi;
using namespace sfm;

const char* const plugin_pathes[] =
{

};

void loadPlugin(const char* plugin_path);
void loadPlugins(const char* const *plugins);

int main()
{
    loadPlugins(plugin_pathes);

    RenderWindow render_window(1920, 1080, "MyPhotoshop v.2.1");

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
        render_window.display();
    }

    return 0;
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

    LoadPluginFunc loadPlugin = reinterpret_cast<LoadPluginFunc>(dlsym(pluginLib, "loadPlugin"));
    UnloadPluginFunc unloadPlugin = reinterpret_cast<UnloadPluginFunc>(dlsym(pluginLib, "unloadPlugin"));

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

    std::cout << "Plugin: \"" << plugin_path << "\"loaded successfully!\n";
}