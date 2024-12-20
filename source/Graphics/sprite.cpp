#include "sprite.hpp"

#include <cassert>

using namespace psapi;
using namespace sfm;

/*===========================< Texture definition >===========================*/

Texture::Texture() :
    texture_()
{
}

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
    return texture_.create(width, height);
}

bool Texture::loadFromFile(const std::string& filename, const IntRect& area)
{
    sf::IntRect rectangle = {area.pos.x, area.pos.y, (int)area.size.x, (int)area.size.y};
    return texture_.loadFromFile(filename, rectangle);
}

bool Texture::loadFromMemory(const void* data, std::size_t size, const IntRect& area)
{
    sf::IntRect rectangle = {area.pos.x, area.pos.y, (int)area.size.x, (int)area.size.y};
    return texture_.loadFromMemory(data, size, rectangle);
}

std::unique_ptr<IImage> Texture::copyToImage() const
{
    std::unique_ptr<IImage> new_image = Image::create();

    Image* temp_ptr = static_cast<Image*>(new_image.get());
    temp_ptr->image_ = texture_.copyToImage();

    return new_image;
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
    const Image* temp_ptr = static_cast<const Image*>(image);
    texture_.update(temp_ptr->image_);
}

/*============================================================================*/

/*============================< Sprite definition >===========================*/

Sprite::Sprite() :
    sprite_()
{
}

void Sprite::setTexture(const ITexture *texture, bool reset_rect)
{
    const Texture* real_texture = static_cast<const Texture*>(texture);

    sprite_.setTexture(real_texture->texture_, reset_rect);
}

void Sprite::setTextureRect(const IntRect &area)
{
    sf::IntRect rectangle = {area.pos.x, area.pos.y, (int)area.size.x, (int)area.size.y};
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

vec2u Sprite::getSize() const
{
    sf::Vector2u vec = sprite_.getTexture()->getSize();
    return vec2u(vec.x, vec.y);
}

void Sprite::setColor(const Color &color)
{
    sprite_.setColor(sf::Color(color.r, color.g, color.b, color.a));
}

Color Sprite::getColor() const
{
    sf::Color cur_color = sprite_.getColor();
    return Color{cur_color.r, cur_color.g, cur_color.b, cur_color.a};
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
    return IntRect{vec2i{(int)area.left, (int)area.top}, vec2u{(unsigned int)area.width, (unsigned int)area.height}};
}

 void Sprite::draw(IRenderWindow *window) const
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