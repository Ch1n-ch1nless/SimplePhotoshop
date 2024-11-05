#ifndef  SYSTEM_PLUGINS_HPP
#define  SYSTEM_PLUGINS_HPP

#include "tool_bar.hpp"

namespace sys_plugin
{
    const char* const PENCIL_BUTTON_TEXTURE = "pictures/pencil_button.png";

    class PencilAction : public ps::ABarAction
    {
    public:
        PencilAction(psapi::ICanvas* canvas);

        virtual ~PencilAction() override = default;

        virtual bool operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event) override;

        virtual void activate() override;

    private:
        psapi::ICanvas* canvas_;
    };

    class PencilButton : public ps::ABarButton
    {
    public:
        PencilButton(std::unique_ptr<psapi::sfm::Sprite>    sprite, 
                     std::unique_ptr<PencilAction>          action );
        
        virtual ~PencilButton() override = default;

        static std::unique_ptr<PencilButton> create(psapi::ICanvas* canvas);
    };
};

#endif //SYSTEM_PLUGINS_HPP