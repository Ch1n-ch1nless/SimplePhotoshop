#ifndef GRAPHICS_MOUSE_HPP
#define GRAPHICS_MOUSE_HPP

#include "math_vector.hpp"
#include "drawble.hpp"

namespace psapi
{
    namespace sfm
    {
        class Mouse
        {
        public:
            enum class Button
            {
                LEFT,
                RIGHT,
                MIDDLE,

                XBUTTON1,
                XBUTTON2
            };

            enum class Wheel
            {
                Vertical,
                Horizontal,
            };

            Mouse() = delete;

            static bool isButtonPressed(Button button);

            static Vec2D<int> getPosition();
            static Vec2D<int> getPosition(const ARenderWindow *relative_to);

            static void setPosition(const Vec2D<int> &position);
            static void setPosition(const Vec2D<int> &position, const ARenderWindow *relative_to);
        };

    } //sfm

} //psapi

#endif //GRAPHICS_MOUSE_HPP