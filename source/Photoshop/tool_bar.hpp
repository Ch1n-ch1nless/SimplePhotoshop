#ifndef  MY_API_TOOL_BAR_HPP
#define  MY_API_TOOL_BAR_HPP

#include "bar.hpp"

namespace psapi
{
    class ToolBar final : public ABar
    {
    public:
         ToolBar();
        ~ToolBar() final = default;
    };
}

#endif //MY_API_TOOL_BAR_HPP