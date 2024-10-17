#ifndef GRAPHICS_LIBRARY_MOUSE_HPP
#define GRAPHICS_LIBRARY_MOUSE_HPP

#include <SFML/Window/Mouse.hpp>
#include "math_vector.hpp"

namespace Graphics
{
    using WindowPoint = Vector2d;
    
    class RenderWindow;

    class Mouse
    {
    public:
        enum class MouseButton
        {
            Left,           //!< The left mouse button
            Right,          //!< The right mouse button
            Middle,         //!< The middle (wheel) mouse button
            XButton1,       //!< The first extra mouse button
            XButton2,       //!< The second extra mouse button

            ButtonCount     //!< Keep last -- the total number of mouse buttons
        };

        enum class MouseWheel
        {
            VerticalWheel,  //!< The vertical mouse wheel 
            HorizontalWheel //!< The horizontal mouse wheel
        };

    private:
        static bool         IsMouseButtonPressed(MouseButton the_button);

        static WindowPoint  GetPosition();
        static WindowPoint  GetPosition(const RenderWindow& window);
        static void         SetPosition(const WindowPoint& new_position);
        static void         SetPosition(const WindowPoint& new_position, const RenderWindow& window);
    };

} //namespace Graphics

#endif //GRAPHICS_LIBRARY_MOUSE_HPP