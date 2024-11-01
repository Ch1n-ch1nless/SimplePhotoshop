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
         ToolBar();
        ~ToolBar() override = default;

        
    private:

    };
}

#endif //SYSTEM_PLUGINS_TOOL_BAR_HPP