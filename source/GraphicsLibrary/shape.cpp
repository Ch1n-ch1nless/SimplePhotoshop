#include "shape.hpp"

/*============================< CIRCLE FUNCTIONS >============================*/

Graphics::Circle::Circle(const WindowPoint& position, float radius, const Color& color = White) :
    position_   (position),
    radius_     (radius),
    color_      (color),
    shape_      ()
{
    shape_.setRadius(radius_);
    shape_.setFillColor(sf::Color(color.GetRedColor(), color.GetGreenColor(), color.GetBlueColor(), color.GetAlphaColor()));
    shape_.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
}

Graphics::Circle::~Circle()
{
}

void Graphics::Circle::Draw(RenderWindow &window) const
{
    window.DrawShape(*this);
}

void Graphics::Circle::SetFillColor(const Color &color)
{
    color_ = color;
    shape_.setFillColor(sf::Color(color.GetRedColor(), color.GetGreenColor(), color.GetBlueColor(), color.GetAlphaColor()));
}

void Graphics::Circle::SetOutlineColor(const Color &color)
{
    shape_.setOutlineColor(sf::Color(color.GetRedColor(), color.GetGreenColor(), color.GetBlueColor(), color.GetAlphaColor()));
}

void Graphics::Circle::SetPosition(const WindowPoint &pos)
{
    position_ = pos;
    shape_.setPosition(sf::Vector2f(pos.GetX(), pos.GetY()));
}

void Graphics::Circle::SetPosition(int x, int y)
{
    position_ = WindowPoint(x, y);
    shape_.setPosition(sf::Vector2f(x, y));
}

void Graphics::Circle::Move(const WindowVector &dir)
{
    position_ += dir;
    shape_.setPosition(sf::Vector2f(position_.GetX(), position_.GetY()));
}

void Graphics::Circle::MoveByX(int dx)
{
    position_ += WindowPoint(dx, 0);
    shape_.setPosition(sf::Vector2f(position_.GetX(), position_.GetY()));
}

void Graphics::Circle::MoveByY(int dy)
{
    position_ += WindowPoint(0, dy);
    shape_.setPosition(sf::Vector2f(position_.GetX(), position_.GetY()));
}

const sf::Shape& Graphics::Circle::GetShape() const
{
    return shape_;
}

/*============================================================================*/

/*===========================< RECTANGLE FUNCTIONS >==========================*/

Graphics::Rectangle::Rectangle(const WindowPoint &position, std::size_t width, std::size_t height, const Color &color) :
    position_   (position),
    color_      (color),
    width_      (width),
    height_     (height),
    shape_      ()
{
    shape_.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
    shape_.setFillColor(sf::Color(color.GetRedColor(), color.GetGreenColor(), color.GetBlueColor(), color.GetAlphaColor()));
    shape_.setSize(sf::Vector2f(width, height));
}

void Graphics::Rectangle::Draw(RenderWindow &window) const
{
    window.DrawShape(*this);
}

void Graphics::Rectangle::SetFillColor(const Color &color)
{
    color_ = color;
    shape_.setFillColor(sf::Color(color.GetRedColor(), color.GetGreenColor(), color.GetBlueColor(), color.GetAlphaColor()));
}

void Graphics::Rectangle::SetOutlineColor(const Color &color)
{
    shape_.setOutlineColor(sf::Color(color.GetRedColor(), color.GetGreenColor(), color.GetBlueColor(), color.GetAlphaColor()));
}

void Graphics::Rectangle::SetPosition(const WindowPoint &pos)
{
    position_ = pos;
    shape_.setPosition(sf::Vector2f(pos.GetX(), pos.GetY()));
}

void Graphics::Rectangle::SetPosition(int x, int y)
{
    position_ = WindowPoint(x, y);
    shape_.setPosition(sf::Vector2f(x, y));
}

void Graphics::Rectangle::Move(const WindowVector &dir)
{
    position_ += dir;
    shape_.setPosition(sf::Vector2f(position_.GetX(), position_.GetY()));
}

void Graphics::Rectangle::MoveByX(int dx)
{
    position_ += WindowPoint(dx, 0);
    shape_.setPosition(sf::Vector2f(position_.GetX(), position_.GetY()));
}

void Graphics::Rectangle::MoveByY(int dy)
{
    position_ += WindowPoint(0, dy);
    shape_.setPosition(sf::Vector2f(position_.GetX(), position_.GetY()));
}

const sf::Shape& Graphics::Rectangle::GetShape() const
{
    return shape_;
}

/*============================================================================*/
