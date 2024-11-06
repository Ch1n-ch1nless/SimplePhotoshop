#include "canvas.hpp"

#include <cassert>

using namespace ps;
using namespace psapi;
using namespace sfm;

/*==========================< Layer implementation >==========================*/

Layer::Layer(const vec2u &size)
:
    size_   (size)
{
    data_.assign(size_.x * size_.y, Color(200, 200, 200));  //TODO: Fix the magic constant!
}

Color Layer::getPixel(vec2i pos) const
{
    if (0 <= pos.x && pos.x <= size_.x &&
        0 <= pos.y && pos.y <= size_.y      )
    {
        int index = pos.x + pos.y * size_.x;

        return data_[index];
    }

    assert(false && "ERROR!!! Mouse not on Layer!\n");
}

void Layer::setPixel(vec2i pos, Color pixel) 
{
    if (0 <= pos.x && pos.x <= size_.x &&
        0 <= pos.y && pos.y <= size_.y      )
    {
        int index = pos.x + pos.y * size_.x;

        data_[index] = pixel;
        return;
    }

    assert(false && "ERROR!!! Mouse not on Layer!\n");
}

void Layer::resize(const vec2u &new_size)
{
    std::vector<Color> new_data(new_size.x * new_size.y, Color(200, 200, 200, 255));    //TODO: FIX the magic constant

    unsigned int min_width  = std::min(new_size.x, size_.x);
    unsigned int min_height = std::min(new_size.y, size_.y);

    for (unsigned int i = 0; i < min_height; i++)
    {
        for (unsigned int j = 0; j < min_width; j++)
        {
            new_data[j + i * min_width] = data_[j + i * min_width];
        }
    }

    data_ = std::move(new_data);
}

/*============================================================================*/

/*=========================< Canvas implementation >==========================*/

Canvas::Canvas(const size_t width, const size_t height)
:
    layers_                 (0),
    texture_                (std::make_unique<Texture>()),
    sprite_                 (std::make_unique<Sprite>()),
    last_mouse_pos_         ({0, 0}),
    scale_                  {1.f, 1.f},
    parent_                 (nullptr),
    is_pressed_             (false),
    is_active_              (true)
{
    pos_.x  = CanvasTopLeftPos.x * width;
    pos_.y  = CanvasTopLeftPos.y * height;

    size_.x = CanvasSize.x * width;
    size_.y = CanvasSize.y * height;

    temp_layer_ = std::make_unique<Layer>(size_);

    texture_->create(size_.x, size_.y);

    layers_.push_back(std::make_unique<Layer>(size_));
}

Canvas::Canvas(const vec2i &position, const vec2u &size)
:
    layers_                 (0),
    temp_layer_             (std::make_unique<Layer>(size)),
    texture_                (std::make_unique<Texture>()),
    sprite_                 (std::make_unique<Sprite>()),
    last_mouse_pos_         ({0, 0}),
    scale_                  {1.f, 1.f},
    parent_                 (nullptr),
    is_pressed_             (false),
    is_active_              (true)
{
    pos_    = position;
    size_   = size;

    texture_->create(size_.x, size_.y);

    layers_.push_back(std::make_unique<Layer>(size));

    for (unsigned int y = 0; y < size_.y; y++)
    {
        for (unsigned int x = 0; x < size_.x; x++)
        {
            layers_.back()->setPixel(vec2i{x, y}, Color{200, 200, 200, 255});   //TODO: Fix the magic constant
        }
    }

    for (unsigned int y = 0; y < size_.y; y++)
    {
        for (unsigned int x = 0; x < size_.x; x++)
        {
            temp_layer_->setPixel(vec2i{x, y}, Color{200, 200, 200, 255});      //TODO: Fix the magic constant
        }
    }
}

void Canvas::drawLayer(const Layer* layer, IRenderWindow* render_window)
{
    texture_->update(layer->data_.data());
    sprite_->setTexture(texture_.get());
    sprite_->setScale(scale_.x, scale_.y);
    sprite_->setPosition(static_cast<float>(pos_.x), static_cast<float>(pos_.y));

    sprite_->draw(render_window);
}

void Canvas::draw(IRenderWindow* render_window)
{
    for (auto& layer : layers_)
    {
        drawLayer(static_cast<Layer*>(layer.get()), render_window);
    }

    drawLayer(temp_layer_.get(), render_window);
}

