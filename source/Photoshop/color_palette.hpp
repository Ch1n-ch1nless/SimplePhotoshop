#ifndef  MY_API_COLOR_PALETTE_HPP
#define  MY_API_COLOR_PALETTE_HPP

#include "../../api/api_bar.hpp"
#include "options_bar.hpp"

namespace psapi
{
    class ColorPaletteAction;

    class ColorPalette final : public ABarButton, public IColorPalette
    {
    public:
         ColorPalette();
        ~ColorPalette() final = default;

        virtual std::unique_ptr<IAction> 
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

        virtual void            setState(State state)                  override;
        virtual State           getState()                       const override;

        virtual sfm::Color      getColor()                       const override;
        virtual void            setColor(const sfm::Color &color)      override;

        static std::unique_ptr<IColorPalette> create();
    private:
        sfm::Color color_;

        std::unique_ptr<sfm::RectangleShape>                cur_color;
        std::vector<std::unique_ptr<sfm::RectangleShape>>   colors_;

        friend class ColorPaletteAction;
    };

    class ColorPaletteAction : public IAction
    {
    public:
         ColorPaletteAction(ColorPalette* palette, const IRenderWindow* renderWindow, const Event& event);
        ~ColorPaletteAction() override = default;

        bool execute(const Key& key) override;
        bool isUndoable(const Key& key) override;

    private:
        const IRenderWindow*    render_window_;
        ColorPalette*           palette_;
        const Event&            event_;
    };
}

#endif //MY_API_COLOR_PALETTE_HPP