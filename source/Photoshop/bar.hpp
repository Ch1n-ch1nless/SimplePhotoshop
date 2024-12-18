#ifndef  MY_API_BAR_HPP
#define  MY_API_BAR_HPP

#include "../../api/api_bar.hpp"
#include "../Graphics/Graphics.hpp"
#include "window.hpp"
#include "memento.hpp"
#include "actions.hpp"

namespace psapi
{
    class ABarAction;
    class ABarButtonAction;

    class ABarButton : public IBarButton, public AWindow
    {
    public:
        ABarButton(std::unique_ptr<sfm::Texture> init_texture, wid_t id);

        ~ABarButton() override = default;

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

    protected:
        std::unique_ptr<sfm::Texture>   texture_;
        std::unique_ptr<sfm::Sprite>    sprite_;
        State                           state_;

    private:
        friend class ABarButtonAction;
    };

    class ABarButtonAction : public IAction
    {
    public:
         ABarButtonAction(ABarButton *button, const IRenderWindow *renderWindow, const Event &event);
        ~ABarButtonAction() override = default;

        virtual bool execute   (const Key& key) override;
        virtual bool isUndoable(const Key& key) override;

    protected:
        const IRenderWindow*    render_window_;
        ABarButton*             button_;
        const Event&            event_;
    };

    class ABar : public AWindowContainer, public IBar
    {
    public:
        ABar(std::unique_ptr<psapi::sfm::Sprite> sprite,
             std::unique_ptr<psapi::sfm::Sprite> hover_button_sprite,
             std::unique_ptr<psapi::sfm::Sprite> pressed_button_sprite,
             std::unique_ptr<psapi::sfm::Sprite> active_button_sprite,
             psapi::vec2i toolbar_pos,
             psapi::vec2u toolbar_size,
             psapi::vec2u side_gap,
             psapi::vec2u inbutton_gap,
             psapi::vec2u button_size,
             int n_buttons_in_row,
             psapi::wid_t id                                             );

        ~ABar() override = default;

        virtual std::unique_ptr<IAction> createAction(const IRenderWindow* renderWindow, const Event& event) override;

        virtual wid_t           getId()                             const   override;
        virtual IWindow*        getWindowById(wid_t id)                     override;
        virtual const IWindow*  getWindowById(wid_t id)             const   override;
        virtual vec2i           getPos()                            const   override;
        virtual vec2u           getSize()                           const   override;
        virtual void            setSize(const vec2u& size)                  override;
        virtual void            setPos(const vec2i& pos)                    override;
        virtual void            setParent(const IWindow* parent)            override;
        virtual void            forceActivate()                             override;
        virtual void            forceDeactivate()                           override;
        virtual bool            isActive()                          const   override;
        virtual bool            isWindowContainer()                 const   override;

        virtual void            draw(IRenderWindow* renderWindow)           override;

        virtual void            addWindow(std::unique_ptr<IWindow> window)  override;
        virtual void            removeWindow(wid_t id)                      override;

        virtual void            finishButtonDraw(IRenderWindow* renderWindow, const IBarButton* button) const override;
        virtual bool            unPressAllButtons() override;

    protected:
        virtual vec2i           getNextChildPos();

        std::unique_ptr<sfm::Sprite>    background_;
        std::unique_ptr<sfm::Sprite>    hovered_;
        std::unique_ptr<sfm::Sprite>    pressed_;
        std::unique_ptr<sfm::Sprite>    released_;

        psapi::vec2u side_gap_;
        psapi::vec2u inbutton_gap_;
        psapi::vec2u button_size_;

        int n_buttons_in_row_;

        int n_buttons_ = 0;

        mutable int cur_button_it = 0;

        wid_t   last_pressed_id_  = -1;

    private:
        friend class ABarAction;
    };

    class ABarAction : public IAction
    {
    public:
        ABarAction(ABar *bar, const IRenderWindow *renderWindow, const Event &event);
        ~ABarAction() override = default;

        virtual bool execute   (const Key& key) override;
        virtual bool isUndoable(const Key& key) override;

    protected:
        const IRenderWindow*    render_window_;
        ABar*                   bar_;
        const Event&            event_;
    };
}

#endif //MY_API_BAR_HPP