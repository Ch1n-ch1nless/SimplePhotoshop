#ifndef GRAPHICS_LIBRARY_EVENT_HPP
#define GRAPHICS_LIBRARY_EVENT_HPP

#include <SFML/Graphics.hpp>
#include "keyboard.hpp"
#include "mouse.hpp"

namespace Graphics
{
    class Event
    {
    public:
        enum class EventType
        {
            UNKNOWN         = -1,
            CLOSED          =  0,
            MOUSE_MOVED,
            MB_PRESSED,
            MB_RELEASED,
            NONE,
            KEY_PRESSED,
            KEY_RELEASED
        };
        
        class KeyEvent
        {
            friend class Event;

        public:
            KeyBoard::Key       key_code;   //!< Code of the key that has been pressed
            KeyBoard::ScanCode  scan_code;  //!< Physical code of the key that has been pressed            
            bool                alt;        //!< Button 'Alt'    press indicator 
            bool                control;    //!< Button 'Ctrl'   press indicator
            bool                shift;      //!< Button 'Shift'  press indicator
        };

        class MouseMoveEvent
        {
            friend class Event;

        public:
            WindowPoint pos;
        };

        class MouseButtonEvent
        {
            friend class Event;
        
        public:
            Mouse::MouseButton  button;
            WindowPoint         pos;
        };

        EventType           type()        const;

        KeyEvent            key()         const;
        MouseMoveEvent      mouseMove()   const;
        MouseButtonEvent    mouseButton() const;

    };
}

#endif //GRAPHICS_LIBRARY_EVENT_HPP