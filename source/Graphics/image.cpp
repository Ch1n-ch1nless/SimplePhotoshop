#include "image.hpp"

/*==========================< IImage implementation >=========================*/

std::unique_ptr<psapi::sfm::IImage> psapi::sfm::IImage::create()
{
    return std::make_unique<Image>();
}

void psapi::sfm::IImage::create(unsigned int width, unsigned int height, const Color &color=Color(0, 0, 0))
{
    //TODO: Maybe cringe, but must work :)
    Image* real_ptr = static_cast<Image*>(this);
    real_ptr->create(width, height, color);
}

void psapi::sfm::IImage::create(vec2u size, const Color &color=Color(0, 0, 0))
{
    //TODO: Maybe cringe, but must work :)
    Image* real_ptr = static_cast<Image*>(this);
    real_ptr->create(size, color);
}

void psapi::sfm::IImage::create(unsigned int width, unsigned int height, const Color *pixels)
{
    //TODO: Maybe cringe, but must work :)
    Image* real_ptr = static_cast<Image*>(this);
    real_ptr->create(width, height, pixels);
}

void psapi::sfm::IImage::create(vec2u size, const Color *pixels)
{
    //TODO: Maybe cringe, but must work :)
    Image* real_ptr = static_cast<Image*>(this);
    real_ptr->create(size, pixels);
}

bool psapi::sfm::IImage::loadFromFile(const std::string &filename)
{
    //TODO: Maybe cringe, but must work :)
    Image* real_ptr = static_cast<Image*>(this);
    real_ptr->loadFromFile(filename);
}

psapi::sfm::vec2u psapi::sfm::IImage::getSize() const
{
    //TODO: Maybe cringe, but must work :)
    const Image* real_ptr = static_cast<const Image*>(this);
    return real_ptr->getSize();
}

void psapi::sfm::IImage::setPixel(unsigned int x, unsigned int y, const Color &color)
{
    //TODO: Maybe cringe, but must work :)
    Image* real_ptr = static_cast<Image*>(this);
    real_ptr->setPixel(x, y, color);
}

void psapi::sfm::IImage::setPixel(vec2u pos, const Color &color)
{
    //TODO: Maybe cringe, but must work :)
    Image* real_ptr = static_cast<Image*>(this);
    real_ptr->setPixel(pos, color);
}

psapi::sfm::Color psapi::sfm::IImage::getPixel(unsigned int x, unsigned int y) const
{
    //TODO: Maybe cringe, but must work :)
    const Image* real_ptr = static_cast<const Image*>(this);
    return real_ptr->getPixel(x, y);
}

psapi::sfm::Color psapi::sfm::IImage::getPixel(vec2u pos) const
{
    //TODO: Maybe cringe, but must work :)
    const Image* real_ptr = static_cast<const Image*>(this);
    return real_ptr->getPixel(pos);
}

/*============================================================================*/

/*===========================< Image implementation >=========================*/

void psapi::sfm::Image::create(unsigned int width, unsigned int height, const Color &color=Color(0, 0, 0))
{
    image_.create(width, height, sf::Color(color.r, color.g, color.b, color.a));
}

void psapi::sfm::Image::create(vec2u size, const Color &color=Color(0, 0, 0))
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
    image_.loadFromFile(filename);
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
    return Color(color.r, color.g, color.b, color.a);
}

psapi::sfm::Color psapi::sfm::Image::getPixel(vec2u pos) const
{
    sf::Color color = image_.getPixel(pos.x, pos.y);
    return Color(color.r, color.g, color.b, color.a);
}

std::unique_ptr<psapi::sfm::IImage> psapi::sfm::Image::create()
{
    return std::make_unique<Image>();
}

/*============================================================================*/