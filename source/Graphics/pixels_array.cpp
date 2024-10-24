#include "pixels_array.hpp"

#include <cassert>

const size_t INIT_SIZE = 1024;

/*=======================< IPixelsArray implementation >======================*/

std::unique_ptr<psapi::sfm::IPixelsArray> psapi::sfm::IPixelsArray::create()
{
    return std::make_unique<psapi::sfm::PixelsArray>(INIT_SIZE);
}

/*============================================================================*/

/*=======================< PixelsArray implementation >=======================*/

psapi::sfm::PixelsArray::PixelsArray(size_t init_size) :
    data_(sf::Points, init_size),
    size_(init_size)
{
}

void psapi::sfm::PixelsArray::setColor(const Color &color, size_t ind)
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    data_[ind].color = sf::Color(color.r, color.g, color.b, color.a);
}
        
psapi::sfm::Color psapi::sfm::PixelsArray::getColor(size_t ind) const
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    sf::Color color = data_[ind].color;
    return Color(color.r, color.g, color.b, color.a);
}
        
void psapi::sfm::PixelsArray::setPosition(const vec2i &coord, size_t ind)
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    data_[ind].position = sf::Vector2f((float)coord.x, (float)coord.y);
}
        
void psapi::sfm::PixelsArray::setPosition(const vec2f &coord, size_t ind)
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    data_[ind].position = sf::Vector2f(coord.x, coord.y);
}
        
void psapi::sfm::PixelsArray::setPosition(const vec2d &coord, size_t ind)
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    data_[ind].position = sf::Vector2f((float)coord.x, (float)coord.y);
}
        
void psapi::sfm::PixelsArray::setPosition(int x, int y, size_t ind)
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    data_[ind].position = sf::Vector2f((float)x, (float)y);
}
        
void psapi::sfm::PixelsArray::setPosition(float x, float y, size_t ind)
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    data_[ind].position = sf::Vector2f(x, y);
}
        
void psapi::sfm::PixelsArray::setPosition(double x, double y, size_t ind)
{
    assert((ind < size_) && "ERROR!!! Invalid index!\n");
    data_[ind].position = sf::Vector2f((float)x, (float)y);
}

std::unique_ptr<psapi::sfm::IPixelsArray> psapi::sfm::PixelsArray::create()
{
    return std::make_unique<psapi::sfm::PixelsArray>(INIT_SIZE);
}

void psapi::sfm::PixelsArray::draw(psapi::sfm::IRenderWindow* window)
{
    RenderWindow* real_window = static_cast<RenderWindow*>(window);
    real_window->window_.draw(data_);
}

/*============================================================================*/