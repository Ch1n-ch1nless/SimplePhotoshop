#ifndef  GRAPHICS_PIXELS_ARRAY_HPP
#define  GRAPHICS_PIXELS_ARRAY_HPP

#include "render_window.hpp"

namespace psapi
{
    namespace sfm
    {
        class PixelsArray final : public IPixelsArray
        {
        public:
             PixelsArray(size_t init_size);
            ~PixelsArray() final = default;

            virtual void draw(IRenderWindow* render_window) const override;

            virtual void setColor(const Color &color, size_t ind) override;
            virtual Color getColor(size_t ind) const override;

            virtual void setPosition(const vec2i &coord, size_t ind) override;
            virtual void setPosition(const vec2f &coord, size_t ind) override;
            virtual void setPosition(const vec2d &coord, size_t ind) override;
            virtual void setPosition(int x, int y, size_t ind) override;
            virtual void setPosition(float x, float y, size_t ind) override;
            virtual void setPosition(double x, double y, size_t ind) override;

            static std::unique_ptr<IPixelsArray> create();

        private:
            sf::VertexArray data_;
            size_t          size_;
        };

    }

}

#endif //GRAPHICS_PIXELS_ARRAY_HPP