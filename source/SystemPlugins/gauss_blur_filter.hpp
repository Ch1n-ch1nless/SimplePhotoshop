#ifndef  SYSTEM_PLUGINS_GAUSS_BLUR_FILTER_HPP
#define  SYSTEM_PLUGINS_GAUSS_BLUR_FILTER_HPP

#include "../View/View.hpp"

namespace sys_plugin
{
    const char* GAUSS_BLUR_FILTER_BUTTON_TEXTURE = "pictures/negative_filter_button.png";

    class GaussBlurFilterAction : public ps::ABarAction
    {
    public:
        GaussBlurFilterAction(double sigma, int radius);
        virtual ~GaussBlurFilterAction() override = default;

        virtual bool operator()(const ps::IRenderWindow* render_window, const ps::Event &event) override;
        virtual void activate() override;

    private:
        std::vector<std::vector<double>> gauss_matrix_;

        ps::Canvas*  canvas_;

        const double sigma_;
        const int    radius_;

        void fillGaussMatrix();
    };

    class GaussBlurFilterButton : public ps::ABarButton
    {
    public:
        GaussBlurFilterButton(std::unique_ptr<psapi::sfm::Sprite>    sprite_,
                              std::unique_ptr<GaussBlurFilterAction> action  );

        virtual ~GaussBlurFilterButton() override = default;

        virtual bool update(const ps::IRenderWindow* render_window, const ps::Event& event) override;

        static std::unique_ptr<GaussBlurFilterButton> create();
    };
}

#endif //SYSTEM_PLUGINS_GAUSS_BLUR_FILTER_HPP