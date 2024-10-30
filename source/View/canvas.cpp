#include "canvas.hpp"

#include <iostream>
#include <cassert>

using namespace psapi;

/*==========================< Layer implementation >==========================*/

Layer::Layer(vec2u init_size) :
    size_   (init_size),
    pixels_ (static_cast<size_t>(init_size.x * init_size.y))
{
}

Layer::~Layer()
{
}

sfm::Color Layer::getPixel(sfm::vec2i pos) const
{
    size_t x = (size_t)pos.x;
    size_t y = (size_t)pos.y;

    //TODO: Change assert -> another
    assert((x < size_.x) && (y < size_.y));

    return pixels_[y * (size_t)size_.x + x];
}

void Layer::setPixel(sfm::vec2i pos, sfm::Color pixel)
{
    size_t x = (size_t)pos.x;
    size_t y = (size_t)pos.y;

    //TODO: Change assert -> another
    assert((x < size_.x) && (y < size_.y));

    pixels_[y * (size_t)size_.x + x] = pixel;
}

void Layer::resize(vec2u new_size)
{
    std::vector<sfm::Color> new_pixels(static_cast<size_t>(new_size.x * new_size.y));

    int width  = std::min(size_.x, new_size.x);
    int height = std::min(size_.y, new_size.y);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            new_pixels.at(y * new_size.x + x) = pixels_.at(y * size_.x + x);
        }
    }

    size_   = new_size;
    pixels_ = std::move(new_pixels);
}

/*============================================================================*/

/*=========================< Canvas implementation >==========================*/

static const sfm::Color BACKGROUND_COLOR = {200, 200, 200, 255};

Canvas::Canvas(vec2u size) :
    temp_layer_(std::make_unique<Layer>(size)),
    layers_(0),
    size_(size),
    scale_(1.0, 1.0),
    texture_(),
    sprite_(),
    last_mouse_pos_({0, 0}),
    is_pressed_(false) 
{
    texture_.create(static_cast<unsigned int>(size_.x),
                    static_cast<unsigned int>(size_.y));

    layers_.push_back(std::make_unique<Layer>(size_));

    for (int y = 0; y < size_.y; y++)
    {
        for (int x = 0; x < size_.x; x++)
        {
            temp_layer_->setPixel({x, y}, BACKGROUND_COLOR);
        }
    }

    for (int y = 0; y < size_.y; y++) 
    {
        for (int x = 0; x < size_.x; x++) 
        {
            layers_.back()->setPixel({x, y}, BACKGROUND_COLOR);
        }
    }
}

Canvas::~Canvas()
{
}

wid_t Canvas::getId() const
{
    return kCanvasWindowId;
}
IWindow* Canvas::getWindowById(wid_t id)
{
    return (kCanvasWindowId == id) ? this : nullptr;
}
const IWindow* Canvas::getWindowById(wid_t id) const
{
    return (kCanvasWindowId == id) ? this : nullptr;
}

vec2i Canvas::getPos() const
{
    return pos_;
}

vec2u Canvas::getSize() const
{
    return size_;
}

void Canvas::setParent(const IWindow* parent)
{
    parent_ = parent;
}

void Canvas::forceActivate()
{
    return;
}
void Canvas::forceDeactivate()
{
    return;
}

bool Canvas::isActive() const
{
    return true;
}

bool Canvas::isWindowContainer() const
{
    return false;
}

void Canvas::draw(psapi::IRenderWindow* renderWindow)
{   
    if (!is_active_)
    {
        return;
    }

    for (const auto& layer : layers_)
    {
        drawLayer(layer.get(), renderWindow);
    }

    drawLayer(temp_layer_.get(), renderWindow);
}

bool Canvas::updateLastMousePos(const IRenderWindow* renderWindow)
{
    vec2i mouse_pos = sfm::Mouse::getPosition(renderWindow);

    mouse_pos -= pos_;

    last_mouse_pos_ = mouse_pos;

    if (0 <= mouse_pos.x && mouse_pos.x <= size_.x &&
        0 <= mouse_pos.y && mouse_pos.y <= size_.y      )
    {
        return true;
    }

    return false;
}

bool Canvas::update(const IRenderWindow* renderWindow, const Event& event)
{
    if (!is_active_) return false;

    if (event.type == Event::EventType::MouseButtonReleased)
    {
        is_pressed_ = false;
    }

    if (!updateLastMousePos(renderWindow)) return false;

    if (event.type == Event::EventType::MouseButtonPressed)
    {
        is_pressed_ = true;
    }

    return true;
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
    sfm::Color pixel = {0, 0, 0, 0};

    for (int y = 0; y < size_.y; y++)
    {
        for (int x = 0; x < size_.x; x++)
        {
            temp_layer_->setPixel({x, y}, pixel);
        }
    }
}

size_t Canvas::getNumLayers() const
{
    return layers_.size();
}

size_t Canvas::getActiveLayerIndex() const
{
    return active_layer_id_;
}

void Canvas::setActiveLayerIndex(size_t index)
{
    assert(index < layers_.size());
    active_layer_id_ = index;
}

bool Canvas::insertLayer(size_t index, std::unique_ptr<ILayer> layer)
{
    assert(index <= layers_.size());

    std::unique_ptr<Layer> new_layer = std::make_unique<Layer>(size_);

    for (int x = 0; x < size_.x; x++) {
        for (int y = 0; y < size_.y; y++) {
            new_layer->setPixel({x, y}, layer->getPixel({x, y}));
        }
    }

    layers_.insert(layers_.begin() + (long)index, std::move(new_layer));
    return true;
}

bool Canvas::removeLayer(size_t index)
{
    assert(index < layers_.size());

    layers_.erase(layers_.begin() + (long)index);
    return true;
}

bool Canvas::insertEmptyLayer(size_t index)
{
    assert(index <= layers_.size());

    std::unique_ptr<Layer> new_layer = std::make_unique<Layer>(size_);

    layers_.insert(layers_.begin() + (long)index, std::move(new_layer));
    return true;
}

void Canvas::setPos(sfm::vec2i pos)
{
    pos_ = pos;
}

void Canvas::setSize(sfm::vec2i size)
{
    size_.x = size.x;
    size_.y = size.y;

    temp_layer_->resize(size_);
    for (auto& layer : layers_) {
        layer->resize(size_);
    }
}

void Canvas::setScale(sfm::vec2f scale)
{
    scale_ = scale;
}

sfm::vec2i Canvas::getMousePosition() const
{
    return last_mouse_pos_;
}

bool Canvas::isPressed() const
{
    return is_pressed_;
}

void Canvas::drawLayer(const Layer* layer, IRenderWindow* renderWindow)
{
    texture_.update(layer->pixels_.data());
    sprite_.setTexture(&texture_);
    sprite_.setScale(scale_.x, scale_.y);
    sprite_.setPosition(static_cast<float>(pos_.x), static_cast<float>(pos_.y));

    sprite_.draw(renderWindow);
}

/*============================================================================*/