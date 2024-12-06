#include "window.hpp"

#include <assert.h>

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

bool psapi::IWindowContainer::isWindowContainer() const
{
    return true;
}

psapi::AWindowContainer::AWindowContainer(const vec2i    &position, 
                                          const vec2u    &size,
                                          wid_t           id,
                                          const IWindow*  parent,
                                          bool            is_active)
:
    AWindow             (position, size, id, parent, is_active),
    IWindowContainer    (),
    children_           ()
{
}

void psapi::AWindowContainer::drawChildren(IRenderWindow* render_window)
{
    for (auto &child_window : children_)
    {
        child_window->draw(render_window);
    }
}

psapi::wid_t psapi::AWindowContainer::getId() const
{
    return id_;
}

psapi::IWindow* psapi::AWindowContainer::getWindowById(wid_t id)
{
    for (auto& window : children_)
    {
        if (window->getWindowById(id) != nullptr)
        {
            return window.get();
        }
    }

    return (id == id_) ? static_cast<psapi::AWindow*>(this) : nullptr;
}

const psapi::IWindow* psapi::AWindowContainer::getWindowById(wid_t id) const
{
    for (auto& window : children_)
    {
        if (window->getWindowById(id) != nullptr)
        {
            return window.get();
        }
    }

    return (id == id_) ? static_cast<const psapi::AWindow*>(this) : nullptr;
}

psapi::vec2i psapi::AWindowContainer::getPos() const
{
    return pos_;
}

psapi::vec2u psapi::AWindowContainer::getSize()  const
{
    return size_;
}

void psapi::AWindowContainer::setSize(const vec2u& size)               
{
    size_ = size;
}

void psapi::AWindowContainer::setPos(const vec2i& pos)                 
{
    pos_ = pos;
}

void psapi::AWindowContainer::setParent(const IWindow* parent)         
{
    parent_ = parent;
}

void psapi::AWindowContainer::forceActivate()                          
{
    is_active_ = true;
}

void psapi::AWindowContainer::forceDeactivate()                        
{
    is_active_ = false;
}

bool psapi::AWindowContainer::isActive() const
{
    return is_active_;
}


bool psapi::AWindowContainer::isWindowContainer() const
{
    return true;
}

void psapi::AWindowContainer::addWindow(std::unique_ptr<IWindow> window)
{
    children_.push_back(std::move(window));
}

void psapi::AWindowContainer::removeWindow(wid_t id)
{
    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        if (it->get()->getId() == id)
        {
            children_.erase(it);
            break;
        }
    }
}

void psapi::AWindowContainer::executeActions(const IRenderWindow* renderWindow, const Event& event)
{
    AActionController* global_controller = getActionController();

    for (auto& window : children_)
    {
        global_controller->execute(window->createAction(renderWindow, event));
    }
}

/*============================================================================*/

/*=======================< RootWindow implementation >========================*/

class RootWindowAction final : public psapi::IAction
{
public:
     RootWindowAction()         = default;
    ~RootWindowAction() final   = default;

    virtual bool execute(const Key& key) override
    {
        return true;
    }

    virtual bool isUndoable(const Key& key) override
    {
        return false;
    }
};

psapi::RootWindow::RootWindow(const size_t width, const size_t height)
:
    AWindowContainer(vec2i{0, 0}, vec2u{width, height}, kRootWindowId, nullptr, true),
    active_layer_id_(0)
{
}

void psapi::RootWindow::draw(IRenderWindow* renderWindow)
{
    drawChildren(renderWindow);
}

std::unique_ptr<psapi::IAction> psapi::RootWindow::createAction(const IRenderWindow* renderWindow, const Event& event)
{
    executeActions(renderWindow, event);
    return std::make_unique<RootWindowAction>();
}

psapi::wid_t psapi::RootWindow::getId() const
{
    return kRootWindowId;
}

psapi::IWindow* psapi::RootWindow::getWindowById(wid_t id)               
{
    for (auto& window : children_)
    {
        if (window->getWindowById(id) != nullptr)
        {
            return window.get();
        }
    }

    return (id == id_) ? static_cast<psapi::AWindow*>(this) : nullptr;
}

const psapi::IWindow* psapi::RootWindow::getWindowById(wid_t id) const
{
    for (auto& window : children_)
    {
        if (window->getWindowById(id) != nullptr)
        {
            return window.get();
        }
    }

    return (id == id_) ? static_cast<const psapi::AWindow*>(this) : nullptr;
}

psapi::vec2i psapi::RootWindow::getPos() const
{
    return pos_;
}

psapi::vec2u psapi::RootWindow::getSize() const
{
    return size_;
}

void psapi::RootWindow::setSize(const vec2u& size)            
{
    size_ = size;
}

void psapi::RootWindow::setPos(const vec2i& pos)              
{
    assert(false && "ERROR!!! Illegal operation!\n");
}

void psapi::RootWindow::setParent(const IWindow* parent)      
{
    assert(false && "ERROR!!! Illegal operation!\n");
}

void psapi::RootWindow::forceActivate()                       
{
    is_active_ = true;
}

void psapi::RootWindow::forceDeactivate()                     
{
    assert(false && "ERROR!!! Illegal operation!\n");
}

bool psapi::RootWindow::isActive() const
{
    return true;
}

bool psapi::RootWindow::isWindowContainer() const
{
    return true;
}

void psapi::RootWindow::addWindow(std::unique_ptr<IWindow> window)
{
    children_.push_back(std::move(window));
}

void psapi::RootWindow::removeWindow(wid_t id)
{
    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        if (it->get()->getId() == id)
        {
            children_.erase(it);
            break;
        }
    }
}

psapi::layer_id_t psapi::RootWindow::getUpperLayerId() const
{
    return active_layer_id_;
}

psapi::layer_id_t psapi::RootWindow::increaseLayerId()
{
    return ++active_layer_id_;
}

psapi::layer_id_t psapi::RootWindow::decreaseLayerId()
{
    return --active_layer_id_;
}


psapi::IRootWindow* psapi::getRootWindow()
{
    static std::unique_ptr<psapi::RootWindow> root_window = std::make_unique<psapi::RootWindow>(1920, 1080);
    return root_window.get(); 
}

/*============================================================================*/