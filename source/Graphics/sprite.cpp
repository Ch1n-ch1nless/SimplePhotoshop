#include "sprite.hpp"

using namespace psapi;
using namespace sfm;

/*===========================< Texture definition >===========================*/

bool Texture::create(unsigned int width, unsigned int height)
{
    texture_.create(width, height);
}

bool Texture::loadFromFile(const std::string& filename, const IntRect& area = IntRect())
{
    sf::IntRect rectangle = {area.top_x, area.top_y, area.width, area.height};
    texture_.loadFromFile(filename, rectangle);
}

bool Texture::loadFromMemory(const void* data, std::size_t size, const IntRect& area = IntRect())
{
    sf::IntRect rectangle = {area.top_x, area.top_y, area.width, area.height};
    texture_.loadFromMemory(data, size, rectangle);
}

bool Texture::loadFromImage(const AImage *image, const IntRect& area = IntRect())
{
    //TODO: Implement this function!!!
    static_assert(false, "Sorry, but you can not use class \'AImage\'!\n");
    return false;
}

vec2u Texture::getSize() const
{
    sf::Vector2u size = texture_.getSize();
    return vec2u{size.x, size.y};
}

std::unique_ptr<AImage> Texture::copyToImage() const
{
    //TODO: Implement this function!!!
    static_assert(false, "Sorry, but you can not use class \'AImage\'!\n");
    return nullptr;
}

void Texture::update(const Color *pixels)
{
    texture_.update(reinterpret_cast<const sf::Uint8*>(pixels));
}

void Texture::update(const Color *pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y) 
{
    texture_.update(reinterpret_cast<const sf::Uint8*>(pixels), width, height, x, y);
}

Texture& Texture::operator =(const ATexture& other)
{
    const Texture& real_texture = dynamic_cast<const Texture&>(other);

    if (this != &real_texture)
    {
        this->texture_ = real_texture.texture_;
    }

    return *this;
}

/*============================================================================*/

/*============================< Sprite definition >===========================*/

void Sprite::setTexture(const ATexture *texture, bool reset_rect = false)
{
    const Texture* real_texture = dynamic_cast<const Texture*>(texture);

    sprite_.setTexture(real_texture->texture_, reset_rect);
}

void Sprite::setTextureRect(const IntRect &area)
{
    sf::IntRect rectangle = {area.top_x, area.top_y, area.width, area.height};
    sprite_.setTextureRect(rectangle);
}

void Sprite::setPosition(float x, float y)
{
    sf::Vector2f vec(x, y);
    sprite_.setPosition(vec);
}

void Sprite::setPosition(const vec2f &pos)
{
    setPosition(pos.x, pos.y);
}

void Sprite::setScale(float factorX, float factorY)
{   
    sprite_.setScale(factorX, factorY);
}

void Sprite::setColor(const Color &color)
{
    sprite_.setColor(sf::Color(color.r, color.g, color.b, color.a));
}

void Sprite::setRotation(float angle)
{
    sprite_.setRotation(angle);
}

const vec2f Sprite::getPosition() const
{
    sf::Vector2f pos = sprite_.getPosition();
    return vec2f{pos.x, pos.y};
}

IntRect Sprite::getGlobalBounds() const
{
    sf::FloatRect area = sprite_.getGlobalBounds();
    return {(unsigned int)area.left, (unsigned int)area.top, (unsigned int)area.width, (unsigned int)area.height};
}

 void Sprite::draw(ARenderWindow *window)
 {
    RenderWindow* real_window = dynamic_cast<RenderWindow*>(window);

    real_window->window_.draw(sprite_);
 }  

/*============================================================================*/