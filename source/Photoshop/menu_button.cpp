#include "menu_button.hpp"

/*=======================< MenuButton implementation >========================*/

psapi::MenuButton::MenuButton(std::unique_ptr<sfm::Texture> init_texture,
                              const IBar*                   nested_bar,
                              wid_t                         id             )
:
    ABarButton(std::move(init_texture), id)
{
    parent_ = static_cast<const IWindow*>(nested_bar);
}

psapi::wid_t psapi::MenuButton::getId() const
{
    return ABarButton::getId();
}

psapi::IWindow* psapi::MenuButton::getWindowById(wid_t id)               
{
    return ABarButton::getWindowById(id);
}

const psapi::IWindow*  psapi::MenuButton::getWindowById(wid_t id) const
{
    return ABarButton::getWindowById(id);
}

psapi::vec2i psapi::MenuButton::getPos() const
{
    return MenuButton::getPos();
}

psapi::vec2u psapi::MenuButton::getSize() const
{
    return ABarButton::getSize();
}

void psapi::MenuButton::setSize(const psapi::vec2u& size)            
{
    ABarButton::setSize(size);
}

void psapi::MenuButton::setPos(const psapi::vec2i& pos)              
{
    ABarButton::setPos(pos);
}

void psapi::MenuButton::setParent(const psapi::IWindow* parent)      
{
    ABarButton::setParent(parent);
}

void psapi::MenuButton::forceActivate()                       
{
    ABarButton::forceActivate();
}

void psapi::MenuButton::forceDeactivate()                     
{
    ABarButton::forceDeactivate();
}

bool psapi::MenuButton::isActive() const
{
    return ABarButton::isActive();
}

bool psapi::MenuButton::isWindowContainer() const
{
    return ABarButton::isWindowContainer();
}


void psapi::MenuButton::draw(psapi::IRenderWindow* renderWindow)     
{
    //TODO: Maybe i need to redo this!
    ABarButton::draw(renderWindow);
}


void psapi::MenuButton::setState(psapi::IBarButton::State state)
{
    ABarButton::setState(state);
}

psapi::IBarButton::State psapi::MenuButton::getState() const    
{
    return ABarButton::getState();
}

void psapi::MenuButton::addMenuItem(std::unique_ptr<psapi::IWindow> item)
{
    IBar* bar = getMenu();
    bar->addWindow(std::move(item));
}

void psapi::MenuButton::activateMenu()
{
    //TODO: Implement this!
}

void psapi::MenuButton::deactivateMenu()
{
    //TODO: Implement this!
}

psapi::IBar* psapi::MenuButton::getMenu()
{
    return dynamic_cast<IBar*>(const_cast<IWindow*>(parent_));
}

const psapi::IBar* psapi::MenuButton::getMenu() const
{
    return dynamic_cast<const IBar*>(parent_);
}

/*============================================================================*/