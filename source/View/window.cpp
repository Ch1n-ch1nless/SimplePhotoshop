#include "window.hpp"

using namespace ps;

/*=========================< AWindow implementation >=========================*/

psapi::IWindow::~IWindow()
{
}

AWindow::~AWindow()
{
}

wid_t AWindow::getId() const
{
    return id_;
}

psapi::IWindow* AWindow::getWindowById(wid_t id)
{
    return (id == id_) ? this : nullptr;
}

const psapi::IWindow* AWindow::getWindowById(wid_t id) const 
{
    return (id == id_) ? this : nullptr;
}

vec2i AWindow::getPos() const
{
    return pos_;
}

vec2u AWindow::getSize() const
{
    return size_;
}

void AWindow::setParent(const IWindow* parent)
{
    parent_ = parent;
}

void AWindow::forceActivate()
{
    is_active_ = true;
}

void AWindow::forceDeactivate()
{
    is_active_ = false;
}

bool AWindow::isActive() const
{
    return is_active_;
}

bool AWindow::isWindowContainer() const
{
    return false;
}

/*============================================================================*/

/*=====================< AWindowContainer implementation >====================*/

bool AWindowContainer::isWindowContainer() const
{
    return true;
}

/*============================================================================*/

/*======================< AWindowVector implementation >======================*/

void AWindowVector::addWindow(std::unique_ptr<IWindow> window)
{
    if (checkDuplicate(window->getId())) return;

    windows_.push_back(std::move(window));
}

void AWindowVector::removeWindow(wid_t id)
{
    for (auto it = windows_.begin(); it != windows_.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            windows_.erase(it);
            break;
        }
    }
}

psapi::IWindow* AWindowVector::getWindowById(wid_t id)
{
    for (auto& window : windows_)
    {
        if (window->getId() == id)
        {
            return window.get();
        }
    }

    AWindow* ptr = static_cast<AWindow*>(this);

    return (id_ == id) ? ptr : nullptr;
}

const psapi::IWindow* AWindowVector::getWindowById(wid_t id) const
{
    for (auto& window : windows_)
    {
        if (window->getId() == id)
        {
            return window.get();
        }
    }

    const AWindow* ptr = static_cast<const AWindow*>(this);

    return (id_ == id) ? ptr : nullptr;
}

bool AWindowVector::checkDuplicate(const wid_t& id)
{
    for (auto& window : windows_)
    {
        if (window->getId() == id)
        {
            return true;
        }
    }

    return false;
}

void AWindowVector::drawChildren(IRenderWindow* renderWindow)
{
    for (auto& window : windows_)
    {
        window->draw(renderWindow);
    }
}

bool AWindowVector::updateChildren(const IRenderWindow* renderWindow, const Event& event)
{
    bool result = false;

    for (auto& window : windows_)
    {
        result |= window->update(renderWindow, event);
    }

    return result;
}

/*============================================================================*/

/*======================< api_photoshop_implementation >======================*/

bool psapi::IWindowContainer::isWindowContainer() const
{
    return true;
}

bool psapi::IWindowVector::isWindowContainer() const
{
    return true;
}

void psapi::IWindowVector::addWindow(std::unique_ptr<IWindow> window)
{
    AWindowVector* real_ptr = static_cast<AWindowVector*>(this);
    real_ptr->addWindow(std::move(window));
}

void psapi::IWindowVector::removeWindow(wid_t id)
{
    AWindowVector* real_ptr = static_cast<AWindowVector*>(this);
    real_ptr->removeWindow(id);
}

psapi::IWindow* psapi::IWindowVector::getWindowById(wid_t id)
{
    AWindowVector* real_ptr = static_cast<AWindowVector*>(this);
    return real_ptr->getWindowById(id);
}

const psapi::IWindow* psapi::IWindowVector::getWindowById(wid_t id) const
{
    const AWindowVector* real_ptr = static_cast<const AWindowVector*>(this);
    return real_ptr->getWindowById(id);
}

/*============================================================================*/