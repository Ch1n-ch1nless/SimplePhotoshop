#ifndef  SYSTEM_PLUGINS_FILTER_HPP
#define  SYSTEM_PLUGINS_FILTER_HPP

#include "../View/View.hpp" 

namespace sys_plugin
{
    const char* const BUMP_FILTER_BUTTON_TEXTURE   = "pictures/negative_filter_button.png";

    class BumpFilterAction : public ps::ABarAction
    {
    public:
         BumpFilterAction();
        ~BumpFilterAction() = default;
    
        virtual bool operator()(const ps::IRenderWindow* render_window, const ps::Event &event) override;
        virtual void activate() override;

    private:
        ps::Canvas* canvas_;
    };

    class BumpFilterButton : public ps::ABarButton
    {
    public:
        BumpFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, 
                             std::unique_ptr<BumpFilterAction>        action );
        
        virtual ~BumpFilterButton() override = default;

        virtual bool update(const ps::IRenderWindow* render_window, const ps::Event& event) override;

        static std::unique_ptr<BumpFilterButton> create();
    };
}

#endif //SYSTEM_PLUGINS_FILTER_HPP