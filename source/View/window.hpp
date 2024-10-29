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
        ~AWindow(){};

        virtual void draw(IRenderWindow* renderWindow) override = 0;
        virtual bool update(const IRenderWindow* renderWindow, const Event& event) override = 0;

              wid_t    getId        ()         const override;
              IWindow* getWindowById(wid_t id)       override;
        const IWindow* getWindowById(wid_t id) const override;

        virtual vec2i getPos() const override = 0;
        virtual vec2u getSize() const override = 0;
        virtual void setParent(const IWindow* parent) override = 0;
        virtual void forceActivate() override = 0;
        virtual void forceDeactivate() override = 0;
        virtual bool isActive() const override= 0;

        virtual bool isWindowContainer() const override = 0;

    protected:
        wid_t id_;
    };

    class AWindowContainer : public IWindowContainer
    {
    public:
         AWindowContainer(const wid_t& id = kInvalidWindowId);
        ~AWindowContainer(){};

        wid_t getId() const override;
        bool isWindowContainer() const override;

        virtual void addWindow(std::unique_ptr<IWindow> window) = 0;
        virtual void removeWindow(wid_t id) = 0;

        virtual void draw(IRenderWindow* renderWindow) = 0;
        virtual bool update(const IRenderWindow* renderWindow, const Event& event) = 0;

        virtual IWindow* getWindowById(wid_t id) = 0;
        virtual const IWindow* getWindowById(wid_t id) const = 0;

        virtual vec2i getPos() const = 0;
        virtual vec2u getSize() const = 0;
        virtual void setParent(const IWindow* parent) = 0;
        virtual void forceActivate() = 0;
        virtual void forceDeactivate() = 0;
        virtual bool isActive() const = 0;

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
        ~AWindowVector(){};

        wid_t getId() const override;

        void addWindow(std::unique_ptr<IWindow> window) override;
        void removeWindow(wid_t id) override;

              IWindow* getWindowById(wid_t id)       override;
        const IWindow* getWindowById(wid_t id) const override;

        bool isWindowContainer() const override;

        virtual void draw(IRenderWindow* renderWindow) = 0;
        virtual bool update(const IRenderWindow* renderWindow, const Event& event) = 0;

        virtual vec2i getPos() const = 0;
        virtual vec2u getSize() const = 0;
        virtual void setParent(const IWindow* parent) = 0;
        virtual void forceActivate() = 0;
        virtual void forceDeactivate() = 0;
        virtual bool isActive() const = 0;

    protected:  
        virtual bool checkDuplicate(const wid_t& id);
        virtual void drawChildren(IRenderWindow* renderWindow);
        virtual bool updateChildren(const IRenderWindow* renderWindow, const Event& event);

        wid_t id_;
    };

    class RootWindow : public AWindowVector
    {
    public:
         RootWindow();
        ~RootWindow(){};

        virtual void draw  (      psapi::IRenderWindow* renderWindow) override;
        virtual bool update(const psapi::IRenderWindow* renderWindow,
                            const psapi::sfm::Event& event)           override;
        
        virtual wid_t getId() const override;

        virtual psapi::vec2i getPos()  const          override;
        virtual psapi::vec2u getSize() const          override;
        virtual void setParent(const IWindow* parent) override;
        virtual void forceActivate()                  override;
        virtual void forceDeactivate()                override;
        virtual bool isActive() const                 override;

    private:
        bool is_active = true;
    };

} //psapi


#endif //GRAPHICS_WINDOW_HPP