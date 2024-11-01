#include "View/View.hpp"

int main()
{
    psapi::sfm::RenderWindow render_window(1920, 1080, "TEST!!!");

    psapi::IWindowContainer* root_window = psapi::getRootWindow();

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