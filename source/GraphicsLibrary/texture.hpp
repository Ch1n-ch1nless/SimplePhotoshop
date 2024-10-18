#ifndef GRAPHICS_LIBRARY_TEXTURE_HPP
#define GRAPHICS_LIBRARY_TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include "math_vector.hpp"

namespace Graphics
{
    using WindowPoint = Vector2d;

    class Sprite;

    class Texture
    {
    public:
         Texture() = default;
         Texture(std::size_t width, std::size_t height);
        ~Texture();

        bool            LoadFile(const char* filename);
        
        WindowPoint     GetScale();

        static Texture  LoadTexture(const char* filename);

    private:
        sf::Texture texture_;
        friend class Sprite;
    };

} //namespace Graphics

#endif //GRAPHICS_LIBRARY_TEXTURE_HPP