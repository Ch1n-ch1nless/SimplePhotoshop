#ifndef  MY_API_ACTION_CONTROLLER_HPP
#define  MY_API_ACTION_CONTROLLER_HPP

#include "api/api_actions.hpp"
#include <stack>

namespace psapi
{
    class ActionController final : public IActionController
    {
    public:
         ActionController();
        virtual ~ActionController() final = 0;

        virtual bool execute(std::unique_ptr<IAction> action) override;
    
        virtual bool undo() override;
        virtual bool redo() override;
    private:
        std::stack<std::unique_ptr<IUndoableAction>> undo_actions_;
        std::stack<std::unique_ptr<IUndoableAction>> redo_actions_;
    };
}

#endif //MY_API_ACTION_CONTROLLER_HPP