#include "text.hpp"

/*==========================< Font implementation >===========================*/

psapi::sfm::Font::Font() :
    font_()
{
}

bool psapi::sfm::Font::loadFromFile(const std::string &filename)
{
    return font_.loadFromFile(filename);
}

std::unique_ptr<psapi::sfm::IFont> psapi::sfm::Font::create()
{
    return std::make_unique<psapi::sfm::Font>();
}

std::unique_ptr<psapi::sfm::IFont> psapi::sfm::IFont::create()
{
    return std::make_unique<psapi::sfm::Font>();
}

/*============================================================================*/

/*==========================< Text implementation >===========================*/

psapi::sfm::Text::Text() :
    text_()
{
}

void psapi::sfm::Text::draw(IRenderWindow *window) const
{
    RenderWindow* real_window = static_cast<RenderWindow*>(window);

    real_window->window_.draw(text_);
}

psapi::sfm::IntRect psapi::sfm::Text::getGlobalBounds() const
{
    psapi::sfm::vec2i pos  = vec2i{static_cast<int>(text_.getPosition().x), 
                                   static_cast<int>(text_.getPosition().y)};
    psapi::sfm::vec2u size = vec2u{static_cast<unsigned int>(text_.getGlobalBounds().width), 
                                   static_cast<unsigned int>(text_.getGlobalBounds().height)};
    
    return IntRect{pos, size};
}   

void psapi::sfm::Text::setString(const std::string &string)
{
    text_.setString(string);
}

void psapi::sfm::Text::setFont(const IFont *font)
{
    const Font* real_font = static_cast<const Font*>(font);

    text_.setFont(real_font->font_);
}

void psapi::sfm::Text::setCharacterSize(unsigned int size)
{
    text_.setCharacterSize(size);
}

void psapi::sfm::Text::setStyle(uint32_t style)
{
    text_.setStyle(style);
}

void psapi::sfm::Text::setPos(const psapi::sfm::vec2f &pos)  
{
    text_.setPosition(static_cast<float>(pos.x),
                      static_cast<float>(pos.y) );
}

void psapi::sfm::Text::setSize(const psapi::sfm::vec2f &size)
{
    float new_factorX = static_cast<float>(size.x) /
                        text_.getGlobalBounds().width;

    float new_factorY = static_cast<float>(size.y) /
                        text_.getGlobalBounds().height;

    text_.setScale(new_factorX, new_factorY);
}

void psapi::sfm::Text::setFillColor(const Color *color)
{
    text_.setFillColor(sf::Color(color->r, color->g, color->b, color->a));
}

void psapi::sfm::Text::setOutlineColor(const Color *color)
{
    text_.setOutlineColor(sf::Color(color->r, color->g, color->b, color->a));
}

void psapi::sfm::Text::setOutlineThickness(float thickness)
{
    text_.setOutlineThickness(thickness);
}

std::unique_ptr<psapi::sfm::IText> psapi::sfm::Text::create()
{
    return std::make_unique<psapi::sfm::Text>();
}

std::unique_ptr<psapi::sfm::IText> psapi::sfm::IText::create()
{
    return std::make_unique<psapi::sfm::Text>();
}

/*============================================================================*/