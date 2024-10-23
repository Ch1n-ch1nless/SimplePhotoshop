#include "image.hpp"

using namespace psapi;
using namespace sfm;

Image::Image(size_t init_size) : 
    points_ (sf::Points, init_size),
    size_   (init_size)
{
}

void Image::setColor(const Color &color, size_t ind)
{
    points_[ind].color = sf::Color(color.r, color.g, color.b, color.a);
}

void Image::draw(ARenderWindow* window)
{
    RenderWindow* real_window = static_cast<RenderWindow*>(window);
    real_window->window_.draw(points_);
}

void Image::setPosition(const vec2i &coord, size_t ind)
{
    points_[ind].position = sf::Vector2f(static_cast<float>(coord.x), static_cast<float>(coord.y));
}

void Image::setPosition(const vec2f &coord, size_t ind)
{
    points_[ind].position = sf::Vector2f(coord.x, coord.y);
}

void Image::setPosition(const vec2d &coord, size_t ind)
{
    points_[ind].position = sf::Vector2f(static_cast<float>(coord.x), static_cast<float>(coord.y));
}

void Image::setPosition(int x, int y, size_t ind)
{
    points_[ind].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}

void Image::setPosition(float x, float y, size_t ind)
{
    points_[ind].position = sf::Vector2f(x, y);
}

void Image::setPosition(double x, double y, size_t ind)
{
    points_[ind].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}

