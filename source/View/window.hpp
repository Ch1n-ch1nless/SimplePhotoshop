#ifndef  GRAPHICS_WINDOW_HPP
#define  GRAPHICS_WINDOW_HPP

#include "../Graphics/Graphics.hpp"
#include "../Standard/api_photoshop.hpp"

namespace psapi
{
    class AWindow : public IWindow
    {
    public:
         AWindow(const wid_t& id = kInvalidWindowId);
        ~AWindow() = default;

        virtual void draw(IRenderWindow* renderWindow) = 0;
        virtual bool update(const IRenderWindow* renderWindow, const Event& event) = 0;

              wid_t    getId        ()         const override;
              IWindow* getWindowById(wid_t id)       override;
        const IWindow* getWindowById(wid_t id) const override;

        virtual vec2i getPos() const = 0;
        virtual vec2i getSize() const = 0;
        virtual void setParent(const IWindow* parent) = 0;
        virtual void forceActivate() = 0;
        virtual void forceDeactivate() = 0;
        virtual bool isWindowContainer() const = 0;

    protected:
        wid_t id_;
    };

    class AWindowContainer : public IWindowContainer
    {
    public:
         AWindowContainer(const wid_t& id = kInvalidWindowId);
        ~AWindowContainer() = default;

        wid_t getId() const override;
        bool isWindowContainer() const override;

        virtual void addWindow(std::unique_ptr<IWindow> window) = 0;
        virtual void removeWindow(wid_t id) = 0;

        virtual void draw(IRenderWindow* renderWindow) = 0;
        virtual bool update(const IRenderWindow* renderWindow, const Event& event) = 0;

        virtual IWindow* getWindowById(wid_t id) = 0;
        virtual const IWindow* getWindowById(wid_t id) const = 0;

        virtual vec2i getPos() const = 0;
        virtual vec2i getSize() const = 0;
        virtual void setParent(const IWindow* parent) = 0;
        virtual void forceActivate() = 0;
        virtual void forceDeactivate() = 0;

    protected:
        virtual bool checkDuplicate(const wid_t& id) = 0;
        virtual void drawChildren(IRenderWindow* renderWindow) = 0;
        virtual bool updateChildren(const IRenderWindow* renderWindow, const Event& event) = 0;

        wid_t id_;
    };

    class AWindowVector : public IWindowVector
    {
    public:
         AWindowVector(const wid_t& id = kInvalidWindowId);
        ~AWindowVector() = default;

        wid_t getId() const override;

        void addWindow(std::unique_ptr<IWindow> window) override;
        void removeWindow(wid_t id) override;

              IWindow* getWindowById(wid_t id)       override;
        const IWindow* getWindowById(wid_t id) const override;

        bool isWindowContainer() const override;

        virtual void draw(IRenderWindow* renderWindow) = 0;
        virtual bool update(const IRenderWindow* renderWindow, const Event& event) = 0;

        virtual vec2i getPos() const = 0;
        virtual vec2i getSize() const = 0;
        virtual void setParent(const IWindow* parent) = 0;
        virtual void forceActivate() = 0;
        virtual void forceDeactivate() = 0;

    protected:  
        virtual bool checkDuplicate(const wid_t& id);
        virtual void drawChildren(IRenderWindow* renderWindow);
        virtual bool updateChildren(const IRenderWindow* renderWindow, const Event& event);

        wid_t id_;
    };

} //psapi


#endif //GRAPHICS_WINDOW_HPP