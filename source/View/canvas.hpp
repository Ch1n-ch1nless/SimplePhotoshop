#ifndef  VIEW_CANVAS_HPP
#define  VIEW_CANVAS_HPP

#include "window.hpp"
#include "../Standard/api_canvas.hpp"

namespace ps
{
    class Layer : public psapi::ILayer
    {
    public:
        Layer(const vec2i &position, const vec2u &size);

        virtual ~Layer() = default;

        virtual psapi::sfm::Color   getPixel(psapi::sfm::vec2i pos) const override;
        virtual void                setPixel(psapi::sfm::vec2i pos, psapi::sfm::Color pixel) override;

        virtual void resize(const vec2u &new_size);

    private:
        std::vector<psapi::sfm::Color> data_;

        ps::vec2i   pos_;
        ps::vec2u   size_;
    };

    class Canvas : public psapi::ICanvas, public AWindow
    {
    public:


    private:

    };
}

#endif //VIEW_CANVAS_HPP