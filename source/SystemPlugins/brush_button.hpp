#ifndef  SYSTEM_PLUGINS_BRUSH_BUTTON_HPP
#define  SYSTEM_PLUGINS_BRUSH_BUTTON_HPP

#include "tool_bar.hpp"
#include "../Standard/plugin_example.hpp"

#include <deque>

namespace sys_plugin
{
    const char* const BRUSH_BUTTON_TEXTURE  = "pictures/brush_button.png";
    const int         BRUSH_RADIUS          = 5;

    class BrushAction : public ps::ABarAction
    {
    public:
        BrushAction();

        virtual ~BrushAction() override = default;

        virtual bool operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event) override;

        virtual void activate() override;

    private:
        ps::Canvas* canvas_;

        std::deque<psapi::vec2i> mouse_points_;

        psapi::vec2i    interpolateHermite( float         t,
                                            psapi::vec2i &point0,
                                            psapi::vec2i &point1,
                                            psapi::vec2i &point2,
                                            psapi::vec2i &point3 );

        size_t          calculateStepsNumber(psapi::vec2i &point1, psapi::vec2i &point2);

        void            paintNewCircle();
    };

    class BrushButton : public ps::ABarButton
    {
    public:
        BrushButton(std::unique_ptr<psapi::sfm::Sprite> sprite, 
                    std::unique_ptr<BrushAction>        action );
        
        virtual ~BrushButton() override = default;

        static std::unique_ptr<BrushButton> create();
    };
}

#endif //SYSTEM_PLUGINS_BRUSH_BUTTONS_HPP