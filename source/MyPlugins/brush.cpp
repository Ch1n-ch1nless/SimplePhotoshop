#include "brush.hpp"

#include <cassert>
#include <string>

extern "C"
{
    bool onLoadPlugin()
    {
        psapi::IRootWindow* root_window = psapi::getRootWindow();

        psapi::IBar* tool_bar = dynamic_cast<psapi::IBar*>(root_window->getWindowById(psapi::kToolBarWindowId));
        if (tool_bar == nullptr)
        {
            assert(false && "ERROR!!! Plugin can get access to ToolBar!\n");
            return false;
        }

        psapi::ICanvas* canvas = dynamic_cast<psapi::ICanvas*>(root_window->getWindowById(psapi::kCanvasWindowId));
        if (canvas == nullptr)
        {
            assert(false && "ERROR!!! Plugin can get access to Canvas!\n");
            return false;
        }

        tool_bar->addWindow(std::make_unique<plugin::BrushButton>(canvas));

        return true;
    }

    void onUnloadPlugin()
    {

    }
}

/*=======================< BrushButton implementation >=======================*/

plugin::BrushButton::BrushButton(psapi::ICanvas* canvas)
:
    texture_    (psapi::sfm::ITexture::create()),
    sprite_     (psapi::sfm::ISprite::create()),
    pos_        (),
    size_       (),
    state_      (psapi::IBarButton::State::Normal),
    parent_     (nullptr),
    canvas_     (canvas),
    id_         (plugin::kBrushButtonId),
    is_active_  (true)
{
    texture_->loadFromFile(BRUSH_TEXTURE);
    sprite_->setTexture(texture_.get());
    sprite_->setTextureRect(psapi::sfm::IntRect{pos_, size_});
}

psapi::wid_t plugin::BrushButton::getId() const
{
    return id_;
}

psapi::IWindow* plugin::BrushButton::getWindowById(psapi::wid_t id)         
{
    return (id_ == id) ? this : nullptr;
}

const psapi::IWindow* plugin::BrushButton::getWindowById(psapi::wid_t id)   const 
{
    return (id_ == id) ? this : nullptr;
}

psapi::vec2i plugin::BrushButton::getPos() const 
{
    return pos_;
}

psapi::vec2u plugin::BrushButton::getSize() const 
{   
    return size_;
}

void plugin::BrushButton::setSize(const psapi::vec2u& size)      
{
    float factor_x = static_cast<float>(size.x) / 
                     static_cast<float>(size_.x) ;

    float factor_y = static_cast<float>(size.y) / 
                     static_cast<float>(size_.y) ;

    sprite_->setScale(factor_x, factor_y);

    size_ = size;
}

void plugin::BrushButton::setPos(const psapi::vec2i& pos)        
{
    sprite_->setPosition(static_cast<float>(pos.x),
                         static_cast<float>(pos.y) );
    pos_ = pos;
}

void plugin::BrushButton::setParent(const IWindow* parent)       
{
    parent_ = parent;
}

void plugin::BrushButton::forceActivate()                        
{
    is_active_ = true;
}

void plugin::BrushButton::forceDeactivate()                      
{
    is_active_ = false;
}

bool plugin::BrushButton::isActive() const 
{
    return is_active_;
}

bool plugin::BrushButton::isWindowContainer() const 
{
    return false;
}

void plugin::BrushButton::setState(State state)
{
    state_ = state;
}

psapi::IBarButton::State plugin::BrushButton::getState() const
{
    return state_;
}

std::unique_ptr<psapi::IAction> 
plugin::BrushButton::createAction(const psapi::IRenderWindow* renderWindow, 
                                  const psapi::Event& event                )
{
    return std::make_unique<BrushAction>(this, renderWindow, event);
}

void plugin::BrushButton::draw(psapi::IRenderWindow* renderWindow)
{
    renderWindow->draw(sprite_.get());
}

/*============================================================================*/

/*=======================< BrushAction implementation >=======================*/

plugin::BrushAction::BrushAction(      BrushButton* button, 
                                 const psapi::IRenderWindow* renderWindow, 
                                 const psapi::Event& event                )
:
    render_window_  (renderWindow),
    button_         (button),
    event_          (event)
{
}

