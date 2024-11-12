#include "shape.hpp"
#include "sprite.hpp"
#include "image.hpp"

#include <cassert>

using namespace psapi;
using namespace sfm;

/*=======================< EllipseShape implementation >======================*/

EllipseShape::EllipseShape(unsigned int width, unsigned int height)
:
shape_(static_cast<float>(width) / 2.0f)
{
    setSize({width, height});
}

EllipseShape::EllipseShape(const vec2u &size)
:
    EllipseShape(size.x, size.y)
{
}

EllipseShape::EllipseShape(unsigned int radius)
:
    shape_(static_cast<float>(radius))
{
}

void EllipseShape::draw(IRenderWindow *window) const 
{
    auto sfmWindow = static_cast<RenderWindow*>(window);
    sfmWindow->window_.draw(shape_);
}

void EllipseShape::setTexture(const ITexture *texture)
{
    const auto sfm_texture = dynamic_cast<const sfm::Texture*>(texture);
    if (sfm_texture) 
    {
        shape_.setTexture(&sfm_texture->texture_);
    }
}

void EllipseShape::setFillColor(const Color &color)
{
    shape_.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

void EllipseShape::setPosition(const vec2i &pos)
{
    shape_.setPosition(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
}

void EllipseShape::setPosition(const vec2f &pos)
{
    shape_.setPosition(sf::Vector2f(pos.x, pos.y));
}

void EllipseShape::setPosition(const vec2d &pos)
{
    shape_.setPosition(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
}

void EllipseShape::setScale(const vec2f &scale)
{
    shape_.setScale(sf::Vector2f(scale.x, scale.y));
}

void EllipseShape::setSize(const vec2u &size)
{
    shape_.setRadius(static_cast<float>(size.x) / 2.0f);
    shape_.setScale(1.0f, static_cast<float>(size.y) / static_cast<float>(size.x));
}

void EllipseShape::setRotation(float angle) 
{
    shape_.setRotation(angle);
}

void EllipseShape::setOutlineColor(const Color &color) 
{
    shape_.setOutlineColor(sf::Color(color.r, color.g, color.b, color.a));
}

void EllipseShape::setOutlineThickness(float thickness) 
{
    shape_.setOutlineThickness(thickness);
}

float EllipseShape::getRotation() const 
{
    return shape_.getRotation();
}

vec2f EllipseShape::getScale() const 
{
    auto scale = shape_.getScale();
    return {scale.x, scale.y};
}

vec2f EllipseShape::getPosition() const 
{
    auto pos = shape_.getPosition();
    return {pos.x, pos.y};
}

const Color &EllipseShape::getFillColor() const 
{
    return reinterpret_cast<const Color&>(shape_.getFillColor());
}

vec2u EllipseShape::getSize() const 
{
    auto radius = shape_.getRadius();
    return {static_cast<unsigned int>(radius * 2.0f * shape_.getScale().x), static_cast<unsigned int>(radius * 2.0f * shape_.getScale().y)};
}

float EllipseShape::getOutlineThickness() const 
{
    return shape_.getOutlineThickness();
}

const Color &EllipseShape::getOutlineColor() const 
{
    return reinterpret_cast<const Color&>(shape_.getOutlineColor());
}

const IImage *EllipseShape::getImage() const 
{
    assert(false && "This function is not implemented");
    return nullptr;
}

void EllipseShape::move(const vec2f &offset)
{
    shape_.move(sf::Vector2f(offset.x, offset.y));
}

std::unique_ptr<IEllipseShape> IEllipseShape::create(unsigned int width, unsigned int height)
{
    return std::make_unique<EllipseShape>(width, height);    
}

std::unique_ptr<IEllipseShape> IEllipseShape::create(unsigned int radius)
{
    return std::make_unique<EllipseShape>(radius);
}

std::unique_ptr<IEllipseShape> IEllipseShape::create(const psapi::sfm::vec2u &size)
{
    return std::make_unique<EllipseShape>(size);
}

/*============================================================================*/

/*======================< RectangleShape implementation >=====================*/

psapi::sfm::RectangleShape::RectangleShape(unsigned int width, unsigned int height)
:
    shape_(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)))
{
}

RectangleShape::RectangleShape(const vec2u &size)
: 
    shape_(sf::Vector2f(static_cast<float>(size.x),  static_cast<float>(size.y))) 
{
}

void RectangleShape::draw(IRenderWindow *window) const 
{
    auto sfmWindow = static_cast<RenderWindow*>(window);
    sfmWindow->window_.draw(shape_);
}

void RectangleShape::setTexture(const ITexture *texture) 
{
    const auto sfm_texture = dynamic_cast<const Texture*>(texture);
    if (sfm_texture) 
    {
        shape_.setTexture(&sfm_texture->texture_);
    }
}

void RectangleShape::setFillColor(const Color &color) 
{
    shape_.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

void RectangleShape::setPosition(const vec2i &pos) 
{
    shape_.setPosition(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
}

void RectangleShape::setPosition(const vec2f &pos) 
{
    shape_.setPosition(sf::Vector2f(pos.x, pos.y));
}

void RectangleShape::setPosition(const vec2d &pos)
{
    shape_.setPosition(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
}

void RectangleShape::setScale(const vec2f &scale) 
{
    shape_.setScale(sf::Vector2f(scale.x, scale.y));
}

void RectangleShape::setSize(const vec2u &size)
{
    shape_.setSize(sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
}

void RectangleShape::setRotation(float angle) 
{
    shape_.setRotation(angle);
}

void RectangleShape::setOutlineColor(const Color &color)
{
    shape_.setOutlineColor(sf::Color(color.r, color.g, color.b, color.a));
}

void RectangleShape::setOutlineThickness(float thickness)
{
    shape_.setOutlineThickness(thickness);
}

float RectangleShape::getRotation() const
{
    return shape_.getRotation();
}

vec2f RectangleShape::getScale() const
{
    auto scale = shape_.getScale();
    return {scale.x, scale.y};
}

vec2f RectangleShape::getPosition() const
{
    auto pos = shape_.getPosition();
    return {pos.x, pos.y};
}

const Color &RectangleShape::getFillColor() const
{
    return reinterpret_cast<const Color&>(shape_.getFillColor());
}

vec2u RectangleShape::getSize() const
{
    auto size = shape_.getSize();
    return {static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y)};
}

float RectangleShape::getOutlineThickness() const
{
    return shape_.getOutlineThickness();
}

const Color &RectangleShape::getOutlineColor() const {
    return reinterpret_cast<const Color&>(shape_.getOutlineColor());
}

const IImage *RectangleShape::getImage() const
{
    assert(false && "This function is not implemented");
    return nullptr;
}

void RectangleShape::move(const vec2f &offset) {
    shape_.move(sf::Vector2f(offset.x, offset.y));
}

std::unique_ptr<IRectangleShape> IRectangleShape::create(unsigned int width,
                                                         unsigned int height) {
    return std::make_unique<RectangleShape>(width, height); 
}

std::unique_ptr<IRectangleShape> IRectangleShape::create(const vec2u &size) {
    return std::make_unique<RectangleShape>(size);
}

/*============================================================================*/
