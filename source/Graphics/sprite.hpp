#ifndef  GRAPHICS_SPRITE_HPP
#define  GRAPHICS_SPRITE_HPP

#include "render_window.hpp"

namespace psapi
{
    namespace sfm
    {
        class Texture : public ATexture
        {
        public:
             Texture() = default;
            ~Texture() = default;

            virtual bool create(unsigned int width, unsigned int height)                                     override;
            virtual bool loadFromFile  (const std::string& filename,        const IntRect& area = IntRect()) override;
            virtual bool loadFromMemory(const void* data, std::size_t size, const IntRect& area = IntRect()) override;
            virtual bool loadFromImage (const AImage *image,                const IntRect& area = IntRect()) override;
            virtual vec2u getSize() const                                                                    override;
            virtual std::unique_ptr<AImage> copyToImage() const                                              override;
            virtual void update(const Color *pixels)                                                         override;
            virtual void update(const Color *pixels, unsigned int width, unsigned int height,
                                                     unsigned int x,     unsigned int y) override;


            virtual Texture& operator =(const ATexture& other) override;

        private:
            sf::Texture texture_;
            
            friend class Sprite;
        };

        class Sprite : public ASprite
        {
        public:
             Sprite() = default;
            ~Sprite() = default;

            virtual void setTexture(const ATexture *texture, bool reset_rect = false) override;
            virtual void setTextureRect(const IntRect &rectangle) override;

            virtual void setPosition(float x, float y) override;
            virtual void setPosition(const vec2f &pos) override;

            virtual void setScale(float factorX, float factorY) override;

            virtual void setColor(const Color &color) override;

            virtual void setRotation(float angle) override;

            virtual const vec2f getPosition() const override;
            virtual IntRect getGlobalBounds() const override;

            virtual void draw(ARenderWindow *window) override;

        private:
            sf::Sprite sprite_;
        };

    } //sfm

} //psapi

#endif //GRAPHICS_SPRITE_HPP