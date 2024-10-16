#ifndef GRAPHICS_LIBRARY_DRAWABLE_HPP
#define GRAPHICS_LIBRARY_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

namespace Graphics
{
    class RenderWindow;

    class Drawable
    {
    public:
        virtual void Draw(RenderWindow& window) = 0;

        virtual ~Drawable() = default;
    };

} //namespace Graphics

#endif //GRAPHICS_LIBRARY_DRAWABLE_HPP