#ifndef  VIEW_SCROLLABLE_HPP
#define  VIEW_SCROLLABLE_HPP

#include "../Graphics/Graphics.hpp"

namespace ps
{
    class Scrollable
    {
    public:
        virtual ~Scrollable() = default;

        virtual void scroll(float offsetX, float offsetY)   = 0;
        virtual void scroll(const vec2f &offset)            = 0;

    protected:
        psapi::sfm::vec2i   object_position_;
        psapi::sfm::vec2u   object_size_;
        psapi::sfm::vec2i   visible_box_pos_;
        psapi::sfm::vec2u   visible_box_size_;
    };
}

#endif //VIEW_SCROLLABLE_HPP