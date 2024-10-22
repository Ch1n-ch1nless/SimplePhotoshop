#include "color.hpp"

using namespace psapi;
using namespace sfm;

Color::Color(const Color& other) :
    r(other.r),
    g(other.g),
    b(other.b),
    a(other.a)
{
}

Color::Color(uint8_t init_r, uint8_t init_g, uint8_t init_b, uint8_t init_a) :
    r(init_r),
    g(init_g),
    b(init_b),
    a(init_a)
{
}

static uint8_t AddChannels(uint8_t left, uint8_t right)
{
    uint16_t sum_of_chanels = (uint16_t)left + (uint16_t)right;
    return (sum_of_chanels > 255) ? (uint8_t)255 : static_cast<uint8_t>(sum_of_chanels);
}

Color& Color::operator+=(const Color& color)
{
    r = AddChannels(r, color.r);
    g = AddChannels(g, color.g);
    b = AddChannels(b, color.b);
    a = AddChannels(a, color.a);

    return *this;
}

static uint8_t MulChannels(uint8_t chanel, double cf)
{
    double new_value = chanel * cf;

    return (new_value > 255.0) ? (uint8_t)255 : static_cast<uint8_t>(new_value);
}

static uint8_t MulChannels(uint8_t chanel, float cf)
{
    float new_value = chanel * cf;

    return (new_value > 255.f) ? (uint8_t)255 : static_cast<uint8_t>(new_value);
}

Color& Color::operator*=(const Color& other)
{
    r = MulChannels(r, other.r / 255.0);
    g = MulChannels(g, other.g / 255.0);
    b = MulChannels(b, other.b / 255.0);
    a = MulChannels(a, other.a / 255.0);

    return *this;
}

Color& Color::operator*=(const double cf)
{
    r = MulChannels(r, cf);
    g = MulChannels(g, cf);
    b = MulChannels(b, cf);
    a = MulChannels(a, cf);

    return *this;
}

Color& Color::operator*=(const float cf)
{
    r = MulChannels(r, cf);
    g = MulChannels(g, cf);
    b = MulChannels(b, cf);
    a = MulChannels(a, cf);

    return *this;
}

Color operator+(const Color &x, const Color &y)
{
    Color tmp = x;
    tmp += y;
    return tmp;
}

Color operator*(const Color &x, const Color &y)
{
    Color tmp = x;
    tmp *= y;
    return tmp;
}

Color operator*(const Color &x, const float cf)
{
    Color tmp = x;
    tmp *= cf;
    return tmp;
}

Color operator*(const Color &x, const double cf)
{
    Color tmp = x;
    tmp *= cf;
    return tmp;
}

Color operator*(const float cf, const Color &x)
{
    Color tmp = x;
    tmp *= cf;
    return tmp;
}

Color operator*(const double cf, const Color &x)
{
    Color tmp = x;
    tmp *= cf;
    return tmp;
}