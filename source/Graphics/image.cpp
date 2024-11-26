#include "image.hpp"

/*==========================< IImage implementation >=========================*/

std::unique_ptr<psapi::sfm::IImage> psapi::sfm::IImage::create()
{
    return std::make_unique<Image>();
}

/*============================================================================*/

/*===========================< Image implementation >=========================*/

psapi::sfm::Image::Image() :
    image_(),
    pos_  ()
{
}

void psapi::sfm::Image::create(unsigned int width, unsigned int height, const Color &color)
{
    image_.create(width, height, sf::Color(color.r, color.g, color.b, color.a));
}

void psapi::sfm::Image::create(vec2u size, const Color &color)
{
    image_.create(size.x, size.y, sf::Color(color.r, color.g, color.b, color.a));
}

void psapi::sfm::Image::create(unsigned int width, unsigned int height, const Color *pixels)
{
    image_.create(width, height, reinterpret_cast<const sf::Uint8*>(pixels));
}

void psapi::sfm::Image::create(vec2u size, const Color *pixels)
{
    image_.create(size.x, size.y, reinterpret_cast<const sf::Uint8*>(pixels));
}

bool psapi::sfm::Image::loadFromFile(const std::string &filename)
{
    return image_.loadFromFile(filename);
}

psapi::sfm::vec2u psapi::sfm::Image::getSize() const
{
    sf::Vector2u size = image_.getSize();
    return vec2u(size.x, size.y);
}

void psapi::sfm::Image::setPixel(unsigned int x, unsigned int y, const Color &color)
{
    image_.setPixel(x, y, sf::Color(color.r, color.g, color.b, color.a));
}

void psapi::sfm::Image::setPixel(vec2u pos, const Color &color)
{
    image_.setPixel(pos.x, pos.y, sf::Color(color.r, color.g, color.b, color.a));
}

psapi::sfm::Color psapi::sfm::Image::getPixel(unsigned int x, unsigned int y) const
{
    sf::Color color = image_.getPixel(x, y);
    return Color((uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b, (uint8_t)color.a);
}

psapi::sfm::Color psapi::sfm::Image::getPixel(vec2u pos) const
{
    sf::Color color = image_.getPixel(pos.x, pos.y);
    return Color((uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b, (uint8_t)color.a);
}

std::unique_ptr<psapi::sfm::IImage> psapi::sfm::Image::create()
{
    return std::make_unique<Image>();
}

//TODO: I need to understand, why we need in standard these functions!
psapi::sfm::vec2i psapi::sfm::Image::getPos() const
{
    return pos_;
}

void psapi::sfm::Image::setPos(const psapi::sfm::vec2i &pos)
{
    pos_ = pos;
}

/*============================================================================*/