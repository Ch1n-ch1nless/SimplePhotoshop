#ifndef GRAPHICS_LIBRARY_COLOR_HPP
#define GRAPHICS_LIBRARY_COLOR_HPP

#include <SFML/Graphics.hpp>

namespace Graphics
{
    using chanel_t = uint8_t;

    const std::size_t MaxValueOfChanel  = 255;
    const std::size_t NumBytesInColor   = 4; 

    class Color
    {
    public:
         Color();
         Color(chanel_t red, chanel_t green, chanel_t blue, chanel_t alpha);

         Color(const Color& other);

        ~Color() = default;

        Color& operator =       (const Color& color);

        Color& operator +=      (const Color& other);
        Color& operator *=      (const Color& other);
        Color& operator *=      (const double coefficient);

        const chanel_t& GetRedColor    () const;
        const chanel_t& GetGreenColor  () const;
        const chanel_t& GetBlueColor   () const;
        const chanel_t& GetAlphaColor  () const;

    private:
        chanel_t red_;
        chanel_t green_;
        chanel_t blue_;
        chanel_t alpha_;
    };

    Color operator + (const Color& left,        const Color& right);
    Color operator * (const Color& left,        const Color& right);
    Color operator * (const Color& color,       const double coefficient);
    Color operator * (const double coefficient, const Color& color);

    const Color White   = {255, 255, 255, 255};
    const Color Red     = {255,   0,   0, 255};
    const Color Green   = {  0, 255,   0, 255};
    const Color Blue    = {  0,   0, 255, 255};
    const Color Black   = {  0,   0,   0, 255};

} //namespace Graphics

#endif //SIMPLE_PHOTOSHOP_GRAPHICS_LIBRARY_COLOR_HPP