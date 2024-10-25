#include "window.hpp"

#include <cassert>

using namespace psapi;

/*=========================< AWindow implementation >=========================*/

AWindow::AWindow(const wid_t& id) : id_(id) {}

wid_t AWindow::getId() const
{
    return id_;
}

IWindow* AWindow::getWindowById(wid_t id)
{
    return (id_ == id) ? this : nullptr;
}

const IWindow* AWindow::getWindowById(wid_t id) const
{
    return (id_ == id) ? this : nullptr;
}

/*============================================================================*/

/*====================< AWindowContainer implementation >=====================*/

AWindowContainer::AWindowContainer(const wid_t& id) : id_(id) {}

wid_t AWindowContainer::getId() const
{
    return id_;
}

bool AWindowContainer::isWindowContainer() const
{
    return true;
}

/*============================================================================*/

/*======================< AWindowVector implementation >======================*/

AWindowVector::AWindowVector(const wid_t& id) : id_(id) {}

wid_t AWindowVector::getId() const
{
    return id_;
}

bool AWindowVector::isWindowContainer() const
{
    return true;
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

void AWindowVector::addWindow(std::unique_ptr<IWindow> window)
{
    if (checkDuplicate(window->getId()))
    {
        //TODO: Temporary solution, needs to fix in the future
        assert(false && "This window is actually in vector, do you really want to add it?\n");
    }
    
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

IWindow* AWindowVector::getWindowById(wid_t id)
{
    for (auto& window : windows_)
    {
        if (window->getId() == id)
        {
            return window.get();
        }
    }

    return (id_ == id) ? this : nullptr;
}

const IWindow* AWindowVector::getWindowById(wid_t id) const
{
    for (auto& window : windows_)
    {
        if (window->getId() == id)
        {
            return window.get();
        }
    }

    return (id_ == id) ? this : nullptr;
}

/*============================================================================*/