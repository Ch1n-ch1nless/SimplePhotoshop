#include "pixel_array.hpp"
#include "render_window.hpp"

/*-----------------------------< Line functions >-----------------------------*/

Graphics::Line::Line(const WindowPoint &begin, const WindowPoint &end, const Color& color = Black) :
    begin_  (begin),
    end_    (end),
    color_  (color)
{
}

void Graphics::Line::Draw(RenderWindow &window)
{
    window.DrawLines(*this);
}

/*----------------------------------------------------------------------------*/

/*-------------------------< RenderWindow functions >-------------------------*/

Graphics::RenderWindow::RenderWindow(std::size_t width, std::size_t height, const char *window_name) :
    window_ (sf::VideoMode((unsigned int)width, (unsigned int)height), window_name),
    width_  (width),
    height_ (height)
{
}

std::size_t Graphics::RenderWindow::GetWidth() const
{
    return width_;
}

std::size_t Graphics::RenderWindow::GetHeight() const
{
    return height_;
}

bool Graphics::RenderWindow::IsOpen()
{
    return window_.isOpen();
}

void Graphics::RenderWindow::Close()
{
    window_.close();
}

void Graphics::RenderWindow::Clear()
{
    window_.clear();
}

void Graphics::RenderWindow::Display()
{
    window_.display();
}

bool Graphics::RenderWindow::PollEvent(Graphics::Event& event)
{
    // TODO: implement this code!

    return false;
}

void Graphics::RenderWindow::DrawLines(const Line &line)
{
    sf::Color sf_color = {line.color_.GetRedColor(), line.color_.GetGreenColor(), line.color_.GetBlueColor(), line.color_.GetAlphaColor()};

     sf::Vertex sf_line[] = 
    {
        sf::Vertex(sf::Vector2f((float)line.begin_.GetX(), (float)line.begin_.GetY()), sf_color),
        sf::Vertex(sf::Vector2f((float)line.end_.GetX(),   (float)line.end_.GetY()  ), sf_color)
    };

    window_.draw(sf_line, 2, sf::Lines);    // TODO: Magic constant! NEED TO FIX!
}

void Graphics::RenderWindow::DrawPixels(const PixelArray &pixels)
{
    sf::Texture texture;
    texture.create(pixels.width_, pixels.height_);
    texture.update(pixels.data_);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    window_.draw(sprite);
}

void Graphics::RenderWindow::DrawShape(const Shape &shape)
{
    // TODO: implement!
}

void Graphics::RenderWindow::DrawSprite(const Sprite &sprite)
{
    // TODO: implement!
}

/*----------------------------------------------------------------------------*/
