#ifndef  SYSTEM_PLUGINS_TOOL_BAR_HPP
#define  SYSTEM_PLUGINS_TOOL_BAR_HPP

#include "../View/View.hpp"

namespace sys_plugin
{
    const char* const TOOL_BAR_BACKGROUND       = "pictures/tool_bar_background.png";

    const char* const TOOL_BAR_BUTTON_PRESSED   = "pictures/pressed_skin.png";
    const char* const TOOL_BAR_BUTTON_HOVERED   = "pictures/hovered_skin.png";
    const char* const TOOL_BAR_BUTTON_RELEASED  = "pictures/released_skin.png";

    class ToolBar : public ps::ABar
    {
    public:
         ToolBar(std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
                 std::unique_ptr<psapi::sfm::Sprite> hover_button,
                 std::unique_ptr<psapi::sfm::Sprite> press_button,
                 std::unique_ptr<psapi::sfm::Sprite> release_button,
                 const ps::vec2i    &bar_position,
                 const ps::vec2u    &bar_size,
                 const ps::vec2u    &button_size, 
                 const size_t   &number_buttons_in_row,
                 const ps::wid_t    &id                                     );
        
        ~ToolBar() override = default;

        static std::unique_ptr<ToolBar> create(const size_t width, const size_t height);
    };
}

#endif //SYSTEM_PLUGINS_TOOL_BAR_HPP