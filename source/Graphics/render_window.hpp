#ifndef  GRAPHICS_RENDER_WINDOW_HPP
#define  GRAPHICS_RENDER_WINDOW_HPP

#include "../Standard/render_window_api.hpp"

#include <SFML/Graphics.hpp>

namespace psapi
{
    namespace sfm
    {
        class Text;
        class Sprite;
        class Image;

        class RenderWindow : public ARenderWindow
        {
        public:
             RenderWindow(size_t width, size_t height, const std::string& window_title);
            ~RenderWindow() = default;

            virtual bool isOpen ()  override;
            virtual void clear  ()  override;
            virtual void display()  override;
            virtual void close  ()  override;

            virtual bool pollEvent(Event& event) override;

            virtual void draw(Drawable *target) override;

        private:
            sf::RenderWindow window_;

            friend class Text;
            friend class Sprite;
            friend class Image;
        };

    } //sfm

} //psapi

#endif //GRAPHICS_RENDER_WINDOW_HPP