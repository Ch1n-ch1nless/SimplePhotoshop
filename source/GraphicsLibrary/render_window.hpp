#ifndef GRAPHICS_LIBRARY_RENDER_WINDOW_HPP
#define GRAPHICS_LIBRARY_RENDER_WINDOW_HPP

#include "color.hpp"
#include "drawable.hpp"
#include "event.hpp"
#include "../MathTools/math_vector.hpp"

namespace Graphics
{
    using WindowPoint  = Math::Vector2d;
    using WindowVector = Math::Vector2d;

    class PixelArray;
    class Shape;
    class Sprite;

    class Line : public Drawable
    {
    public:
         Line(const WindowPoint& begin, const WindowPoint& end, const Color& color = Black);
        ~Line() = default;

        virtual void Draw(RenderWindow& window) override;

        friend class RenderWindow;

    private:
        WindowPoint begin_;
        WindowPoint end_;
        Color       color_;
    };

    class RenderWindow
    {
    public:
         RenderWindow(std::size_t width, std::size_t height, const char* window_name);
        ~RenderWindow() = default;

        std::size_t GetWidth()  const;
        std::size_t GetHeight() const;

        bool        IsOpen();
        void        Close();
        void        Clear();
        void        Display();

        bool        PollEvent(Event& event);

        void        DrawLines (const Line&       line);
        void        DrawPixels(const PixelArray& pixels);
        void        DrawShape (const Shape&      shape);
        void        DrawSprite(const Sprite&     sprite);

    private:
        sf::RenderWindow    window_;
        std::size_t         width_;
        std::size_t         height_;
    };
} // namespace Graphics


#endif //GRAPHICS_LIBRARY_RENDER_WINDOW_HPP