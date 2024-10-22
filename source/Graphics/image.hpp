#ifndef  GRAPHICS_IMAGE_HPP
#define  GRAPHICS_IMAGE_HPP

#include "render_window.hpp"

namespace psapi
{
    namespace sfm
    {
        class Image : public AImage
        {
        public:
             Image() = default;
            ~Image() = default;

            virtual void setColor(const Color &color, size_t ind) override;

            virtual void setPosition(const vec2i &coord, size_t ind) override;
            virtual void setPosition(const vec2f &coord, size_t ind) override;
            virtual void setPosition(const vec2d &coord, size_t ind) override;

            virtual void setPosition(int    x, int    y, size_t ind) override;
            virtual void setPosition(float  x, float  y, size_t ind) override;
            virtual void setPosition(double x, double y, size_t ind) override;

            virtual void draw(ARenderWindow *window) override;
        };

    } //sfm

} //psapi

#endif //GRAPHICS_IMAGE_HPP