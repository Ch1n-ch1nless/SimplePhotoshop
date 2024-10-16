#ifndef GRAPHICS_LIBRARY_PIXEL_ARRAY_HPP
#define GRAPHICS_LIBRARY_PIXEL_ARRAY_HPP

#include "render_window.hpp"

namespace Graphics
{
    class PixelArray : public Drawable
    {
    public:
         PixelArray(std::size_t width, std::size_t height, const WindowPoint& position, const Color& background_color = White);
         PixelArray(const PixelArray& pixel_array);
        ~PixelArray();

        PixelArray& operator = (PixelArray& other);

        void    SetPixel(std::size_t x, std::size_t y, const Color& color);
        void    SetPixel(const WindowPoint& pos, const Color& color);
        Color   GetPixel(std::size_t x, std::size_t y) const;
        Color   GetPixel(const WindowPoint& pos) const;

        void    Move    (const WindowVector& direction);
        void    MoveByX (int dx);
        void    MoveByY (int dy);

        std::size_t GetWidth () const;
        std::size_t GetHeight() const;

        WindowPoint GetTopLeftCorner() const;
        WindowPoint GetCenter() const;

        virtual void Draw(RenderWindow& window) override;

        friend class RenderWindow;

    private:
        sf::Uint8*      data_;
        WindowPoint     pos_;
        std::size_t     width_;
        std::size_t     height_;
        Color           back_color_;
    };
} //namespace Graphics

#endif //GRAPHICS_LIBRARY_PIXEL_ARRAY_HPP