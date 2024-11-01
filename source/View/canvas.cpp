#include "canvas.hpp"

#include <cassert>

using namespace ps;
using namespace psapi;
using namespace sfm;

/*==========================< Layer implementation >==========================*/

Layer::Layer(const vec2i &position, const vec2u &size)
:
    pos_    (position),
    size_   (size),
    data_   ()
{
    data_.assign(size_.x * size_.y, Color(200, 200, 200));  //TODO: Fix the magic constant!
}

Color Layer::getPixel(vec2i pos) const
{
    if (pos_.x <= pos.x && pos.x <= (pos_.x + size_.x) &&
        pos_.y <= pos.y && pos.y <= (pos_.y + size_.y)      )
    {
        int x = pos.x - pos_.x;
        int y = pos.y - pos_.y;

        int index = x + y * size_.x;

        return data_[index];
    }

    assert(false && "ERROR!!! Mouse not on Layer!\n");
}

void Layer::setPixel(vec2i pos, Color pixel) 
{
    if (pos_.x <= pos.x && pos.x <= (pos_.x + size_.x) &&
        pos_.y <= pos.y && pos.y <= (pos_.y + size_.y)      )
    {
        int x = pos.x - pos_.x;
        int y = pos.y - pos_.y;

        int index = x + y * size_.x;

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



/*============================================================================*/