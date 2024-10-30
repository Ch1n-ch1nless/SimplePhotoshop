#ifndef  SYSTEM_PLUGIN_TOOL_BAR_HPP
#define  SYSTEM_PLUGIN_TOOL_BAR_HPP

#include "../View/bar.hpp"
#include "../View/canvas.hpp"

namespace sys_plugin
{
    class ToolBarButton : public psapi::ABarButton
    {
    public:
        ToolBarButton(const psapi::vec2i& pos, const psapi::vec2u& size, const psapi::wid_t& id);
        virtual ~ToolBarButton() noexcept override;

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
        ToolBar(const psapi::vec2i& pos, const psapi::vec2i& size, const std::string& background);
        virtual ~ToolBar() noexcept override;

        virtual void draw(psapi::IRenderWindow* renderWindow) override;
        virtual bool update(const psapi::IRenderWindow* renderWindow, const psapi::Event& event) override;

        virtual psapi::ChildInfo getNextChildInfo() const override;
        virtual void finishButtonDraw(psapi::IRenderWindow* renderWindow, const psapi::IBarButton* button) override;

        void createButtons(const std::vector<std::string> &texture_files);

    private:    
        psapi::sfm::Texture texture_;
        psapi::sfm::Sprite  sprite_;
    };

}

#endif  //SYSTEM_PLUGIN_TOOL_BAR_HPP