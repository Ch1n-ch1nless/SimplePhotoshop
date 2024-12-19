#ifndef  MY_API_MAIN_MENU_HPP
#define  MY_API_MAIN_MENU_HPP

#include "../../api/api_bar.hpp"
#include "bar.hpp"

namespace psapi
{
    class MenuButton : public ABarButton, public IMenuButton
    {
    public:
        MenuButton(std::unique_ptr<sfm::Texture> init_texture,
                   const IBar*                   nested_bar,
                   wid_t                         id             );

        ~MenuButton() override = default;

        virtual std::unique_ptr<IAction> createAction(const IRenderWindow* renderWindow, const Event& event) override = 0;

        virtual wid_t           getId()                          const override;
        virtual IWindow*        getWindowById(wid_t id)                override;
        virtual const IWindow*  getWindowById(wid_t id)          const override;
        virtual vec2i           getPos()                         const override;
        virtual vec2u           getSize()                        const override;
        virtual void            setSize(const vec2u& size)             override;
        virtual void            setPos(const vec2i& pos)               override;
        virtual void            setParent(const IWindow* parent)       override;
        virtual void            forceActivate()                        override;
        virtual void            forceDeactivate()                      override;
        virtual bool            isActive()                       const override;
        virtual bool            isWindowContainer()              const override;

        virtual void            draw(IRenderWindow* renderWindow)      override;

        virtual void            setState(State state) override;
        virtual State           getState() const     override;

        virtual void            addMenuItem(std::unique_ptr<IWindow> item) override;

        virtual void            activateMenu()                          override;
        virtual void            deactivateMenu()                        override;

        virtual IBar*           getMenu()                               override;
        virtual const IBar*     getMenu()                         const override;

    protected:

    };
}

#endif //MY_API_MAIN_MENU_HPP