#ifndef  SYSTEM_PLUGINS_BLUR_FILTER_HPP
#define  SYSTEM_PLUGINS_BLUR_FILTER_HPP

#include "../View/View.hpp"

namespace sys_plugin
{
    const char* const BLUR_FILTER_BUTTON_TEXTURE = "pictures/negative_filter_button.png";

    class BlurFilterAction : public ps::ABarAction
    {
    public:
        BlurFilterAction();

        virtual ~BlurFilterAction() override = default;

        virtual bool operator()(const ps::IRenderWindow* render_window, const ps::Event &event) override;
        virtual void activate() override;

    private:
        ps::Canvas* canvas_;
    };

    class BlurFilterButton : public ps::ABarButton
    {
    public:
        BlurFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, 
                         std::unique_ptr<BlurFilterAction>   action );
        
        virtual ~BlurFilterButton() override = default;

        virtual bool update(const ps::IRenderWindow* render_window, const ps::Event& event) override;

        static std::unique_ptr<BlurFilterButton> create();

    };
}

#endif //SYSTEM_PLUGINS_BLUR_FILTER_HPP