#include "sprite.hpp"

#include <cassert>

using namespace psapi;
using namespace sfm;

/*===========================< Texture definition >===========================*/

std::unique_ptr<ITexture> ITexture::create()
{
    return std::make_unique<Texture>();
}

std::unique_ptr<ITexture> Texture::create()
{
    return std::make_unique<Texture>();
}

bool Texture::create(unsigned int width, unsigned int height)
{
    texture_.create(width, height);
}

bool Texture::loadFromFile(const std::string& filename, const IntRect& area)
{
    sf::IntRect rectangle = {area.top_x, area.top_y, area.width, area.height};
    return texture_.loadFromFile(filename, rectangle);
}

bool Texture::loadFromMemory(const void* data, std::size_t size, const IntRect& area)
{
    sf::IntRect rectangle = {area.top_x, area.top_y, area.width, area.height};
    texture_.loadFromMemory(data, size, rectangle);
}

std::unique_ptr<IImage> Texture::copyToImage() const
{
    assert(false && "Sorry, but why do you use this function?\n Do you really need it?\n I think, you are tired and you need go from the room.\n Phone on this number: +7(952)812\n");
    return nullptr;
}

vec2u Texture::getSize() const
{
    sf::Vector2u size = texture_.getSize();
    return vec2u{size.x, size.y};
}

void Texture::update(const Color *pixels)
{
    texture_.update(reinterpret_cast<const sf::Uint8*>(pixels));
}

void Texture::update(const Color *pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y) 
{
    texture_.update(reinterpret_cast<const sf::Uint8*>(pixels), width, height, x, y);
}

void Texture::update(const IImage *image)
{
    assert(false && "Sorry, but why do you use this function?\n Do you really need it?\n I think, you are tired and you need go from the room.\n Phone on this number: +7(952)812\n");
}

/*============================================================================*/

/*============================< Sprite definition >===========================*/

void Sprite::setTexture(const ITexture *texture, bool reset_rect)
{
    const Texture* real_texture = static_cast<const Texture*>(texture);

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

vec2i Sprite::getSize() const
{
    sf::Vector2u vec = sprite_.getTexture()->getSize();
    return vec2i(vec.x, vec.y);
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

 void Sprite::draw(IRenderWindow *window)
 {
    RenderWindow* real_window = static_cast<RenderWindow*>(window);

    real_window->window_.draw(sprite_);
 }  

 std::unique_ptr<ISprite> Sprite::create()
 {
    return std::make_unique<Sprite>();
 }

 std::unique_ptr<ISprite> ISprite::create()
 {
    return std::make_unique<Sprite>();
 }

/*============================================================================*/