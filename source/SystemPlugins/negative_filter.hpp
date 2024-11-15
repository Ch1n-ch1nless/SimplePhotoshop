#ifndef  SYSTEM_PLUGINS_FILTER_HPP
#define  SYSTEM_PLUGINS_FILTER_HPP

#include "../View/View.hpp" 

namespace sys_plugin
{
    const char* const NEGATIVE_FILTER_BUTTON_TEXTURE   = "pictures/negative_filter_button.png";

    class NegativeFilterAction : public ps::ABarAction
    {
    public:
         NegativeFilterAction();
        ~NegativeFilterAction() = default;
    
        virtual bool operator()(const ps::IRenderWindow* render_window, const ps::Event &event) override;
        virtual void activate() override;

    private:
        ps::Canvas* canvas_;
    };

    class NegativeFilterButton : public ps::ABarButton
    {
    public:
        NegativeFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, 
                             std::unique_ptr<NegativeFilterAction>        action );
        
        virtual ~NegativeFilterButton() override = default;

        virtual bool update(const ps::IRenderWindow* render_window, const ps::Event& event) override;

        static std::unique_ptr<NegativeFilterButton> create();
    };
}

#endif //SYSTEM_PLUGINS_FILTER_HPP