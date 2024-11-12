#ifndef  VIEW_TRANSFORMABLE_HPP
#define  VIEW_TRANSFORMABLE_HPP

#include "../Standard/api_system.hpp"

namespace ps
{
    class Transformable
    {
    public:
        Transformable() = default;
        virtual ~Transformable() = default;

        virtual void moveee(float offsetX, float offsetY)     = 0;
        virtual void moveee(psapi::sfm::vec2f offset)         = 0;

        virtual void scaleee(float factorX, float factorY)    = 0;
        virtual void scaleee(psapi::sfm::vec2f factor)        = 0;
    };
}

#endif //VIEW_TRANSFORMABLE_HPP