#ifndef  SYSTEM_PLUGIN_TOOL_BAR_HPP
#define  SYSTEM_PLUGIN_TOOL_BAR_HPP

#include "../View/bar.hpp"
#include "../View/canvas.hpp"

namespace sys_plugin
{
    class ToolBarButton : public psapi::ABarButton
    {
    public:
        ToolBarButton(  const psapi::IBar* parent, 
                        std::unique_ptr<psapi::AButtonAction> action,
                        const char** texture_files,
                        const psapi::vec2i &pos  = psapi::vec2i{0, 0}, 
                        const psapi::vec2u &size = psapi::vec2u{0, 0}, 
                        const psapi::wid_t &id   = psapi::kInvalidWindowId  );
        
        ~ToolBarButton() noexcept override = default;

        virtual void draw(psapi::IRenderWindow* renderWindow) const override;
        virtual bool update(const psapi::IRenderWindow* renderWindow, const psapi::Event& event) override;

        virtual bool loadTextures(const char** texture_files);

    private:
        psapi::sfm::Texture texture_[4];
        psapi::sfm::Sprite  sprite_;
    };

    class ToolBar : public psapi::ABar 
    {
    public:
        ToolBar(const psapi::vec2i& pos, const psapi::vec2u& size, const psapi::vec2u &the_button_size, const size_t &rows_number, const std::string& background);
        ~ToolBar() noexcept override = default;

        virtual void draw(psapi::IRenderWindow* renderWindow) override;
        virtual bool update(const psapi::IRenderWindow* renderWindow, const psapi::Event& event) override;

    private:    
        psapi::sfm::Texture texture_;
        psapi::sfm::Sprite  sprite_;
    };

}

#endif  //SYSTEM_PLUGIN_TOOL_BAR_HPP