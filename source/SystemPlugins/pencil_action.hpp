#ifndef  SYSTEM_PLUGIN_PENCIL_ACTION_HPP
#define  SYSTEM_PLUGIN_PENCIL_ACTION_HPP

#include "../View/View.hpp"
#include <deque>

namespace sys_plugin
{
    class PencilAction : public psapi::AButtonAction
    {
    public:
         PencilAction();
        ~PencilAction() override = default;

        bool operator()(const psapi::IRenderWindow* renderWindow, const psapi::Event& event) override;

    private:
        psapi::ICanvas* canvas_;

        std::deque<psapi::vec2i> mouse_points_;

        psapi::vec2i interpolatePoints( float t, 
                                        psapi::vec2i &point0, 
                                        psapi::vec2i &point1, 
                                        psapi::vec2i &point2, 
                                        psapi::vec2i &point3    );

        size_t calcStepNumber(psapi::vec2i &point1, psapi::vec2i &point2);
    };
};

#endif //SYSTEM_PLUGIN_PENCIL_ACTION_HPP