#include "canvas.hpp"

#include <cassert>

using namespace psapi;

/*==========================< Layer implementation >==========================*/

Layer::Layer(vec2i init_size) :
    size_   (init_size),
    pixels_ (static_cast<size_t>(init_size.x * init_size.y))
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

void Layer::resize(vec2i new_size)
{
    size_ = new_size;
    pixels_.resize(static_cast<size_t>(new_size.x * new_size.y));
}

/*============================================================================*/

/*=========================< Canvas implementation >==========================*/



/*============================================================================*/