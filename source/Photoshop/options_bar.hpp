#ifndef  MY_API_OPTIONS_BAR_HPP
#define  MY_API_OPTIONS_BAR_HPP

#include "../../api/api_bar.hpp"
#include "bar.hpp"

namespace psapi
{
    class OptionAction;

    class OptionsBar final : public ABar, public IOptionsBar
    {
    public:
         OptionsBar();
        ~OptionsBar() final = default;

        void draw(IRenderWindow* renderWindow) override;
        std::unique_ptr<IAction> createAction(const IRenderWindow* renderWindow, const Event& event) override;

        wid_t getId() const override;
        IWindow* getWindowById(wid_t id) override;
        const IWindow* getWindowById(wid_t id) const override;
        vec2i getPos() const override;
        vec2u getSize() const override;

        void setParent(const IWindow* parent) override;
        void setSize(const vec2u &size) override;
        void setPos(const vec2i &pos) override;

        void forceActivate() override;
        void forceDeactivate() override;

        bool isActive() const override;
        bool isWindowContainer() const override;

        void addWindow(std::unique_ptr<IWindow> window) override;
        void removeWindow(wid_t id) override;

        void finishButtonDraw(IRenderWindow* renderWindow, const IBarButton* button) const override;
        bool unPressAllButtons() override;

        void removeAllOptions() override;

    private:
        friend class OptionAction;
    };

    class OptionAction : public IAction
    {
    public:
         OptionAction(OptionsBar* bar, const IRenderWindow* renderWindow, const Event& event);
        ~OptionAction() override = default;

        bool execute   (const Key& key) override;
        bool isUndoable(const Key& key) override;

    protected:
        const IRenderWindow* render_window_;
        OptionsBar*          bar_;
        const Event&         event_;
    };
}

#endif //MY_API_OPTIONS_BAR_HPP