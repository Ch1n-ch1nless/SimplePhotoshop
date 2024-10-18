#include "sprite.hpp"

void Graphics::Sprite::Draw(RenderWindow &window)
{
    window.DrawSprite(*this);
}

void Graphics::Sprite::SetTexture(const Texture &texture)
{
    sprite_.setTexture(texture.texture_);
}

void Graphics::Sprite::SetPosition(const WindowPoint &pos)
{
    sprite_.setPosition(sf::Vector2f(pos.GetX(), pos.GetY()));
}

Graphics::WindowPoint Graphics::Sprite::GetPosition()
{
    sf::Vector2f vec = sprite_.getPosition();
    return WindowPoint((int)vec.x, (int)vec.y);
}

void Graphics::Sprite::SetColor(const Color &color)
{
    sprite_.setColor(sf::Color(color.GetRedColor(), color.GetGreenColor(), color.GetBlueColor(), color.GetAlphaColor()));
}

Graphics::Color Graphics::Sprite::GetColor()
{
    sf::Color color = sprite_.getColor();
    return Color(color.r, color.g, color.b, color.a);
}


