#ifndef  VIEW_BAR_HPP
#define  VIEW_BAR_HPP

#include "../Standard/api_bar.hpp"
#include "../Graphics/Graphics.hpp"
#include "window.hpp"

namespace ps
{
    class ABarAction 
    {
    public:
        virtual ~ABarAction() = default;

        virtual bool operator()(const psapi::IRenderWindow* render_window, const psapi::sfm::Event& event) = 0;
    };

    class ABarButton : public psapi::IBarButton, public AWindowVector
    {
    public:
        ABarButton( std::unique_ptr<psapi::sfm::Sprite> sprite, 
                    std::unique_ptr<ABarAction>         action,
                    const IWindow*                      bar_parent  );
        
        virtual ~ABarButton() override = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;

        virtual void addWindow(std::unique_ptr<IWindow> window) override;
        virtual void removeWindow(wid_t id)                     override;

        virtual wid_t getId() const override;
        
        virtual       IWindow* getWindowById(wid_t id)       override;
        virtual const IWindow* getWindowById(wid_t id) const override;

        virtual vec2i getPos()  const override;
        virtual vec2u getSize() const override;

        virtual void setParent(const IWindow* parent) override;

        virtual void forceActivate() override;
        virtual void forceDeactivate() override;

        virtual bool isActive() const override;

        virtual bool isWindowContainer() const override;

        virtual void setSize(const vec2u& size);
        virtual void setPos(const vec2i& position);

        virtual void setState(State state) override;
        virtual State getState() const override;  

    protected:
        virtual void drawChildren(IRenderWindow* render_window) override;
        virtual bool updateChildren(const IRenderWindow* render_window, const Event& event) override;
        virtual void activeChildren(const IRenderWindow* render_window, const Event& event);

        std::unique_ptr<psapi::sfm::Sprite> sprite_;
        std::unique_ptr<ABarAction>         action_;
        State state_;
    };

    class ABar : public psapi::IBar, public AWindowVector
    {
    public:
        ABar(std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
             std::unique_ptr<psapi::sfm::Sprite> hover_button,
             std::unique_ptr<psapi::sfm::Sprite> press_button,
             std::unique_ptr<psapi::sfm::Sprite> release_button,
             const vec2i    &bar_position,
             const vec2u    &bar_size,
             const vec2u    &button_size, 
             const size_t   &number_buttons_in_row,
             const wid_t    &id                                     );

        virtual ~ABar() override = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;

        virtual void addWindow(std::unique_ptr<IWindow> window) override;
        virtual void removeWindow(wid_t id)                     override;

        virtual wid_t getId() const override;
        
        virtual       IWindow* getWindowById(wid_t id)       override;
        virtual const IWindow* getWindowById(wid_t id) const override;

        virtual vec2i getPos()  const override;
        virtual vec2u getSize() const override;

        virtual void setParent(const IWindow* parent) override;

        virtual void forceActivate() override;
        virtual void forceDeactivate() override;

        virtual bool isActive() const override;

        virtual bool isWindowContainer() const override;


        virtual psapi::ChildInfo getNextChildInfo() const override;
        virtual void finishButtonDraw(IRenderWindow* renderWindow, const psapi::IBarButton* button) const override;

    protected:
        virtual void drawChildren(IRenderWindow* render_window) override;
        virtual bool updateChildren(const IRenderWindow* render_window, const Event& event) override;
        virtual void handleDoubleAction();
        
        std::unique_ptr<psapi::sfm::Sprite> background_;
        std::unique_ptr<psapi::sfm::Sprite> hover_button_;
        std::unique_ptr<psapi::sfm::Sprite> press_button_;
        std::unique_ptr<psapi::sfm::Sprite> release_button_;

        const vec2u     button_size_;
        const size_t    n_row_buttons_;
        mutable size_t  cur_button_index;
        mutable ssize_t last_active_button_ = -1;
    };
}

#endif //VIEW_BAR_HPP