#ifndef  VIEW_CANVAS_HPP
#define  VIEW_CANVAS_HPP

#include "window.hpp"
#include "scrollable.hpp"
#include "../Standard/api_canvas.hpp"

namespace ps
{
    class Layer : public psapi::ILayer
    {
    public:
        Layer(const vec2u &size);

        virtual ~Layer() = default;

        virtual psapi::sfm::Color   getPixel(psapi::sfm::vec2i pos) const override;
        virtual void                setPixel(psapi::sfm::vec2i pos, psapi::sfm::Color pixel) override;

        virtual void resize(const vec2u &new_size);

    private:
        std::vector<psapi::sfm::Color> data_;

        vec2u   size_;
        
        friend class Canvas;
    };

    class Canvas : public psapi::ICanvas, public Scrollable, public AWindow
    {
    public:
        Canvas(const size_t width, const size_t height);
        Canvas(const vec2i &position, const vec2u &canvas_size, const vec2u &layer_size);
        virtual ~Canvas() = default;

        virtual void draw(psapi::IRenderWindow* renderWindow)         override;
        virtual bool update(const psapi::IRenderWindow* renderWindow,
                            const psapi::sfm::Event& event)           override;

        virtual psapi::wid_t            getId()                             const   override;
        virtual IWindow*                getWindowById(psapi::wid_t id)              override;
        virtual const IWindow*          getWindowById(psapi::wid_t id)      const   override;
        virtual vec2i                   getPos()                            const   override;
        virtual vec2u                   getSize()                           const   override;
        virtual void                    setParent(const IWindow* parent)            override;
        virtual void                    forceActivate()                             override;
        virtual void                    forceDeactivate()                           override;
        virtual bool                    isActive()                          const   override;
        virtual bool                    isWindowContainer()                 const   override;

        virtual psapi::ILayer*          getLayer(size_t index)                      override;
        virtual const psapi::ILayer*    getLayer(size_t index)              const   override;

        virtual psapi::ILayer*          getTempLayer()                              override;
        virtual const psapi::ILayer*    getTempLayer()                      const   override;

        virtual void                    cleanTempLayer()                            override;

        virtual size_t                  getNumLayers()                      const   override;

        virtual size_t                  getActiveLayerIndex()               const   override;
        virtual void                    setActiveLayerIndex(size_t index)           override;

        virtual bool                    insertLayer     (size_t index, std::unique_ptr<psapi::ILayer> layer)    override;
        virtual bool                    removeLayer     (size_t index)                                          override;
        virtual bool                    insertEmptyLayer(size_t index)                                          override;

        virtual void                    setPos  (vec2i pos)                         override;
        virtual void                    setSize (vec2i size)                        override;
        virtual void                    setScale(vec2f scale)                       override;

        virtual vec2i                   getMousePosition()                  const   override;
        virtual bool                    isPressed()                         const   override;

        virtual void                    scroll(float offsetX, float offsetY)        override;
        virtual void                    scroll(const vec2f &offset)                 override;

    private:
        void drawLayer(const Layer* layer, IRenderWindow* render_window);

        std::vector<std::unique_ptr<psapi::ILayer>> layers_;
        std::unique_ptr<Layer>                      temp_layer_;

        std::unique_ptr<psapi::sfm::Texture>        texture_;
        std::unique_ptr<psapi::sfm::Sprite>         sprite_;

        vec2i                                       last_mouse_pos_;
        vec2f                                       scale_;

        const IWindow*                              parent_;

        size_t                                      active_layer_index_;

        mutable bool                                is_active_;
                bool                                is_pressed_ = false;
    };
}

#endif //VIEW_CANVAS_HPP