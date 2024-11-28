#include "action_controller.hpp"

psapi::ActionController::ActionController()
:
    undo_actions_(),
    redo_actions_()
{
}

bool psapi::ActionController::execute(std::unique_ptr<psapi::IAction> action)
{
    bool result = action->execute();

    if (action->isUndoable())
    {
        IUndoableAction* action_ptr = dynamic_cast<IUndoableAction*>(action.release());
        undo_actions_.push(std::make_unique<IUndoableAction>(action_ptr));
    }

    return result;
}

bool psapi::ActionController::undo()
{
    bool result = undo_actions_.top()->undo();
    redo_actions_.push(std::move(undo_actions_.top()));
    undo_actions_.pop();
    return result;
}

bool psapi::ActionController::redo()
{
    bool result = redo_actions_.top()->redo();
    redo_actions_.pop();
    return result;
}