bool plugin::BrushAction::execute(const Key& key)
{
    psapi::vec2i mouse_pos = psapi::sfm::Mouse::getPosition(render_window_);

    psapi::vec2i pos  = button_->pos_;
    psapi::vec2u size = button_->size_;

    bool is_in_button = (pos.x <= mouse_pos.x) && (mouse_pos.x < (pos.x + size.x)) &&
                        (pos.y <= mouse_pos.y) && (mouse_pos.y < (pos.y + size.y))    ;

    if (is_in_button)
    {
        if (mouse_points_.empty())
        {
            mouse_points_.push_back(mouse_pos);
            return true;
        }

        psapi::vec2i last_mouse_pos_ = mouse_points_.back();

        if (((mouse_pos.x - last_mouse_pos_.x) * (mouse_pos.x - last_mouse_pos_.x) + 
             (mouse_pos.y - last_mouse_pos_.y) * (mouse_pos.y - last_mouse_pos_.y)) < 5)
        {
            return true;
        }

        mouse_points_.push_back(mouse_pos);

        psapi::IColorPalette* palette = 
            dynamic_cast<psapi::IColorPalette*>(psapi::getRootWindow()->getWindowById(psapi::kColorPaletteId));
        
        paintNewCircle(button_->canvas_, palette->getColor());

        return true;
    }

    mouse_points_.clear();

    return false;
}

psapi::vec2i plugin::BrushAction::interpolateHermite(float         t,
                                                     psapi::vec2i &point0,
                                                     psapi::vec2i &point1,
                                                     psapi::vec2i &point2,
                                                     psapi::vec2i &point3 )
{
    psapi::vec2f medium0 = {(point2.x - point0.x) / 2.f, (point2.y - point0.y) / 2.f};
    psapi::vec2f medium1 = {(point3.x - point1.x) / 2.f, (point3.y - point1.y) / 2.f};

    float t2   = t*t,
          t3   = t2 * t,
          t3_2 = t3 * 2,
          t2_3 = t2 * 3;

    float hermite00 =  t3_2 - t2_3 + 1;
    float hermite10 =  t3   - t2*2 + t;
    float hermite01 = -t3_2 + t2_3;
    float hermite11 =  t3   - t2;

    float x = hermite00 * point1.x + hermite10 * medium0.x +
              hermite01 * point2.x + hermite11 * medium1.x;

    float y = hermite00 * point1.y + hermite10 * medium0.y +
              hermite01 * point2.y + hermite11 * medium1.y;

    return psapi::vec2i{(int)round(x), (int)round(y)};
}

size_t plugin::BrushAction::calculateStepsNumber(psapi::vec2i &point1, psapi::vec2i &point2)
{
    float dist = (point2.x - point1.x) * (point2.x - point1.x) +
                 (point2.y - point1.y) * (point2.y - point1.y)  ;
    
    return static_cast<size_t>(std::max(sqrt(dist), 50.0));
}

void plugin::BrushAction::paintNewCircle(psapi::ICanvas* canvas, psapi::sfm::Color color)
{
    if (mouse_points_.size() < 4) 
    {
        return;
    }

    psapi::vec2i &point0 = mouse_points_[0];
    psapi::vec2i &point1 = mouse_points_[1];
    psapi::vec2i &point2 = mouse_points_[2];
    psapi::vec2i &point3 = mouse_points_[3];

    size_t steps_number = calculateStepsNumber(point1, point2);

    for (size_t i = 0; i <= steps_number; ++i)
    {
        float t = static_cast<float>(i) / static_cast<float>(steps_number);

        psapi::vec2i point = interpolateHermite(t, point0, point1, point2, point3);

        for (int offsetY = -BRUSH_RADIUS; offsetY <= BRUSH_RADIUS; offsetY++)
        {
            for (int offsetX = -BRUSH_RADIUS; offsetX <= BRUSH_RADIUS; offsetX++)
            {
                if ((offsetX * offsetX + offsetY * offsetY) <= BRUSH_RADIUS * BRUSH_RADIUS)
                {
                    canvas->getTempLayer()->setPixel(point + psapi::vec2i{offsetX, offsetY}, color);
                }
            }
        }
    }

    mouse_points_.pop_front();
}


bool plugin::BrushAction::isUndoable(const Key& key)
{
    //TODO: Reimplement this code to undoable!
    return false;
}

/*============================================================================*/