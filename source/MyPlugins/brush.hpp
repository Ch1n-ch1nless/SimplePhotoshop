#ifndef  MY_PLUGIN_BRUSH_HPP
#define  MY_PLUGIN_BRUSH_HPP

#include "../Photoshop/Photoshop.hpp"

namespace psapi
{
    class BrushButton : public ABarButton
    {
    public:
         BrushButton();
        ~BrushButton() final = default;

        std::unique_ptr<IAction>
        createAction(const IRenderWindow* renderWindow, const Event& event) override;

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

    private:
        bool update(const IRenderWindow* render_window, const Event& event);

        friend class BrushAction;
    };

    class BrushAction final : public IAction
    {
    public:
         BrushAction(BrushButton *button, const IRenderWindow *renderWindow, const Event &event);
        ~BrushAction() final = default;

        bool execute   (const Key& key) override;
        bool isUndoable(const Key& key) override;

    private:
        BrushButton*         button_;
        const IRenderWindow* render_window_;
        const Event&         event_;
    };
}

#endif //MY_PLUGIN_BRUSH_HPP