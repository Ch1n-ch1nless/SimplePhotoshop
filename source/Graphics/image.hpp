#ifndef  GRAPHICS_IMAGE_HPP
#define  GRAPHICS_IMAGE_HPP

#include "render_window.hpp"

namespace psapi
{
    namespace sfm
    {
        class Image final : public IImage
        {
        public:
             Image();
            virtual ~Image() final = default;

            void create(unsigned int width, unsigned int height, const Color &color=Color(0, 0, 0)) override;
            void create(vec2u size, const Color &color=Color(0, 0, 0)) override;

            void create(unsigned int width, unsigned int height, const Color *pixels) override;
            void create(vec2u size, const Color *pixels) override;

            bool loadFromFile(const std::string &filename) override;

            vec2u getSize() const override;
            void setPixel(unsigned int x, unsigned int y, const Color &color) override;
            void setPixel(vec2u pos, const Color &color) override;

            Color getPixel(unsigned int x, unsigned int y) const override;
            Color getPixel(vec2u pos) const override;

            virtual vec2i getPos() const override;
            virtual void setPos(const vec2i &pos) override;

            static std::unique_ptr<IImage> create();

        private:
            sf::Image image_;
            vec2i     pos_;

            friend class Texture;
            friend class RectangleShape;
            friend class EllipseShape;
        };

    } //sfm
    
} //psapi

#endif //GRAPHICS_IMAGE_HPP