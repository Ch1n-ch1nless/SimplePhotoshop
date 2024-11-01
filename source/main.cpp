#include "View/View.hpp"
#include "SystemPlugins/tool_bar.hpp"
#include "SystemPlugins/cat_button.hpp"

int main()
{
    psapi::sfm::RenderWindow render_window(1920, 1080, "TEST!!!");

    psapi::IWindowContainer* root_window = psapi::getRootWindow();

    root_window->addWindow(static_cast<std::unique_ptr<ps::AWindow>>(sys_plugin::ToolBar::create(1920, 1080)));

    sys_plugin::ToolBar* tool_bar = static_cast<sys_plugin::ToolBar*>(static_cast<ps::AWindow*>(root_window->getWindowById(psapi::kToolBarWindowId)));

    tool_bar->addWindow(static_cast<std::unique_ptr<ps::AWindow>>(sys_plugin::CatButton::create()));

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