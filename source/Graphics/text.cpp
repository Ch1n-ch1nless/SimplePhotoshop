#include "text.hpp"

bool psapi::sfm::Font::loadFromFile(const std::string &filename)
{
    return font_.loadFromFile(filename);
}

void psapi::sfm::Text::draw(ARenderWindow *window)
{
    RenderWindow* real_window = static<RenderWindow*>(window);

    real_window->window_.draw(text_);
}

void psapi::sfm::Text::setString(const std::string &string)
{
    text_.setString(string);
}

void psapi::sfm::Text::setFont(const AFont *font)
{
    const Font* real_font = static<const Font*>(font);

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
