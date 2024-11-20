#ifndef  SYSTEM_PLUGINS_UNSHARP_MASK_FILTER_HPP
#define  SYSTEM_PLUGINS_UNSHARP_MASK_FILTER_HPP

#include "../View/View.hpp"

namespace sys_plugin
{
    const char* const UNSHARP_MASK_FILTER_BUTTON_TEXTURE = "pictures/negative_filter_button.png";

    class UnsharpMaskFilterAction : public ps::ABarAction
    {
    public:
        UnsharpMaskFilterAction(double sigma, int radius);

        virtual ~UnsharpMaskFilterAction() override = default;

        virtual bool operator()(const ps::IRenderWindow* render_window, const ps::Event &event) override;
        virtual void activate() override;

    private:
        std::vector<std::vector<double>> kernel_;

        ps::Canvas* canvas_;

        const double sigma_;
        const int    radius_;

        void fillKernel();
    };

    class UnsharpMaskFilterButton : public ps::ABarButton
    {
    public:
        UnsharpMaskFilterButton(std::unique_ptr<psapi::sfm::Sprite> sprite, 
                         std::unique_ptr<UnsharpMaskFilterAction>   action );
        
        virtual ~UnsharpMaskFilterButton() override = default;

        virtual bool update(const ps::IRenderWindow* render_window, const ps::Event& event) override;

        static std::unique_ptr<UnsharpMaskFilterButton> create();

    };
}

#endif //SYSTEM_PLUGINS_UNSHARP_MASK_FILTER_HPP