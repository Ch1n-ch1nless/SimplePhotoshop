#include "options_bar.hpp"

/*=======================< OptionsBar implementation >========================*/

psapi::OptionsBar::OptionsBar()
:
    ABar(std::make_unique<sfm::Sprite>(),
         std::make_unique<sfm::Sprite>(),
         std::make_unique<sfm::Sprite>(),
         std::make_unique<sfm::Sprite>(),
         getOptionsBarIntRect().pos,
         getOptionsBarIntRect().size,
         {20, 20},
         {0, 20},
         {200, 200},
         1,
         kOptionsBarWindowId              )
{
    static std::unique_ptr<sfm::ITexture> texture = sfm::ITexture::create();
    texture->loadFromFile("assets/options_bar_background.png");

    background_->setTexture(texture.get());

    setSize(size_);
    setPos(pos_);
}

void psapi::OptionsBar::draw(IRenderWindow* renderWindow)
{
    ABar::draw(renderWindow);
}

std::unique_ptr<psapi::IAction> 
psapi::OptionsBar::createAction(const IRenderWindow* renderWindow, const Event& event)
{
    return std::make_unique<OptionAction>(this, renderWindow, event);
}

psapi::wid_t psapi::OptionsBar::getId() const
{
    return ABar::getId();
}

psapi::IWindow* psapi::OptionsBar::getWindowById(wid_t id)
{
    return ABar::getWindowById(id);
}

const psapi::IWindow* psapi::OptionsBar::getWindowById(wid_t id) const
{
    return ABar::getWindowById(id);
}

psapi::vec2i psapi::OptionsBar::getPos() const
{
    return ABar::getPos();
}

psapi::vec2u psapi::OptionsBar::getSize() const
{
    return ABar::getSize();
}


void psapi::OptionsBar::setParent(const IWindow* parent)
{
    ABar::setParent(parent);
}

void psapi::OptionsBar::setSize(const vec2u &size)
{
    ABar::setSize(size);
}

void psapi::OptionsBar::setPos(const vec2i &pos)
{
    ABar::setPos(pos);
}


void psapi::OptionsBar::forceActivate()
{
    is_active_ = true;
}

void psapi::OptionsBar::forceDeactivate()
{
    is_active_ = false;
}


bool psapi::OptionsBar::isActive() const
{
    return is_active_;
}

bool psapi::OptionsBar::isWindowContainer() const
{
    return ABar::isWindowContainer();
}


void psapi::OptionsBar::addWindow(std::unique_ptr<IWindow> window)
{
    ABar::addWindow(std::move(window));
}

void psapi::OptionsBar::removeWindow(wid_t id)
{
    ABar::removeWindow(id);
}

void psapi::OptionsBar::finishButtonDraw(IRenderWindow* renderWindow, const IBarButton* button) const
{
    return;
}

bool psapi::OptionsBar::unPressAllButtons()
{
    ABar::unPressAllButtons();
}

void psapi::OptionsBar::removeAllOptions()
{
    children_.clear();
}


/*============================================================================*/

/*======================< OptionAction implementation >=======================*/

psapi::OptionAction::OptionAction(OptionsBar* bar, const IRenderWindow* renderWindow, const Event& event)
:
    render_window_  (renderWindow),
    bar_            (bar),
    event_          (event)
{
}

bool psapi::OptionAction::execute(const Key& key)
{
    for ( auto &option : bar_->children_ )
    {
        if ( !psapi::getActionController()->execute(option->createAction(render_window_, event_)) )
        {
            return false;
        }
    }
    return true;
}

bool psapi::OptionAction::isUndoable(const Key& key)
{
    return false;
}

/*============================================================================*/