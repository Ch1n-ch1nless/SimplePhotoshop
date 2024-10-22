#include "render_window.hpp"

using namespace psapi;
using namespace sfm;

RenderWindow::RenderWindow(size_t width, size_t height, const std::string& window_title)
    : window_(sf::VideoMode(width, height), window_title)
{
}

void RenderWindow::clear()
{
    window_.clear();
}

void RenderWindow::close()
{
    window_.close();
}

void RenderWindow::display()
{
    window_.display();
}

void RenderWindow::draw(Drawable* target)
{
    target->draw(this);
}

bool RenderWindow::isOpen()
{
    return window_.isOpen();
}

bool RenderWindow::pollEvent(Event& event)
{
    //TODO: implement ...
}
