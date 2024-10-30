#ifndef  GRAPHICS_BAR_HPP
#define  GRAPHICS_BAR_HPP

#include "../Standard/api_bar.hpp"
#include "../Graphics/Graphics.hpp"
#include "window.hpp"

namespace psapi
{
    class AButtonAction 
    {
    public:
        virtual ~AButtonAction() = default;

        virtual bool operator()(const IRenderWindow* renderWindow, const Event& event) = 0;
    };

    class ABarButton : public IBarButton
    {
    public:
        ABarButton( const IBar* parent, 
                    std::unique_ptr<AButtonAction> action,
                    const psapi::vec2i &pos  = vec2i{0, 0}, 
                    const psapi::vec2u &size = vec2u{0, 0}, 
                    const wid_t &id = kInvalidWindowId);
        
        ABarButton() = default;

        virtual ~ABarButton() noexcept = default;

        virtual void draw(IRenderWindow* renderWindow) const = 0;
        virtual bool update(const IRenderWindow* renderWindow, const sfm::Event& event) = 0;

        virtual       IWindow* getWindowById(wid_t id)       override;
        virtual const IWindow* getWindowById(wid_t id) const override;

        virtual vec2i getPos()  const override;
        virtual vec2u getSize() const override;
        virtual wid_t getId()   const override;

        virtual void setParent(const IWindow* parent) override;
        virtual void forceDeactivate()                override;
        virtual void forceActivate()                  override;
        virtual bool isActive() const                 override;

        virtual void setState(State state);
        virtual State getState() const;

    protected:
        State state_ = State::Normal;

        wid_t   id_ = kInvalidWindowId;

        const IWindow* parent_ = nullptr;
        bool is_active_ = true;

        vec2i pos_;
        vec2u size_;

        std::unique_ptr<AButtonAction> action_;
    };

    class ABar : public IBar
    {
    public:
        ABar(const psapi::vec2i &pos, const psapi::vec2u &size, const wid_t &id = kInvalidWindowId);
        ABar() = default;

        virtual ~ABar() noexcept = 0;

        virtual ChildInfo getNextChildInfo() const = 0;

        virtual void finishButtonDraw(IRenderWindow* renderWindow, const IBarButton* button) = 0;

        virtual       IWindow* getWindowById(wid_t id)       override;
        virtual const IWindow* getWindowById(wid_t id) const override;

        virtual void addWindow(std::unique_ptr<IWindow> window) override;
        virtual void removeWindow(wid_t id) override;

        virtual vec2i getPos()  const override;
        virtual vec2u getSize() const override;
        virtual wid_t getId()   const override;

        virtual void setParent(const IWindow* parent) override;
        virtual void forceDeactivate()                override;
        virtual void forceActivate()                  override; 
        virtual bool isActive() const                 override;

    protected:
        virtual bool checkDuplicate(const wid_t& id);
        virtual void drawChildren(IRenderWindow* renderWindow);
        virtual bool updateChildren(const IRenderWindow* renderWindow, const Event& event);

        std::vector<std::unique_ptr<IWindow>> buttons_;

        wid_t   id_ = kInvalidWindowId;

        const IWindow* parent_ = nullptr;
        bool is_active_ = true;

        vec2i pos_;
        vec2u size_;
    };  

}

#endif //GRAPHICS_BAR_HPP