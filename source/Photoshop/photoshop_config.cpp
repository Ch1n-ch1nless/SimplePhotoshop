#include "../../api/api_photoshop.hpp"

namespace psapi
{
    sfm::IntRect getCanvasIntRect()
    {
        auto screen_size = getScreenSize();
        return sfm::IntRect{sfm::vec2i(0.15 * screen_size.x, 0.05 * screen_size.y),
                            sfm::vec2u(0.7 * screen_size.x , 0.85 * screen_size.y)};
    }

    sfm::IntRect getToolbarIntRect()
    {
        auto screen_size = getScreenSize();
        return sfm::IntRect{sfm::vec2i(0, 0.05 * screen_size.y),
                            sfm::vec2u(0.125 * screen_size.x, 0.875 * screen_size.y)};
    }

    sfm::IntRect getMenuBarIntRect()
    {
        auto screen_size = getScreenSize();
        return sfm::IntRect{sfm::vec2i(0, 0),
                            sfm::vec2u(screen_size.x, 0.025 * screen_size.y)};
    }

    sfm::IntRect getOptionsBarIntRect()
    {
        auto screen_size = getScreenSize();
        return sfm::IntRect{sfm::vec2i(0.875 * screen_size.x, 0.05 * screen_size.y),
                            sfm::vec2u(0.125 * screen_size.x, 0.875 * screen_size.y)};
    }

    sfm::vec2u getScreenSize()
    {
        return sfm::vec2u(1920, 1080);
    }
}
