#include "texture.hpp"

Graphics::Texture::Texture(std::size_t width, std::size_t height) :
    texture_()
{
    texture_.create(width, height);
}

bool Graphics::Texture::LoadFile(const char *filename)
{
    return texture_.loadFromFile(filename);
}

Graphics::WindowPoint Graphics::Texture::GetScale()
{
    return WindowPoint(texture_.getSize().x, texture_.getSize().y);
}

Graphics::Texture Graphics::Texture::LoadTexture(const char *filename)
{
    Texture texture;
    texture.LoadFile(filename);
    return texture;
}
