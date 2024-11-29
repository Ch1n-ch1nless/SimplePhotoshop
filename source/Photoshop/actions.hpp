#ifndef  MY_ACTIONS_HPP
#define  MY_ACTIONS_HPP

#include "api/api_actions.hpp"
#include <deque>

namespace psapi
{
    class ActionController final : public AActionController
    {
    public:
         ActionController();
        ~ActionController() final = default;

        virtual bool execute(std::unique_ptr<IAction> action) override;

        virtual bool undo() override;
        virtual bool redo() override;

    private:  
        std::deque<std::unique_ptr<IUndoableAction>> undo_actions_;
        std::deque<std::unique_ptr<IUndoableAction>> redo_actions_;
    
        const size_t MAX_ACTIONS_DEQUE_SIZE = 10;
    };
}

#endif //MY_ACTIONS_HPP