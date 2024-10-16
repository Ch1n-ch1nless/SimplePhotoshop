#include "color.hpp"

Graphics::Color::Color() :
    red_    (0),
    green_  (0),
    blue_   (0),
    alpha_  (0)
{
}

Graphics::Color::Color (chanel_t red, chanel_t green, chanel_t blue, chanel_t alpha) :
    red_    (red),
    green_  (green),
    blue_   (blue),
    alpha_  (alpha)
{
}

Graphics::Color::Color(const Color& other) :
    red_    (other.red_),
    green_  (other.green_),
    blue_   (other.blue_),
    alpha_  (other.alpha_)
{
}

Graphics::Color& Graphics::Color::operator=(const Color& other)
{
    this->red_      = other.red_;
    this->green_    = other.green_;
    this->blue_     = other.blue_;
    this->alpha_    = other.alpha_;

    return *this;
}

static Graphics::chanel_t AddChanels(const Graphics::chanel_t one, const Graphics::chanel_t two)
{
    uint16_t sum_of_chanels = (uint16_t)one + (uint16_t)two;
    return (sum_of_chanels > (uint16_t)Graphics::MaxValueOfChanel) ? Graphics::MaxValueOfChanel : static_cast<Graphics::chanel_t>(sum_of_chanels);
}

Graphics::Color& Graphics::Color::operator+=(const Color& other)
{
    red_    = AddChanels(red_,   other.red_);
    green_  = AddChanels(green_, other.green_);
    blue_   = AddChanels(blue_,  other.blue_);
    alpha_  = AddChanels(alpha_, other.alpha_);

    return *this;
}

static Graphics::chanel_t MulChanels(const Graphics::chanel_t value, const double scalar)
{
    double new_value = scalar * value;

    return (new_value > (double)Graphics::MaxValueOfChanel) ? Graphics::MaxValueOfChanel : static_cast<Graphics::chanel_t>(new_value);
}

Graphics::Color& Graphics::Color::operator*=(const double coefficient)
{
    red_    = MulChanels(red_,   coefficient);
    green_  = MulChanels(green_, coefficient);
    blue_   = MulChanels(blue_,  coefficient);
    alpha_  = MulChanels(alpha_, coefficient);
}

Graphics::Color& Graphics::Color::operator+=(const Color& other)
{
    red_    = MulChanels(red_,   (static_cast<double>(other.red_)    / static_cast<double>(MaxValueOfChanel)));
    green_  = MulChanels(green_, (static_cast<double>(other.green_)  / static_cast<double>(MaxValueOfChanel)));
    blue_   = MulChanels(blue_,  (static_cast<double>(other.blue_)   / static_cast<double>(MaxValueOfChanel)));
    alpha_  = MulChanels(alpha_, (static_cast<double>(other.alpha_)  / static_cast<double>(MaxValueOfChanel)));

    return *this;
}

const Graphics::chanel_t& Graphics::Color::GetRedColor() const
{
    return red_;
}

const Graphics::chanel_t& Graphics::Color::GetGreenColor() const
{
    return green_;
}

const Graphics::chanel_t& Graphics::Color::GetBlueColor() const
{
    return blue_;
}

const Graphics::chanel_t& Graphics::Color::GetAlphaColor() const
{
    return alpha_;
}

Graphics::Color operator + (const Graphics::Color& left, const Graphics::Color& right)
{
    Graphics::Color new_color = left;
    new_color += right;
    return new_color;
}

Graphics::Color operator * (const Graphics::Color& left, const Graphics::Color& right)
{
    Graphics::Color new_color = left;
    new_color *= right;
    return new_color;
}

Graphics::Color operator * (const Graphics::Color& color, const double coefficient)
{
    Graphics::Color new_color = color;
    new_color *= coefficient;
    return new_color;
}

Graphics::Color operator * (const double coefficient, const Graphics::Color& color)
{
    Graphics::Color new_color = color;
    new_color *= coefficient;
    return new_color;
}