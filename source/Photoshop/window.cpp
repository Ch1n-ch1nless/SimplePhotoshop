#include "window.hpp"

/*=========================< AWindow implementation >=========================*/

psapi::AWindow::AWindow(const vec2i    &position, 
                        const vec2u    &size,
                        wid_t           id,
                        const IWindow*  parent,
                        bool            is_active   )
:
    pos_        (position),
    size_       (size),
    id_         (id),
    parent_     (parent),
    is_active_  (is_active)
{
}

psapi::wid_t psapi::AWindow::getId() const
{
    return id_;
}

psapi::IWindow* psapi::AWindow::getWindowById(wid_t id)
{
    return (id_ == id) ? static_cast<IWindow*>(this) : nullptr;
}

const psapi::IWindow* psapi::AWindow::getWindowById(wid_t id) const
{
    return (id_ == id) ? static_cast<const IWindow*>(this) : nullptr;
}

psapi::vec2i psapi::AWindow::getPos() const
{
    return pos_;
}

psapi::vec2u psapi::AWindow::getSize() const
{
    return size_;
}

void psapi::AWindow::setSize(const vec2u &size)
{
    size_ = size;
}

void psapi::AWindow::setPos(const vec2i &pos)
{
    pos_ = pos;
}

void psapi::AWindow::setParent(const psapi::IWindow* parent)
{
    parent_ = parent;
}

void psapi::AWindow::forceActivate()
{
    is_active_ = true;
}

void psapi::AWindow::forceDeactivate()
{
    is_active_ = false;
}

bool psapi::AWindow::isActive() const
{
    return is_active_;
}

bool psapi::AWindow::isWindowContainer() const
{
    return false;
}

/*============================================================================*/

/*====================< AWindowContainer implementation >=====================*/

psapi::AWindowContainer::AWindowContainer(const vec2i    &position, 
                                          const vec2u    &size,
                                          wid_t           id,
                                          const IWindow*  parent,
                                          bool            is_active)
:
    AWindow     (position, size, id, parent, is_active),
    children_   ()
{
}

void psapi::AWindowContainer::drawChildren(IRenderWindow* render_window)
{
    for (auto &child_window : children_)
    {
        child_window->draw(render_window);
    }
}

bool psapi::AWindowContainer::isWindowContainer() const
{
    return true;
}

/*============================================================================*/