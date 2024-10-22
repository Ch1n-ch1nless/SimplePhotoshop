#ifndef GRAPHICS_COLOR_HPP
#define GRAPHICS_COLOR_HPP

#include <cstdint>

namespace psapi
{
    namespace sfm
    {
        struct Color
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;

            Color( const Color &color);
            Color( uint8_t init_r, uint8_t init_g, uint8_t init_b, uint8_t init_a);
            ~Color();

            Color &operator+=(const Color &color);
            Color &operator*=(const Color &color);
            Color &operator*=(const double cf);
            Color &operator*=(const float cf);
        };

        Color operator+(const Color  &x, const Color  &y);
        Color operator*(const Color  &x, const Color  &y);
        Color operator*(const Color  &x, const float  cf);
        Color operator*(const Color  &x, const double cf);
        Color operator*(const float  cf, const Color  &x);
        Color operator*(const double cf, const Color  &x);

    }   //sfm

}   //psapi

#endif