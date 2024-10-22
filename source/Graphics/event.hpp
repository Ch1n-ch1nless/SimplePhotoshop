#ifndef GRAPHICS_EVENT_HPP
#define GRAPHICS_EVENT_HPP

#include "math_vector.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

#include <cstdint>

namespace psapi
{
    namespace sfm
    {
        class Event
        {
        public:
            struct SizeEvent
            {
                unsigned int width;
                unsigned int height;
            };

            struct KeyEvent
            {
                Keyboard::Key code;
                bool          alt;
                bool          control;
                bool          shift;
                bool          system;
            };

            struct TextEvent
            {
                uint32_t unicode;
            };

            struct MouseMoveEvent
            {
                int x;
                int y;
            };

            struct MouseButtonEvent
            {
                Mouse::Button button;
                int           x;
                int           y;
            };

            struct MouseWheelScrollEvent
            {
                Mouse::Wheel wheel;
                float        delta;
                int          x;
                int          y;
            };

            enum EventType
            {
                Unknown,
                Closed,
                Resized,
                LostFocus,
                GainedFocus,
                TextEntered,
                KeyPressed,
                KeyReleased,
                MouseWheelScrolled,
                MouseButtonPressed,
                MouseButtonReleased,
                MouseMoved,
                MouseEntered,
                MouseLeft,
            };

            EventType type;

            union
            {
                SizeEvent             size;
                KeyEvent              key;
                TextEvent             text;
                MouseMoveEvent        mouseMove;
                MouseButtonEvent      mouseButton;
                MouseWheelScrollEvent mouseWheel;
            };

        };
    }   
}

#endif //GRAPHICS_EVENT_HPP