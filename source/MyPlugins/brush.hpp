#ifndef  MY_PLUGINS_BRUSH_HPP
#define  MY_PLUGINS_BRUSH_HPP

#include "../../api/api_actions.hpp"
#include "../../api/api_bar.hpp"
#include "../../api/api_canvas.hpp"
#include "../../api/plugin_example.hpp"

#include <deque>

namespace plugin
{
    const char* const   BRUSH_TEXTURE  = "assets/brush_button.png";

    const psapi::wid_t  kBrushButtonId = 1;

    class BrushAction;

    class BrushButton final : public psapi::IBarButton
    {
    public:
         BrushButton(psapi::ICanvas* canvas);
        ~BrushButton() final = default;

        virtual void  draw(psapi::IRenderWindow* renderWindow)                  override;

        virtual std::unique_ptr<psapi::IAction> 
        createAction(const psapi::IRenderWindow* renderWindow, 
                     const psapi::Event& event                  )               override;

        virtual psapi::wid_t            getId()                          const  override;
        virtual psapi::IWindow*         getWindowById(psapi::wid_t id)          override;
        virtual const psapi::IWindow*   getWindowById(psapi::wid_t id)   const  override;
        virtual psapi::vec2i            getPos()                         const  override;
        virtual psapi::vec2u            getSize()                        const  override;
        virtual void                    setSize(const psapi::vec2u& size)       override;
        virtual void                    setPos(const psapi::vec2i& pos)         override;
        virtual void                    setParent(const IWindow* parent)        override;
        virtual void                    forceActivate()                         override;
        virtual void                    forceDeactivate()                       override;
        virtual bool                    isActive()                       const  override;
        virtual bool                    isWindowContainer()              const  override;

        virtual void                    setState(State state)                   override;
        virtual State                   getState()                       const  override;

    private:
        std::unique_ptr<psapi::sfm::ITexture>   texture_;
        std::unique_ptr<psapi::sfm::ISprite>    sprite_;

        psapi::vec2i                            pos_;
        psapi::vec2u                            size_;
        psapi::IBarButton::State                state_;    
        const psapi::IWindow*                   parent_;
        psapi::ICanvas*                         canvas_;
        psapi::wid_t                            id_;
        bool                                    is_active_;

        friend class BrushAction;
    };

    class BrushAction final : public psapi::IAction
    {
    public:
         BrushAction(BrushButton* button, const psapi::IRenderWindow* renderWindow, const psapi::Event& event);
        ~BrushAction() final = default;

        bool execute   (const Key& key) override;
        bool isUndoable(const Key& key) override;

    private:
        std::deque<psapi::vec2i> mouse_points_;

        psapi::vec2i interpolateHermite(float         t,
                                        psapi::vec2i &point0,
                                        psapi::vec2i &point1,
                                        psapi::vec2i &point2,
                                        psapi::vec2i &point3 );

        size_t calculateStepsNumber(psapi::vec2i &point1, psapi::vec2i &point2);

        void paintNewCircle(psapi::ICanvas* canvas, psapi::sfm::Color color);

        const psapi::IRenderWindow* render_window_;
        BrushButton*                button_;
        const psapi::Event&         event_;

        const int                   BRUSH_RADIUS = 5;
    };

    

} // namespace plugin

#endif //MY_PLUGINS_BRUSH_HPP
