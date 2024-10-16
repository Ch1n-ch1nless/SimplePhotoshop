#include "pixel_array.hpp"
#include "render_window.hpp"
#include <cassert>
#include <cstring>

using namespace Graphics;

std::size_t GetPixelPos(std::size_t x, std::size_t y, std::size_t width)
{
    return (x + y * width) * NumBytesInColor;
}

Graphics::PixelArray::PixelArray(std::size_t width, std::size_t height, const WindowPoint &position, const Color &background_color) :
    data_       (nullptr),
    width_      (width),
    height_     (height),
    pos_        (position),
    back_color_ (background_color)
{
    data_ = new sf::Uint8[width_ * height_ * NumBytesInColor];
    
    for (std::size_t y = 0; y < height_; ++y)
    {
        for (std::size_t x = 0; x < width_; ++x)
        {
            data_[GetPixelPos(x, y, width_) + 0] = back_color_.GetRedColor();
            data_[GetPixelPos(x, y, width_) + 1] = back_color_.GetGreenColor();
            data_[GetPixelPos(x, y, width_) + 2] = back_color_.GetBlueColor();
            data_[GetPixelPos(x, y, width_) + 3] = back_color_.GetAlphaColor();
        }
    }
}

Graphics::PixelArray::PixelArray(const PixelArray& pixel_array) :
    data_       (nullptr),
    width_      (pixel_array.width_),
    height_     (pixel_array.height_),
    pos_        (pixel_array.pos_),
    back_color_ (pixel_array.back_color_)
{
    data_ = new sf::Uint8[width_ * height_ * NumBytesInColor];
    memcpy(data_, pixel_array.data_, height_ * width_ * NumBytesInColor);
}

Graphics::PixelArray::~PixelArray()
{
    delete[] data_;
}

PixelArray& Graphics::PixelArray::operator=(PixelArray& other)
{
    if (this == &other) return other;

    delete[] data_;

    width_      = other.width_;
    height_     = other.height_;
    pos_        = other.pos_;
    back_color_ = other.back_color_;

    data_ = new sf::Uint8[width_ * height_ * NumBytesInColor];
    memcpy(data_, other.data_, height_ * width_ * NumBytesInColor);

    return *this;
}

void Graphics::PixelArray::SetPixel(std::size_t x, std::size_t y, const Color &color)
{
    //TODO: assert -> my exception
    assert((x < width_ && y < height_) && "ERROR!!! Point (x, y) does not belong the pixel array!\n");

    data_[GetPixelPos(x, y, width_) + 0] = color.GetRedColor();
    data_[GetPixelPos(x, y, width_) + 1] = color.GetGreenColor();
    data_[GetPixelPos(x, y, width_) + 2] = color.GetBlueColor();
    data_[GetPixelPos(x, y, width_) + 3] = color.GetAlphaColor();
}

void Graphics::PixelArray::SetPixel(const WindowPoint &pos, const Color &color)
{
    SetPixel(pos.GetX(), pos.GetY(), color);
}

Color Graphics::PixelArray::GetPixel(std::size_t x, std::size_t y) const
{
     //TODO: assert -> my exception
    assert((x < width_ && y < height_) && "ERROR!!! Point (x, y) does not belong the pixel array!\n");

    chanel_t red    = data_[GetPixelPos(x, y, width_) + 0];
    chanel_t green  = data_[GetPixelPos(x, y, width_) + 1];
    chanel_t blue   = data_[GetPixelPos(x, y, width_) + 2];
    chanel_t alpha  = data_[GetPixelPos(x, y, width_) + 3];

    return Color(red, green, blue, alpha);
}

Color Graphics::PixelArray::GetPixel(const WindowPoint &pos) const
{
    return GetPixel(pos.GetX(), pos.GetY());
}

void Graphics::PixelArray::Move(const WindowVector &direction)
{
    MoveByX(direction.GetX());
    MoveByY(direction.GetY());
}

void Graphics::PixelArray::MoveByX(int dx)
{
    if (dx == 0) return;

    if (dx > 0)
    {
        for (unsigned int y = 0; y < height_; ++y)
        {
            for (unsigned int x = width_ - 1; x >= static_cast<unsigned int>(std::max(dx, 0)); --x)
            {
                SetPixel(x, y, GetPixel(x - dx, y));
            }
            for (unsigned int x = ((unsigned int)dx - 1 < width_ - 1) ? (unsigned int)dx - 1 : width_ - 1; x + 1 > 0; --x)
            {
                SetPixel(x, y, back_color_);
            }
        }
    }
    else
    {
        for (unsigned int y = 0; y < height_; ++y)
        {
            for (unsigned int x = 0; x - dx < width_; ++x)
            {
                SetPixel(x, y, GetPixel(x - dx, y));
            }
            for (unsigned int x = (width_ + dx > 0u) ? width_ + dx : 0u; x < width_; ++x)
            {
                SetPixel(x, y, back_color_);
            }
        }
    }
}

void Graphics::PixelArray::MoveByY(int dy)
{
    if (dy == 0) return;

    if (dy > 0)
    {
        for (unsigned int x = 0; x < width_; ++x)
        {
            for (unsigned int y = height_ - 1; y >= static_cast<unsigned int>(std::max(dy, 0)); --y)
            {
                SetPixel(x, y, GetPixel(x, y - dy));
            }
            for (unsigned int y = ((unsigned int)dy - 1 < height_ - 1) ? (unsigned int)dy - 1 : height_ - 1; y + 1 > 0; --y)
            {
                SetPixel(x, y, back_color_);
            }
        }
    }
    else
    {
        for (unsigned int x = 0; x < width_; ++x)
        {
            for (unsigned int y = 0; y - dy < height_; ++y)
            {
                SetPixel(x, y, GetPixel(x, y - dy));
            }
            for (unsigned int y = (height_ + dy > 0u) ? height_ + dy : 0u; y < height_; ++y)
            {
                SetPixel(x, y, back_color_);
            }
        }
    }
}

std::size_t Graphics::PixelArray::GetWidth() const
{
    return width_;
}

std::size_t Graphics::PixelArray::GetHeight() const
{
    return height_;
}

WindowPoint Graphics::PixelArray::GetTopLeftCorner() const
{
    return pos_;
}

WindowPoint Graphics::PixelArray::GetCenter() const
{
    return WindowPoint(pos_.GetX() + width_ / 2, pos_.GetY() + height_ / 2);
}

void Graphics::PixelArray::Draw(RenderWindow& window)
{
    window.DrawPixels(*this);
}
