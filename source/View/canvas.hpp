#ifndef  GRAPHICS_CANVAS_HPP
#define  GRAPHICS_CANVAS_HPP

#include "../Standard/api_canvas.hpp"
#include "../Graphics/Graphics.hpp"

namespace psapi
{
    class Layer : public ILayer
    {
    public:
         Layer(vec2i size);
        ~Layer() = default;

        sfm::Color getPixel(sfm::vec2i pos) const override;
        void       setPixel(sfm::vec2i pos, sfm::Color pixel) override;

        void       resize(vec2i new_size);

    private:
        friend class Canvas;

        vec2i size_;

        std::vector<sfm::Color> pixels_;
    };

    class Canvas : public ICanvas
    {
    public:
        //...

    private:
        //...
    };

}
#endif //GRAPHICS_CANVAS_HPP