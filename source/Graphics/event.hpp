#ifndef GRAPHICS_EVENT_HPP
#define GRAPHICS_EVENT_HPP

#include "math_vector.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

namespace psapi
{
    namespace sfm
    {
        class Event
        {
        public:
            enum class EventType
            {
                CLOSED,
                MOUSE_MOVED,
                MB_PRESSED,
                MB_RELEASED,
                NONE
            };

            class KeyEvent
            {
                friend class Event;

            public:
                Keyboard::Key code;
                bool          alt;
                bool          control;
                bool          shift;
            };

            class MouseMoveEvent
            {
                friend class Event;

            public:
                Vec2D<int> pos;
            };

            class MouseButtonEvent
            {
                friend class Event;

            public:
                Mouse::Button button;
                Vec2D<int> pos;
            };

            EventType type() const;

            KeyEvent         key         () const;
            MouseMoveEvent   mouse_move  () const;
            MouseButtonEvent mouse_button() const;

        };
    }   
}

#endif //GRAPHICS_EVENT_HPP