#ifndef  MY_API_CANVAS_HPP
#define  MY_API_CANVAS_HPP

#include "../../api/api_canvas.hpp"
#include "../Graphics/Graphics.hpp"
#include "memento.hpp"
#include "window.hpp"

#include <list>

namespace psapi
{
    class Canvas;
    class CanvasAction;

    class Layer final : public ILayer
    {
    public:
        Layer(Canvas* parent);
        Layer(ILayer* parent);
        virtual ~Layer() final = default;

        virtual sfm::Color      getPixel(sfm::vec2i pos)                            const   override;
        virtual void            setPixel(sfm::vec2i pos, sfm::Color pixel)                  override;

        virtual drawable_id_t   addDrawable(std::unique_ptr<sfm::Drawable> object)          override;
        virtual void            removeDrawable(drawable_id_t id)                            override;
        virtual void            removeAllDrawables()                                        override;
        virtual sfm::vec2u      getSize()                                           const   override;

        virtual std::unique_ptr<ILayerSnapshot> save()                                      override;
        virtual void restore(ILayerSnapshot* snapshot)                                      override;

        void resize(vec2u new_layer_size);

    private:
        std::vector<psapi::sfm::Color>                      data_;
        std::vector<std::unique_ptr<psapi::sfm::Drawable>>  drawable_objects_;
        psapi::vec2u                                        size_;
        Canvas*                                             canvas_;

        friend class Canvas;
    };

    class Canvas final : public ICanvas
    {
    public:
        Canvas(const vec2i& init_position, const vec2u& init_size);
        ~Canvas() final = default;

        virtual void                     draw(IRenderWindow* renderWindow) override;
        virtual std::unique_ptr<IAction> createAction(const IRenderWindow* renderWindow, const Event& event) override;

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

        virtual ILayer*         getLayer(size_t index)                      override;
        virtual const ILayer*   getLayer(size_t index)              const   override;

        virtual ILayer*         getTempLayer()                              override;
        virtual const ILayer*   getTempLayer()                      const   override;

        virtual void            cleanTempLayer()                            override;

        virtual size_t          getNumLayers()                      const   override;
        virtual size_t          getActiveLayerIndex()               const   override;
        virtual void            setActiveLayerIndex(size_t index)           override;

        virtual bool            insertLayer(size_t index, std::unique_ptr<ILayer> layer) override;
        virtual bool            removeLayer(size_t index)                                override;
        virtual bool            insertEmptyLayer(size_t index)                           override;

        virtual void            setZoom(sfm::vec2f zoom) override;
        virtual sfm::vec2i      getMousePosition() const override;

        virtual bool            isPressedRightMouseButton() const override;
        virtual bool            isPressedLeftMouseButton()  const override;
        virtual bool            isPressedScrollButton()     const override;

        virtual sfm::Color      getCanvasBaseColor()        const override;

        virtual std::unique_ptr<ICanvasSnapshot> save() override;
        virtual void restore(ICanvasSnapshot* snapshot) override; 

    private:
        void drawLayer(const Layer* layer, IRenderWindow* render_window);

        std::unique_ptr<sfm::Texture>       texture_;
        std::unique_ptr<sfm::Sprite>        sprite_;

        std::vector<std::unique_ptr<Layer>> layers_;
        std::unique_ptr<Layer>              temp_layer_;

        vec2i                               pos_;
        vec2i                               mouse_position_;
        vec2u                               size_;
        const IWindow*                      parent_;
        size_t                              active_layer_id_;
        bool                                is_active_;

        friend class Layer;
        friend class CanvasAction;
    };

    class CanvasAction final : public IAction
    {
    public:
        CanvasAction(const IRenderWindow *render_window,
                     const Event         &event         );
        ~CanvasAction() final = default;

        virtual bool execute   (const Key& key) override;
        virtual bool isUndoable(const Key& key) override;
    };
}

#endif //MY_API_CANVAS_HPP