#include "canvas.hpp"

#include <iostream>

/*==========================< Layer implementation >==========================*/

psapi::Layer::Layer(psapi::Canvas* parent)
:
    canvas_ (parent),
    size_   (parent->getSize())
{
     data_.assign(size_.x * size_.y, sfm::Color(255, 255, 255));
}

psapi::Layer::Layer(ILayer* parent)
{
    Layer* old_layer = dynamic_cast<Layer*>(parent);

    data_.resize(static_cast<size_t>(old_layer->size_.x) *
                 static_cast<size_t>(old_layer->size_.y)  );

    size_   = old_layer->size_;
    canvas_ = old_layer->canvas_;

    for (unsigned int y = 0; y < size_.y; y++)
    {
        for (unsigned int x = 0; x < size_.x; x++)
        {
            data_[static_cast<size_t>(y * size_.x + x)] = 
                old_layer->data_[static_cast<size_t>(y * size_.x + x)];
        }
    }
}

psapi::sfm::Color psapi::Layer::getPixel(sfm::vec2i pos) const
{
    pos -= canvas_->getPos();
    if (((0 <= pos.x) && (pos.x < size_.x)) &&
        ((0 <= pos.y) && (pos.y < size_.y))    )
    {
        //TODO: Rewrite to my exception!
        assert(false && "ERROR!!! Access is denied!\n");
    }

    return data_[static_cast<size_t>(pos.x + pos.y * size_.x)];
}

void psapi::Layer::setPixel(sfm::vec2i pos, psapi::sfm::Color color)
{
    pos -= canvas_->getPos();

    if (((0 <= pos.x) && (pos.x < size_.x)) &&
        ((0 <= pos.y) && (pos.y < size_.y))    )
    {
        //TODO: Rewrite to my exception!
        assert(false && "ERROR!!! Access is denied!\n");
        return;
    }

    data_[static_cast<size_t>(pos.x + pos.y * size_.x)] = color;
}

psapi::drawable_id_t psapi::Layer::addDrawable(std::unique_ptr<sfm::Drawable> object)
{
    drawable_objects_.push_back(std::move(object));
}

void psapi::Layer::removeDrawable(psapi::drawable_id_t id)
{
    drawable_objects_.erase(drawable_objects_.begin() + id);
}

void psapi::Layer::removeAllDrawables()
{
    drawable_objects_.clear();
}

psapi::vec2u psapi::Layer::getSize() const
{
    return size_;
}

std::unique_ptr<psapi::ILayerSnapshot> psapi::Layer::save()
{
    assert(false && "Function is not implemented!\n");
    return nullptr;
}
        
void psapi::Layer::restore(psapi::ILayerSnapshot* snapshot)
{
    assert(false && "Function is not implemented!\n");
}

void psapi::Layer::resize(psapi::vec2u new_layer_size)
{
    std::vector<sfm::Color> new_data(static_cast<size_t>(new_layer_size.x) *
                                     static_cast<size_t>(new_layer_size.y)  );

    unsigned int min_height = std::min(size_.y, new_layer_size.y);
    unsigned int min_width  = std::min(size_.x, new_layer_size.x);

    for (unsigned int x = 0; x < min_width; x++) 
    {
        for (unsigned int y = 0; y < min_height; y++) 
        {
            new_data.at(static_cast<size_t>(y * min_width + x)) =
                data_.at(static_cast<size_t>(y * min_width + x));
        }
    }

    for (unsigned int x = min_width; x < new_layer_size.x; x++)
    {
        for (unsigned int y = 0; y < new_layer_size.y; y++) 
        {
            new_data.at(static_cast<size_t>(y * new_layer_size.x + x)) = sfm::Color(255, 255, 255, 255);
        }
    }

    for (unsigned int x = 0; x < new_layer_size.x; x++)
    {
        for (unsigned int y = min_height; y < new_layer_size.y; y++)
        {
            new_data.at(static_cast<size_t>(y * new_layer_size.x + x)) = sfm::Color(255, 255, 255, 255);
        }
    }

    size_ = new_layer_size;
    data_ = std::move(new_data);
}

/*============================================================================*/

/*=========================< Canvas implementation >==========================*/

psapi::Canvas::Canvas(const vec2i& init_position,
                      const vec2u& init_size     )
:
    texture_        (std::make_unique<sfm::Texture>()),
    sprite_         (std::make_unique<sfm::Sprite>()),
    layers_         (0),
    pos_            (init_position),
    mouse_position_ (vec2i{0, 0}),
    size_           (init_size),
    active_layer_id_(0),
    is_active_      (true)
{
    texture_->create(size_.x, size_.y);

    temp_layer_ = std::make_unique<Layer>(this);
    layers_.push_back(std::make_unique<Layer>(this));
}

psapi::ILayer *psapi::Canvas::getLayer(size_t index)
{
    if (index < layers_.size())
    {
        assert(false && "ERROR!!! Incorrect argument in function!\n");
    }

    return layers_[index].get();
}

const psapi::ILayer *psapi::Canvas::getLayer(size_t index) const
{
    if (index < layers_.size())
    {
        assert(false && "ERROR!!! Incorrect argument in function!\n");
    }

    return layers_[index].get();
}

psapi::ILayer *psapi::Canvas::getTempLayer()
{
    return temp_layer_.get();
}

