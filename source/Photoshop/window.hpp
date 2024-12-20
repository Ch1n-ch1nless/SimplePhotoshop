#ifndef  MY_API_WINDOW_HPP
#define  MY_API_WINDOW_HPP

#include "../../api/api_photoshop.hpp"
#include "actions.hpp"
#include <vector>

namespace psapi
{
    /*=========================< AWindow interface >==========================*/

    class AWindow : public IWindow
    {
    public:
        AWindow(const vec2i   &position,
                const vec2u   &size,
                wid_t          id,
                const IWindow* parent    = nullptr,
                bool           is_active = false   );

        AWindow(const AWindow& other);

        virtual ~AWindow() override = default;

        AWindow& operator=(const AWindow& other) = delete;

        virtual void                     draw(IRenderWindow* renderWindow) override = 0;
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

    protected:
        vec2i           pos_;
        vec2u           size_;
        wid_t           id_;
        const IWindow*  parent_;
        bool            is_active_;
    };

    /*=====================< AWindowContainer interface >=====================*/

    class AWindowContainer : public IWindowContainer, public AWindow
    {
    public:
        AWindowContainer(const vec2i   &position,
                         const vec2u   &size,
                         wid_t          id,
                         const IWindow* parent    = nullptr,
                         bool           is_active = false   );

        AWindowContainer(const AWindowContainer& other);

        virtual ~AWindowContainer() override = default;

        AWindowContainer& operator=(const AWindowContainer& other) = delete;

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

        virtual void            addWindow(std::unique_ptr<IWindow> window)  override;
        virtual void            removeWindow(wid_t id)                      override;

    protected:
        virtual void drawChildren(IRenderWindow* render_window);
        virtual void executeActions(const IRenderWindow* renderWindow, const Event& event);

        std::vector<std::unique_ptr<IWindow>> children_;
    };

    /*========================================================================*/

    /*========================< RootWindow interface >========================*/

    class RootWindow final : public AWindowContainer, public IRootWindow
    {
    public:
        RootWindow(RootWindow& other_window) = delete;
        RootWindow(const size_t width, const size_t height);

        ~RootWindow() final = default;
        
        virtual void                     draw(IRenderWindow* renderWindow) override;
        virtual std::unique_ptr<IAction> createAction(const IRenderWindow* renderWindow, const Event& event) override;

        virtual wid_t           getId()                                     const   override;
        virtual IWindow*        getWindowById(wid_t id)                             override;
        virtual const IWindow*  getWindowById(wid_t id)                     const   override;
        virtual vec2i           getPos()                                    const   override;
        virtual vec2u           getSize()                                   const   override;
        virtual void            setSize(const vec2u& size)                          override;
        virtual void            setPos(const vec2i& pos)                            override;
        virtual void            setParent(const IWindow* parent)                    override;
        virtual void            forceActivate()                                     override;
        virtual void            forceDeactivate()                                   override;
        virtual bool            isActive()                                  const   override;
        virtual bool            isWindowContainer()                         const   override;

        virtual void            addWindow(std::unique_ptr<IWindow> window)          override;
        virtual void            removeWindow(wid_t id)                              override;

        virtual layer_id_t      getUpperLayerId()                           const   override;
        virtual layer_id_t      increaseLayerId()                                   override;
        virtual layer_id_t      decreaseLayerId()                                   override;

    private:
        layer_id_t  active_layer_id_;
    };

    /*========================================================================*/
}

#endif //MY_API_WINDOW_HPP