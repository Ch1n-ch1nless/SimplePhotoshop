#ifndef  GRAPHICS_CANVAS_HPP
#define  GRAPHICS_CANVAS_HPP

#include "../Standard/api_canvas.hpp"
#include "../Graphics/Graphics.hpp"
#include "window.hpp"

namespace psapi
{
    class Layer : public ILayer
    {
    public:
         Layer(vec2i size);
        ~Layer();

        sfm::Color getPixel(sfm::vec2i pos) const override;
        void       setPixel(sfm::vec2i pos, sfm::Color pixel) override;

        void       resize(vec2i new_size);

    private:
        friend class Canvas;

        vec2i size_;

        std::vector<sfm::Color> pixels_;
    };

    class Canvas : public ICanvas
    {
    public:
         Canvas(vec2i init_size);
        ~Canvas();

        virtual wid_t getId() const override;
        virtual IWindow* getWindowById(wid_t id) override;
        virtual const IWindow* getWindowById(wid_t id) const override;

        virtual vec2i getPos()  const override;
        virtual vec2i getSize() const override;

        virtual void setParent(const IWindow* parent) override;

        virtual void forceActivate() override;
        virtual void forceDeactivate() override;
        virtual bool isWindowContainer() const override;

        virtual void draw(psapi::IRenderWindow* renderWindow)         override;
        virtual bool update(const psapi::IRenderWindow* renderWindow,
                            const psapi::Event& event)                override;

        virtual ILayer*       getLayer(size_t index)       override;
        virtual const ILayer* getLayer(size_t index) const override;

        virtual ILayer*       getTempLayer()       override;
        virtual const ILayer* getTempLayer() const override;

        virtual void cleanTempLayer() override;

        virtual size_t getNumLayers() const override;

        virtual size_t getActiveLayerIndex() const override;
        virtual void   setActiveLayerIndex(size_t index) override;

        virtual bool insertLayer     (size_t index, std::unique_ptr<ILayer> layer) override;
        virtual bool removeLayer     (size_t index) override;
        virtual bool insertEmptyLayer(size_t index) override;

        virtual void setPos  (sfm::vec2i pos)   override;
        virtual void setSize (sfm::vec2i size)  override;
        virtual void setScale(sfm::vec2f scale) override;

        virtual sfm::vec2i getMousePosition() const override;
        virtual bool isPressed()         const override;

    private:
        void drawLayer(const Layer* layer, IRenderWindow* renderWindow);

        std::vector<std::unique_ptr<Layer>> layers_;

        std::unique_ptr<Layer> temp_layer_;

        const IWindow* parent_;

        vec2i size_;
        vec2i pos_;
        vec2f scale_;

        size_t active_layer_id_;

        psapi::sfm::Texture texture_;
        psapi::sfm::Sprite sprite_;

        vec2i last_mouse_pos_;

        bool is_pressed_ = false;
    };

}
#endif //GRAPHICS_CANVAS_HPP