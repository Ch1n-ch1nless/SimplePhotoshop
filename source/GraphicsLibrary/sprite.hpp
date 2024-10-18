#ifndef GRAPHICS_LIBRARY_SPRITE_HPP
#define GRAPHICS_LIBRARY_SPRITE_HPP

#include "drawable.hpp"
#include "texture.hpp"
#include "render_window.hpp"

namespace Graphics
{
    class Sprite : public Drawable
    {
    public:
         Sprite() = default;
        ~Sprite() = default;

        virtual void    Draw        (RenderWindow& window) override; 

        void            SetTexture  (const Texture& texture);

        void            SetPosition (const WindowPoint& pos);
        WindowPoint     GetPosition ();

        void            SetColor    (const Color& color);
        Color           GetColor    ();

    private:
        sf::Sprite  sprite_;
        friend void RenderWindow::DrawSprite(const Sprite& sprite);
    };
}

#endif //GRAPHICS_LIBRARY_SPRITE_HPP