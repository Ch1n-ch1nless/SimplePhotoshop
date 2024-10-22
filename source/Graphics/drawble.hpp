#ifndef GRAPHICS_DRAWABLE_HPP
#define GRAPHICS_DRAWABLE_HPP

namespace psapi
{
    namespace sfm
    {
        class ARenderWindow;

        class Drawable
        {
        public:
            virtual ~Drawable() = default;

            virtual void draw(ARenderWindow *window) = 0;
        };

    } //sfm

} //psapi

#endif //GRAPHICS_DRAWABLE_HPP