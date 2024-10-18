#ifndef GRAPHICS_LIBRARY_SHAPE_HPP
#define GRAPHICS_LIBRARY_SHAPE_HPP

#include <SFML/Graphics.hpp>
#include "render_window.hpp"

namespace Graphics
{
    class Shape : public Drawable
    {
    public:
        Shape() = default;

        virtual ~Shape() = default;
        
        virtual void Draw                   (RenderWindow& window) const    = 0;
        virtual void SetFillColor           (const Color& color)            = 0;
        virtual void SetOutlineColor        (const Color& color)            = 0;
        virtual void SetPosition            (const WindowPoint& pos)        = 0;
        virtual void SetPosition            (int x, int y)                  = 0;
        virtual void Move                   (const WindowVector& dir)       = 0;
        virtual void MoveByX                (int dx)                        = 0;
        virtual void MoveByY                (int dy)                        = 0;
    };

    class Circle : public Shape
    {
    public:
         Circle(const WindowPoint& position, float radius, const Color& color = White);
        ~Circle() = default;

        virtual void Draw                   (RenderWindow& window)    const override;
        virtual void SetFillColor           (const Color& color)            override;
        virtual void SetOutlineColor        (const Color& color)            override;
        virtual void SetPosition            (const WindowPoint& pos)        override;
        virtual void SetPosition            (int x, int y)                  override;
        virtual void Move                   (const WindowVector& dir)       override;
        virtual void MoveByX                (int dx)                        override;
        virtual void MoveByY                (int dy)                        override;

    private:
        sf::CircleShape shape_;
        WindowPoint     position_;
        Color           color_;
        float           radius_;
    };

    class Rectangle : public Shape
    {
    public:
         Rectangle(const WindowPoint& position, std::size_t width, std::size_t height, const Color& color = White);
        ~Rectangle() = default;

        virtual void Draw                   (RenderWindow& window)    const override;
        virtual void SetFillColor           (const Color& color)            override;
        virtual void SetOutlineColor        (const Color& color)            override;
        virtual void SetPosition            (const WindowPoint& pos)        override;
        virtual void SetPosition            (int x, int y)                  override;
        virtual void Move                   (const WindowVector& dir)       override;
        virtual void MoveByX                (int dx)                        override;
        virtual void MoveByY                (int dy)                        override;

    private:
        sf::RectangleShape  shape_;
        WindowPoint         position_;
        Color               color_;
        std::size_t         width_;
        std::size_t         height_;
    };
}

#endif //GRAPHICS_LIBRARY_SHAPE_HPP