const psapi::ILayer *psapi::Canvas::getTempLayer() const
{
    return temp_layer_.get();
}

void psapi::Canvas::cleanTempLayer()
{
    temp_layer_->removeAllDrawables();

    for (unsigned int y = 0; y < temp_layer_->size_.y; y++)
    {
        for (unsigned int x = 0; x < temp_layer_->size_.x; x++)
        {
            temp_layer_->setPixel(vec2i{x, y}, sfm::Color(255, 255, 255, 255)); //TODO: Fix magic constant!
        }
    }
}

size_t psapi::Canvas::getNumLayers() const
{
    return layers_.size();
}

size_t psapi::Canvas::getActiveLayerIndex() const
{
    return active_layer_id_;
}

void psapi::Canvas::setActiveLayerIndex(size_t index)
{
    if (index > layers_.size())
    {
        assert(false && "ERROR!!! This index does not exist!\n");
    }

    active_layer_id_ = index;
}

bool psapi::Canvas::insertLayer(size_t index, std::unique_ptr<psapi::ILayer> layer)
{
    if (index > layers_.size())
    {
        return false;
    }

    //TODO: Think how about to refact this strange method!
    std::unique_ptr<Layer> new_layer = std::make_unique<Layer>(layer.release());  
    layers_.insert(layers_.begin() + index, std::move(new_layer));

    return true;
}

bool psapi::Canvas::removeLayer(size_t index)
{
    if (index > layers_.size())
    {
        return false;
    }

    layers_.erase(layers_.begin() + index);
    return true;
}

bool psapi::Canvas::insertEmptyLayer(size_t index)
{
    if (index > layers_.size())
    {
        return false;
    }

    //TODO: Needs to refact, because it's not working good???
    layers_.insert(layers_.begin() + index, std::make_unique<Layer>(this));
    return true;
}

void psapi::Canvas::setZoom(sfm::vec2f zoom)
{
    //TODO: Needs to implement!
    return;
}

psapi::sfm::vec2i psapi::Canvas::getMousePosition() const
{
    return mouse_position_;
}

bool psapi::Canvas::isPressedRightMouseButton() const
{
    //TODO: Implement!
    return false;
}

bool psapi::Canvas::isPressedLeftMouseButton() const
{
    //TODO: Implement!
    return false;
}

bool psapi::Canvas::isPressedScrollButton() const
{
    //TODO: implement!
    return false;
}

psapi::sfm::Color psapi::Canvas::getCanvasBaseColor() const
{
    //TODO: Fix magic constant
    return sfm::Color(255, 255, 255, 255);
}

psapi::wid_t psapi::Canvas::getId() const
{
    return kCanvasWindowId;
}

psapi::IWindow* psapi::Canvas::getWindowById(wid_t id)
{
    return (id == kCanvasWindowId) ? this : nullptr;
}

const psapi::IWindow*  psapi::Canvas::getWindowById(wid_t id) const
{
    return (id == kCanvasWindowId) ? this : nullptr;
}

psapi::vec2i psapi::Canvas::getPos() const
{
    return pos_;
}

psapi::vec2u psapi::Canvas::getSize() const
{
    return size_;
}

void psapi::Canvas::setSize(const vec2u& size)
{
    size_ = size;
}

void psapi::Canvas::setPos(const vec2i& pos)
{
    pos_ = pos;
}

void psapi::Canvas::setParent(const IWindow* parent)
{
    parent_ = parent;
    return;
}   

void psapi::Canvas::forceActivate()
{
    is_active_ = true;
}

void psapi::Canvas::forceDeactivate()
{
    is_active_ = false;
}

bool psapi::Canvas::isActive() const
{
    return is_active_;
}

bool psapi::Canvas::isWindowContainer() const
{
    return false;
}

std::unique_ptr<psapi::ICanvasSnapshot> psapi::Canvas::save()
{
    assert(false && "ERROR!!! Function is not implemented!\n");
    return nullptr;
}

void psapi::Canvas::restore(psapi::ICanvasSnapshot* snapshot)
{
    assert(false && "ERROR!!! Function is not implemented!\n");
} 

void psapi::Canvas::drawLayer(const Layer* layer, IRenderWindow* render_window)
{
    texture_->update(layer->data_.data());
    sprite_->setTexture(texture_.get());
    sprite_->setScale(1.f, 1.f);
    sprite_->setPosition(static_cast<float>(pos_.x), static_cast<float>(pos_.y));

    sprite_->draw(render_window);
}

void psapi::Canvas::draw(IRenderWindow* render_window)
{
    for (auto& layer : layers_)
    {
        drawLayer(layer.get(), render_window);
    }

    drawLayer(temp_layer_.get(), render_window);
}

std::unique_ptr<psapi::IAction> 
psapi::Canvas::createAction(const psapi::IRenderWindow* renderWindow, 
                            const psapi::Event& event                )
{
    //TODO: Implement it later!
    return std::make_unique<CanvasAction>(renderWindow, event);
}

/*============================================================================*/

/*======================< CanvasAction implementation >=======================*/

psapi::CanvasAction::CanvasAction(const IRenderWindow* render_window,
                                  const Event&         event         )
{
}

bool psapi::CanvasAction::execute(const Key& key)
{
    //TODO: implement!
    return true;
}

bool psapi::CanvasAction::isUndoable(const Key& key)
{
    //TODO: implement!
    return false;
}

/*============================================================================*/