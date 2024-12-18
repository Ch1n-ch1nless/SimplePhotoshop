#include "../../api/api_system.hpp"

#include <cassert>

psapi::sfm::Color psapi::sfm::Color::getStandardColor(Type color)
{
    switch (color)
    {
    case Type::Black:
        return Color{0, 0, 0, 255};

    case Type::White:
        return Color{255, 255, 255, 255};

    case Type::Red:
        return Color{255, 0, 0, 255};

    case Type::Green:
        return Color{0, 255, 0, 255};

    case Type::Blue:
        return Color{0, 0, 255, 255};

    case Type::Yellow:
        return Color{255, 255, 0, 255};

    case Type::Magenta:
        return Color{255, 0, 255, 255};

    case Type::Cyan:
        return Color{0, 255, 255, 255};

    case Type::Transparent:
        return Color{0, 0, 0, 0};
    
    default:
        assert(false);
        break;
    }
}