#ifndef  SYSTEM_PLUGINS_TOOL_BAR_HPP
#define  SYSTEM_PLUGINS_TOOL_BAR_HPP

#include "../View/View.hpp"
/*
namespace sys_plugin
{
    const char* const TOOL_BAR_BACKGROUND       = "pictures/tool_bar_background.png";

    const char* const TOOL_BAR_BUTTON_PRESSED   = "pictures/pressed_skin.png";
    const char* const TOOL_BAR_BUTTON_HOVERED   = "pictures/hovered_skin.png";
    const char* const TOOL_BAR_BUTTON_RELEASED  = "pictures/released_skin.png";

    class ToolBar : public ps::ABar
    {
    public:
         ToolBar();
        ~ToolBar() override = default;

        virtual void draw(psapi::IRenderWindow* render_window) override;
        virtual bool update(const psapi::IRenderWindow* render_window, const ps::Event& event) override;

        virtual psapi::ChildInfo getNextChildInfo() const override;

        virtual void addWindow(std::unique_ptr<IWindow> window) override;

        virtual void finishButtonDraw(psapi::IRenderWindow* renderWindow, const psapi::IBarButton* button) const override;

    private:
        psapi::sfm::Texture back_texture_;
        psapi::sfm::Sprite  background_;

        psapi::sfm::Texture hover_texture_;
        psapi::sfm::Sprite  button_is_hovered_;

        psapi::sfm::Texture pressed_texture;
        psapi::sfm::Sprite  button_is_pressed_;

        psapi::sfm::Texture released_texture;
        psapi::sfm::Sprite  button_is_released_;

        const vec2f     button_scale    = {0.9f, 0.9f};
        vec2i           button_offset;

        const size_t    n_row_buttons    = 3;
        mutable size_t  cur_button_index = 1;

        void updateSprite(sfm::Sprite& sprite, ChildInfo& params);
        void updateSprite(sfm::Sprite& sprite, sfm::Texture& texture, const char* file, ChildInfo& params);
    };
}
*/
#endif //SYSTEM_PLUGINS_TOOL_BAR_HPP