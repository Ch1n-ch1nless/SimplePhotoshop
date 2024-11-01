#ifndef  VIEW_BAR_HPP
#define  VIEW_BAR_HPP

#include "../Standard/api_bar.hpp"
#include "../Graphics/Graphics.hpp"
#include "window.hpp"

namespace ps
{
    class ABarButton : public psapi::IBarButton, public AWindowVector
    {
    public:
        virtual ~ABarButton() override = default;

        virtual void setState(State state) override;
        virtual State getState() const override;  

    protected:
        State state_;
    };

    class ABar : public psapi::IBar, public AWindowVector
    {

    };
}

#endif //VIEW_BAR_HPP