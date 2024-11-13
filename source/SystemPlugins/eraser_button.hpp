#ifndef  SYSTEM_PLUGINS_ERASER_HPP
#define  SYSTEM_PLUGINS_ERASER_HPP

#include "tool_bar.hpp"
#include "../Standard/plugin_example.hpp"

#include <deque>

namespace sys_plugin
{
    const char* const ERASER_BUTTON_TEXTURE = "pictures/eraser_button.png";
    const int         ERASER_RADIUS         = 10;

    class EraserAction : public ps::ABarAction
    {
    public:
        EraserAction();

        virtual ~EraserAction() override = default;

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

    class EraserButton : public ps::ABarButton
    {
    public:
        EraserButton(std::unique_ptr<psapi::sfm::Sprite> sprite, 
                     std::unique_ptr<EraserAction>       action );
        
        virtual ~EraserButton() override = default;

        static std::unique_ptr<EraserButton> create();
    };
}

#endif //SYSTEM_PLUGINS_ERASER_HPP