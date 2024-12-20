#include "actions.hpp"

/*====================< ActionController implementation >=====================*/

psapi::ActionController::ActionController()
:
    undo_actions_(),
    redo_actions_()
{
}

bool psapi::ActionController::execute(std::unique_ptr<IAction> action)
{
    if (action == nullptr) return false;

    bool result = actionExecute(action.get());

    if (isUndoableAction(action.get()))
    {
        undo_actions_.push_back(std::move(action));
        if (undo_actions_.size() > MAX_ACTIONS_DEQUE_SIZE)
        {
            undo_actions_.pop_front();
        }
    }

    return result;
}

bool psapi::ActionController::undo()
{
    if (undo_actions_.empty())
    {
        return false;
    }

    std::unique_ptr<IAction> action(std::move(undo_actions_.back()));
    undo_actions_.pop_back();

    bool result = actionUndo(dynamic_cast<IUndoableAction*>(action.get()));

    redo_actions_.push_back(std::move(action));
    if (redo_actions_.size() > MAX_ACTIONS_DEQUE_SIZE)
    {
        redo_actions_.pop_front();
    }

    return result;
}

bool psapi::ActionController::redo()
{
    if (redo_actions_.empty())
    {
        return false;
    }

    std::unique_ptr<IAction> action(std::move(redo_actions_.back()));
    redo_actions_.pop_back();

    return actionRedo(dynamic_cast<IUndoableAction*>(action.get()));
}

/*============================================================================*/

psapi::AActionController* psapi::getActionController()
{
    static std::unique_ptr<psapi::ActionController> 
    global_action_controller = std::make_unique<ActionController>();

    return global_action_controller.get();
}