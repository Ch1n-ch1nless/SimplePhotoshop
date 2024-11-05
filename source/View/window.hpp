#ifndef  VIEW_WINDOW_HPP
#define  VIEW_WINDOW_HPP

#include "../Standard/api_photoshop.hpp"
#include "../Graphics/Graphics.hpp"

namespace ps
{
    using psapi::IRenderWindow;
    using psapi::Event;

    using psapi::vec2i;
    using psapi::vec2f;
    using psapi::vec2u;
    using psapi::vec2d;

    using psapi::wid_t;

    class AWindow : public psapi::IWindow
    {
    public:
        virtual ~AWindow();

        virtual void draw(IRenderWindow* render_window) override = 0;
        virtual bool update(const IRenderWindow* renderWindow, const Event& event) override = 0;

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

    protected:
        vec2u   size_;
        vec2i   pos_;
        wid_t   id_;
        bool    is_active_;

        const IWindow*  parent_;
    };

    class AWindowContainer : public psapi::IWindowContainer, public AWindow
    {
    public:
        virtual ~AWindowContainer() = default;

        virtual void addWindow(std::unique_ptr<IWindow> window) override = 0;
        virtual void removeWindow(wid_t id)                     override = 0;

        virtual void draw(IRenderWindow* render_window) override = 0;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override = 0;

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

    protected:
        virtual void drawChildren(IRenderWindow* render_window) = 0;
        virtual bool updateChildren(const IRenderWindow* render_window, const Event& event) = 0;
        virtual bool checkDuplicate(const wid_t& id) = 0;
    };

    class AWindowVector : public AWindowContainer, public psapi::IWindowVector
    {
    public:
         AWindowVector() = default;
        ~AWindowVector() override = default;

        virtual void draw(IRenderWindow* render_window) override = 0;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override = 0;

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

    protected:
        virtual void drawChildren(IRenderWindow* render_window) override;
        virtual bool updateChildren(const IRenderWindow* render_window, const Event& event) override;
        virtual bool checkDuplicate(const wid_t& id) override;
    };

    class RootWindow : public AWindowVector
    {
    public:
         RootWindow();
        ~RootWindow() = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;
    };
}

#endif //VIEW_WINDOW_HPP