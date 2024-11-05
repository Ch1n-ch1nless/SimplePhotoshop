#ifndef  SYSTEM_PLUGINS_CAT_BUTTON_HPP
#define  SYSTEM_PLUGINS_CAT_BUTTON_HPP

#include "tool_bar.hpp"

namespace sys_plugin
{
    const char* const CAT_BUTTON_TEXTURE = "pictures/cat_button.png";

    class CatButtonAction : public ps::ABarAction
    {
    public:
        virtual ~CatButtonAction() override = default;

        virtual bool operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event) override;

        virtual void activate() override;
    };

    class CatButton : public ps::ABarButton
    {
    public:
        CatButton(  std::unique_ptr<psapi::sfm::Sprite> sprite, 
                    std::unique_ptr<CatButtonAction>    action );
        
        virtual ~CatButton() override = default;

        static std::unique_ptr<CatButton> create();
    };
}

#endif //SYSTEM_PLUGINS_CAT_BUTTON_HPP