bool Canvas::update(const IRenderWindow* render_window, const Event& event)
{
    if (!is_active_)
    {
        return false;
    }

    if (event.type == psapi::Event::EventType::MouseButtonReleased)
    {
        is_pressed_ = false;
    }

    ps::vec2i new_mouse_pos = psapi::sfm::Mouse::getPosition(render_window);

    new_mouse_pos -= pos_;

    bool is_in_window = false;

    if (0 <= new_mouse_pos.x && new_mouse_pos.x <= size_.x &&
        0 <= new_mouse_pos.y && new_mouse_pos.y <= size_.y      )
    {
        is_in_window = true;
    }

    last_mouse_pos_ = new_mouse_pos;

    if (!is_in_window)
    {
        return false;
    }

    if (event.type == psapi::sfm::Event::MouseButtonPressed) 
    {
        is_pressed_ = true;
    }

    return true;
}

wid_t Canvas::getId() const 
{
    return kCanvasWindowId;
}

const IWindow* Canvas::getWindowById(psapi::wid_t id) const
{
    return (id == kCanvasWindowId) ? static_cast<const AWindow*>(this) : nullptr;
}

IWindow* Canvas::getWindowById(psapi::wid_t id)
{
    return (id == kCanvasWindowId) ? static_cast<AWindow*>(this) : nullptr;
}

vec2i Canvas::getPos() const 
{
    return pos_;
}

vec2u Canvas::getSize() const 
{
    return size_;
}

void Canvas::setParent(const IWindow* parent) {
    parent_ = parent;
}

void Canvas::forceActivate() {
    is_active_ = true;
}

void Canvas::forceDeactivate() {
    is_active_ = false;
}

bool Canvas::isWindowContainer() const {
    return false;
}

bool Canvas::isActive() const
{
    return is_active_;
}

ILayer* Canvas::getLayer(size_t index)
{
    return layers_.at(index).get();
}

const ILayer* Canvas::getLayer(size_t index) const
{
    return layers_.at(index).get();
}

ILayer* Canvas::getTempLayer()
{
    return temp_layer_.get();
}

const ILayer* Canvas::getTempLayer() const
{
    return temp_layer_.get();
}

void Canvas::cleanTempLayer()
{
    Color clear_color = {0, 0, 0, 0};

    for (int y = 0; y < size_.y; y++)
    {
        for (int x = 0; x < size_.x; x++)
        {
            temp_layer_->setPixel({x, y}, clear_color);
        }
    }
}

size_t Canvas::getNumLayers() const
{
    return layers_.size();
}

size_t Canvas::getActiveLayerIndex() const
{
    return active_layer_index_;
}

void Canvas::setActiveLayerIndex(size_t index)
{
    active_layer_index_ = index;
}

bool Canvas::insertLayer(size_t index, std::unique_ptr<ILayer> layer) {
    if (index > layers_.size()) 
    {
        assert(false && "ERROR!!! Program can not insert new layer!");
    }

    std::unique_ptr<Layer> new_layer = std::make_unique<Layer>(size_);
    for (int y = 0; y < size_.y; y++)
    {
        for (int x = 0; x < size_.x; x++)
        {
            new_layer->setPixel({x, y}, layer->getPixel({x, y}));
        }
    }

    layers_.insert(layers_.begin() + (long)index, std::move(new_layer));
    return true;
}

bool Canvas::removeLayer(size_t index)
{
    if (index >= layers_.size())
    {
        assert(false && "ERROR!!! Program can not remove layer!");
    }

    layers_.erase(layers_.begin() + (long)index);
    return true;
}

bool Canvas::insertEmptyLayer(size_t index)
{
    if (index > layers_.size())
    {
        assert(false && "ERROR!!! Program can not insert new empty layer!");
    }

    layers_.insert(layers_.begin() + (long)index, std::make_unique<Layer>(size_));
    return true;
}

void Canvas::setPos(vec2i pos)
{
    pos_ = pos;
}

void Canvas::setSize(vec2i size)
{
    size_.x = size.x;
    size_.y = size.y;

    temp_layer_->resize(size_);

    for (auto& layer : layers_)
    {
        static_cast<Layer*>(layer.get())->resize(size_);
    }
}

void Canvas::setScale(vec2f scale)
{
    scale_ = scale;
}

vec2i Canvas::getMousePosition() const
{
    return last_mouse_pos_;
}

bool Canvas::isPressed() const
{
    return is_pressed_;
}

/*============================================================================*/